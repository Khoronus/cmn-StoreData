/**
* @file AtomicContainerDataInherit.hpp
* @brief Header of the defined class
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR/AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @original author Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 0.2.0.0
*
*/


#ifndef STOREDATA_BUFFER_ATOMICCONTAINERDATAINHERIT_HPP__
#define STOREDATA_BUFFER_ATOMICCONTAINERDATAINHERIT_HPP__

#include <string>
#include <memory>
#include "buffer_defines.hpp"

namespace storedata
{

/** @brief Container data to transfer data between threads. It copies the data.
*/
class STOREDATA_BUFFER_EXPORT AtomicContainerDataInherit
{
public:

	virtual ~AtomicContainerDataInherit() {}
	virtual void* getObject(int which) = 0;

	virtual void dispose() = 0;
};

} // namespace storedata

#endif // STOREDATA_BUFFER_ATOMICCONTAINERDATAINHERIT_HPP__