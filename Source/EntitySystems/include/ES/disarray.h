/********************************************************************************
 │ 
 │  ╔═════════════╗
 │  ║EntitySystems║
 │  ╚═════════════╝
 ╰╼━━━━━━━━━━━━━━━━━━━━━━━╾
                                                                                
   Copyright (c) 2015 h0wXD & LorenzJ.                                          
   https://github.com/h0wXD                                                     
   https://github.com/LorenzJ                                                   
                                                                                
   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights 
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell    
   copies of the Software, and to permit persons to whom the Software is        
   furnished to do so, subject to the following conditions:                     
                                                                                
   The above copyright notice and this permission notice shall be included in   
   all copies or substantial portions of the Software.                          
                                                                                
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN    
   THE SOFTWARE.                                                                
 ********************************************************************************/


#ifndef ES_DISARRAY_H
#define ES_DISARRAY_H

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <cstdlib>

namespace es
{
	/**
	 * @brief Static sized array that gets allocated at runtime.
	 *
	 * A small static sized array that gets allocated at runtime
	 * Supports up to 32767 items
	 * Can be reallocated at runtime but will not remember its previous data
	 * Does not keep track of how many items it stores nor does it do any
	 * range checking. Does keep track of its capacity.
	 */
	template <class T>
	class disarray final
	{
		// Bitmask for _size
		// Most significant bit of _size indicates whether or not it's an array slice
		static const std::uint16_t BITMASK = 0x7FFFu;
		T *_data;
		std::uint16_t _size;
	public:

		explicit disarray(std::uint16_t size) :
			_size(size)
		{
			_data = new T[size];
		}

		disarray() : _data(nullptr), _size(0) { }

		~disarray()
		{
			if (!(_size >> 15) && _data)
			{
				delete[] _data;
			}
		}

		/**
		 * @brief Allocates a disarray at runtime
		 *
		 * Allocates a disarray at runtime
		 * Old data will get freed if any
		 */
		void Allocate(std::uint16_t size)
		{
			delete[] _data;
			_data = new T[size];
			_size = size;
		}

		T *GetRaw()
		{
			return _data;
		}
		
		std::uint16_t GetSize() const
		{
			return _size & BITMASK;
		}

		/**
		 * @brief Outputs a disarray slice
		 * @param[out] out   The disarray to output the slice to
		 * @param[in]  in    The disarray to take the slice from
		 * @param[in]  start Start index of the slice
		 * @param[in]  size  Number of elements in the slice
		 */
		static void Slice(disarray<T> *out, const disarray<T> &in, std::uint16_t start, std::uint16_t size)
		{
			out->_data = in._data + start;
			out->_size = size | ~BITMASK;
		}

		template <class Y>
		class iterator_templ : public std::iterator<std::random_access_iterator_tag, Y, std::uint16_t>
		{
			Y *_ptr;
		public:
			explicit iterator_templ(Y *ptr) : _ptr(ptr) {}

			iterator_templ<Y> &operator++()
			{
				++_ptr;
				return *this;
			}

			iterator_templ<Y> &operator--()
			{
				--_ptr;
				return *this;
			}

			iterator_templ<Y> operator++(int)
			{
				iterator_templ<Y> copy(*this);
				++_ptr;
				return copy;
			}

			iterator_templ<Y> operator--(int)
			{
				iterator_templ<Y> copy(*this);
				--_ptr;
				return copy;
			}

			iterator_templ<Y> operator+ (const std::uint16_t offset) const
			{
				return iterator_templ<Y>(this->_ptr + offset);
			}

			iterator_templ<Y> operator- (const std::uint16_t offset) const
			{
				return iterator_templ<Y>(this->_ptr - offset);
			}

			iterator_templ<Y> &operator+=(const std::uint16_t offset)
			{
				_ptr += offset;
				return *this;
			}
			iterator_templ<Y> &operator-=(const std::uint16_t offset)
			{
				_ptr -= offset;
				return *this;
			}

			std::uint16_t operator- (const iterator_templ<Y> &rhs) const
			{
				return (std::uintptr_t(_ptr) - std::uintptr_t(rhs._ptr)) / 2;
			}

			iterator_templ<Y> &operator-=(const iterator_templ<Y> &rhs)
			{
				_ptr -= std::uintptr_t(rhs._ptr);
				return *this;
			}

			Y &operator*()
			{
				return *_ptr;
			}

			Y *operator->()
			{
				return _ptr;
			}

			bool operator==(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr == rhs._ptr;
			}

			bool operator!=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr != rhs._ptr;
			}

			bool operator<(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr < rhs._ptr;
			}

			bool operator>(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr > rhs._ptr;
			}

			bool operator<=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr <= rhs._ptr;
			}

			bool operator>=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr >= rhs._ptr;
			}

		};

		/********************************
		 * For interaction with the STL *
		 ********************************/
		typedef iterator_templ<T> iterator;
		typedef const iterator_templ<T> const_iterator;

		T *data()
		{
			return _data;
		}

		const T *data() const
		{
			return _data;
		}

		std::uint16_t size() const
		{
			return _size & BITMASK;
		}

		iterator_templ<T> begin() const
		{
			return iterator_templ<T>(_data);
		}

		iterator_templ<T> end() const
		{
			return iterator_templ<T>(_data + GetSize());
		}

		T &operator[](std::uint16_t index)
		{
			return _data[index];
		}

		const T&operator[](std::uint16_t index) const
		{
			return _data[index];
		}
		
	};
}
#endif
