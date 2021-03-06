#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

#include "record/inc/record/recordcontainerfile.hpp"

//typedef unsigned char BYTE;
//
//std::vector<BYTE> readFile(const char* filename)
//{
//	// open the file:
//	std::ifstream file(filename, std::ios::binary);
//	if (!file.is_open()) {
//		std::cout << "[-] : " << filename << std::endl;
//		return std::vector<BYTE>();
//	}
//
//	// Stop eating new lines in binary mode!!!
//	file.unsetf(std::ios::skipws);
//
//	// get its size:
//	std::streampos fileSize;
//
//	file.seekg(0, std::ios::end);
//	fileSize = file.tellg();
//	file.seekg(0, std::ios::beg);
//
//	// reserve capacity
//	std::vector<BYTE> vec;
//	vec.reserve(fileSize);
//
//	// read the data:
//	vec.insert(vec.begin(),
//		std::istream_iterator<BYTE>(file),
//		std::istream_iterator<BYTE>());
//
//	std::cout << "<readFile/>" << std::endl;
//	return vec;
//}
//
///** @brief It reads some data from a set of files.
//
//The data is in the format XYZRGBA where XYZ is float and RGBA is a 4 byte
//data.
//*/
//void test_binary(
//	const std::string &fname_in) {
//	std::vector<BYTE> vdata = readFile(fname_in.c_str());
//	std::vector<float> data = std::vector<float>(vdata.size() / sizeof(float));
//
//	std::cout << "Copy the points: " << vdata.size() << std::endl;
//	std::cout << "Copy the points: " << data.size() << std::endl;
//	memcpy(data.data(), vdata.data(), sizeof(uchar) * vdata.size());
//
//	for (int i = 0; i < data.size(); ++i) {
//		std::cout << "i > " << data[i] << std::endl;
//	}
//
//	//std::ifstream f(fname_in, std::ios::binary);
//	//for (int i = 0; i < 10000; ++i) {
//	//	float v;
//	//	f.read(reinterpret_cast<char*>(&v), sizeof(float));
//	//	std::cout << "i: " << i << " " << v << std::endl;
//	//}
//}
//
//
//void test() {
//	std::vector<float> data;
//	for (int i = 0; i < 10000; ++i) {
//		data.push_back(i);
//	}
//	// Add the record to save on a separate thread
//	storedata::RecordContainerData rcd;
//	rcd.copyFrom(&data[0], data.size() * sizeof(float));
//
//	/** @brief Container with the data to record
//	*/
//	std::map<int, storedata::RecordContainerFile> record_container;
//	record_container[0].push("fname.data", rcd);
//	record_container[0].start();
//	int r;
//	std::cin >> r;
//}
//
//
//
///** @brief It reads some data from a set of files.
//
//The data is in the format XYZRGBA where XYZ is float and RGBA is a 4 byte
//data.
//*/
//void extract_rgb(
//	const std::string &fname_in,
//	cv::Size &size_in,
//	cv::Mat &rgb) {
//	std::vector<BYTE> vdata = readFile(fname_in.c_str());
//	std::cout << "vdata: " << vdata.size() << std::endl;
//	if (vdata.size() == 0) return;
//	rgb = cv::Mat(size_in, CV_8UC3);
//	memcpy(rgb.data, &vdata[0], vdata.size() * sizeof(uchar));
//}
//
///** @brief It extracts the XYZUV data
//*/
//void extract_xyzuv(
//	const std::string &fname_xyz,
//	const std::string &fname_uv,
//	std::vector<cv::Point3f> &xyz,
//	std::vector<cv::Point2f> &uv) {
//	std::vector<BYTE> xyz_raw_data = readFile(fname_xyz.c_str());
//	std::vector<BYTE> uv_raw_data = readFile(fname_uv.c_str());
//	std::vector<float> xyzdata = std::vector<float>(xyz_raw_data.size() / sizeof(float));
//	std::vector<float> uvdata = std::vector<float>(uv_raw_data.size() / sizeof(float));
//
//	memcpy(xyzdata.data(), xyz_raw_data.data(), sizeof(uchar) * xyz_raw_data.size());
//	memcpy(uvdata.data(), uv_raw_data.data(), sizeof(uchar) * uv_raw_data.size());
//
//	std::cout << "# xyz points: " << xyzdata.size() / 3 << std::endl;
//	std::cout << "# uv points: " << uvdata.size() / 2 << std::endl;
//
//	size_t s = xyzdata.size() / 3;
//	for (size_t i = 0; i < s; ++i) {
//		xyz.push_back(cv::Point3f(xyzdata[i * 3], xyzdata[i * 3 + 1],
//			xyzdata[i * 3 + 2]));
//		uv.push_back(cv::Point2f(uvdata[i * 2], uvdata[i * 2 + 1]));
//	}
//}
//
//
//
///** @brief Example to read saved data from the CaptureRealSense
//*/
//void read_saved_data() {
//	std::string path = "D:\\workspace\\programs\\projects\\CameraCapture\\CameraCaptureRealSense\\build\\sample\\data\\";
//	for (int i = 0; i < 100; ++i) {
//		// read image
//		cv::Mat rgb;
//		extract_rgb(path + "frame_" + std::to_string(i) + ".data", cv::Size(640, 480), rgb);
//		// read xyz
//		std::vector<cv::Point3f> xyz;
//		std::vector<cv::Point2f> uv;
//		extract_xyzuv(
//			path + "xyz_" + std::to_string(i) + ".data",
//			path + "uv_" + std::to_string(i) + ".data",
//			xyz, uv);
//		std::cout << "XYZ: " << xyz.size() << " " << uv.size() << std::endl;
//		// read uv
//		if (!rgb.empty()) {
//			cv::imshow("rgb", rgb);
//			if (cv::waitKey(0) == 27) break;
//		}
//	}
//}


void test_record_container_file() {
	cv::VideoCapture vc(0);
	if (!vc.isOpened()) return;

	/** @brief Container with the data to record
	*/
	std::map<int, storedata::RecordContainerFile> record_container;

	double start = cv::getTickCount();
	bool continue_capture = true;
	bool bufferize = false;
	int num_frame = 0;
	while (continue_capture) {
		cv::Mat m;
		vc >> m;
		if (m.empty()) continue;

		// Save the current frame
		if (bufferize) {

			// [+] 20170812 Changed the record format
			std::string fname = "data\\F0_" + std::to_string(num_frame) + ".data";
			// Add the record to save on a separate thread
			storedata::RecordContainerData rcd0, rcd1;
			rcd0.copyFrom(m.data, m.cols * m.rows * (m.step / m.cols));
			record_container[0].push(fname, rcd0, false, -1);
			fname = "data\\F1_" + std::to_string(num_frame) + ".data";

			rcd1.copyFrom(m.data, m.cols * m.rows * (m.step / m.cols));
			record_container[0].push(fname, rcd1, false, -1);
			++num_frame;
		}
		std::cout << "Size: " << record_container[0].size_about() << " " << record_container[0].size_about_micro() << std::endl;

		cv::imshow("m", m);
		char c = cv::waitKey(1);

		switch (c) {
		case 27:
			continue_capture = false;
			break;
		case 's':
			bufferize = true;
			record_container[0].start();
			break;
		case 'p':
			bufferize = false;
			record_container[0].close(10, 100);
			break;
		}
	}

	record_container[0].set_save_boost(true);
	record_container[0].close(10, 100);

}


//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	// There seems no point in using the microbuffer to save the files
	test_record_container_file();
	return 0;
}
