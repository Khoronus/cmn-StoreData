/** 
/* @file buffer_definies.hpp
* @brief Defines for this project
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
* @author Alessandro Moro <alessandromoro.italy@google.com>
* @bug No known bugs.
* @version 0.1.0.0
*
*/

#ifndef STOREDATA_BUFFER_DEFINES_HPP__
#define STOREDATA_BUFFER_DEFINES_HPP__

#include "core/storedata_defines.hpp"

#if STOREDATADLL_USE_LIB == 1

#ifdef STOREDATABUFFERDLL
#define STOREDATA_BUFFER_EXPORT
#else
#define STOREDATA_BUFFER_EXPORT
#endif

#else // STOREDATADLL_USE_LIB != 1

#ifdef STOREDATABUFFERDLL
#define STOREDATA_BUFFER_EXPORT __declspec(dllexport)
#else
#define STOREDATA_BUFFER_EXPORT __declspec(dllimport)
#endif

#endif // STOREDATADLL_USE_LIB

#endif // STOREDATA_CORE_DEFINES_HPP__
