/* @file sample_record_container_video.cpp
 * @brief Example of recorder for video via container.
 *
 * @section LICENSE
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * @author Alessandro Moro <alessandromoro.italy@gmail.com>
 * @bug No known bugs.
 * @version 0.1.0.0
 * 
 */

#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

#include "record/inc/record/recordcontainervideo.hpp"

class MicroBufferObjDerived : public vb::MicroBufferObjBase
{
public:
	MicroBufferObjDerived() {}
	MicroBufferObjDerived(const std::string &msg, const cv::Mat &img) {
		msg_ = msg;
		img_ = img;
	}

	virtual void clone(MicroBufferObjDerived&obj) {
		obj.set_img(img_);
		obj.set_msg(msg_);
	};
	//template <typename _Ty>
	//_Ty& get_item(int id) { 
	//	if (id == 0) return static_cast<_Ty>(msg_);
	//	if (id == 1) return static_cast<_Ty>(img_);
	//	return nullptr; 
	//}
	virtual void* get_item(int id) {
		if (id == 0) return &msg_;
		if (id == 1) return &img_;
		return nullptr;
	}

	void set_msg(const std::string &msg) {
		msg_ = msg;
	}
	std::string& msg() {
		return msg_;
	}

	void set_img(const cv::Mat &img) {
		img_ = img;
	}
	cv::Mat& img() {
		return img_;
	}

private:

	std::string msg_;
	cv::Mat img_;
};

// ----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	cv::VideoCapture vc(0);
	if (!vc.isOpened()) return -1;

	/** @brief Container with the data to record
	*/
	std::map<int, storedata::RecordContainerVideo> record_container;
	//record_container[0].set_fname_root("data\\sample_RecordContainerVideo");
	//record_container[0].set_size_image(cv::Size(640, 480));

	vb::VolatileTimedBuffer small_buffer_;

	int ff = 0;
	int ss = 0;
	int mm = 0;
	int hh = 0;

	// Container with the margin buffer
	std::vector<vb::PtrMicrobuffer> vptr;


	double start = cv::getTickCount();
	bool continue_capture = true;
	bool bufferize = false;
	bool bufferize_microbuffer = true;
	int num_frame_buffer = 0;
	long long duration_total = 0;
	long long duration_sum_elems = 0;
	int num_frame = 0;
	while (continue_capture) {

		auto t1 = std::chrono::high_resolution_clock::now();

		cv::Mat m;
		vc >> m;
		if (m.empty()) continue;

		// Microbuffering
		if (bufferize_microbuffer) {
			// Increase the timecode. It simulated a sync timecode
			// in the format hh:mm:ss:ff
			++ff;
			if (ff >= 30) { ++ss; ff = 0; }
			if (ss >= 60) { ++mm; ss = 0; }
			if (mm >= 60) { ++hh; mm = 0; }
			std::string timecode = std::to_string(hh) + ":" +
				std::to_string(mm) + ":" + std::to_string(ss) + ":" +
				std::to_string(ff);
			double tnow = (cv::getTickCount() - start) / cv::getTickFrequency();

			small_buffer_.clean_buffer(tnow, 3.0);

			if (!small_buffer_.add_forceexpand(tnow,
				std::make_shared<MicroBufferObjDerived>(MicroBufferObjDerived(timecode, m.clone())))) {
				std::cout << "buffer critical error" << std::endl;
			}
		}



		// Save the current frame
		if (bufferize) {

			// [+] 20170812 Changed the record format
			std::string fname = "data\\F0_" + std::to_string(num_frame_buffer);
			// Add the record to save on a separate thread
			storedata::RecordContainerData rcd0;
			rcd0.copyFrom(m.data, m.cols * m.rows * (m.step / m.cols));
			record_container[0].push(fname, rcd0, true, 0); // <- it allows 
			                                                // only 1 frame 
			                                                // buffering.
			++num_frame_buffer;
		}

		cv::imshow("m", m);
		char c = cv::waitKey(1);

		switch (c) {
		case 27:
			continue_capture = false;
			break;
		case 's':
			bufferize = true;
			record_container[0].set_fname_root("data\\sample_RecordContainerVideo");
			record_container[0].set_size_image(cv::Size(640, 480));
			// copy the microbuffer
			if (bufferize_microbuffer) {
				small_buffer_.get_ptr_containers(5, vptr);
				record_container[0].push(vptr, false, -1);
				// clear the buffers
				vptr.clear();
				small_buffer_.clear();
			}
			bufferize_microbuffer = false;
			record_container[0].start();
			break;
		case 'p':
			bufferize_microbuffer = true;
			bufferize = false;
			record_container[0].set_save_boost(true);
			record_container[0].close(10, 100);
			break;
		}
		++num_frame;

		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		duration_total += duration;
		duration_sum_elems += 1;
		if (num_frame % 30 == 0) {
			std::cout << "Size: " << record_container[0].size_about() << " " << record_container[0].size_about_micro() << std::endl;
			std::cout << "ct: " << duration_total / duration_sum_elems << std::endl;
			duration_total = duration;
			duration_sum_elems = 1;
		}
	}

	record_container[0].set_save_boost(true);
	for (auto &it : record_container) {
		it.second.close(10, 100);
	}
	
	return 0;
}
