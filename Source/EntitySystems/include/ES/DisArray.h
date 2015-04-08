#ifndef ES_DISARRAY_H
#define ES_DISARRAY_H

#include <cstddef>
#include <cstdint>
#include <iterator>

namespace es
{
	/**
	 * Static sized array that gets allocated at runtime.
	 */
	template <class T>
	class DisArray final
	{
		static const std::uint16_t _bitmask = 0x7FFFu;
		T *_data;
		std::uint16_t _size;
	public:

		DisArray(std::uint16_t size) :
			_size(size)
		{
			_data = new T[size];
		}

		DisArray() : _data(nullptr), _size(0) { }

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

		std::size_t GetSize() const
		{
			return _size & _bitmask;
		}

		void Move(std::uint16_t destination, std::uint16_t source)
		{
			_data[destination] = _data[source];
		}

		static void Slice(DisArray<T> *out, const DisArray<T> &in, std::uint16_t start, std::uint16_t size)
		{
			out->_data = in._data + start;
			out->_size = size | ~_bitmask;
		}

		template <class Y>
		class iterator_templ : public std::iterator<std::random_access_iterator_tag, Y, std::uint16_t>
		{
			Y *_ptr;
		public:
			iterator_templ(Y *ptr) : _ptr(ptr) {}

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

			iterator_templ<Y> operator+ (const std::uint16_t offset) const
			{
				return iterator_templ<Y>(this->_ptr + offset);
			}

			iterator_templ<Y> operator- (const std::uint16_t offset) const
			{
				return iterator_templ<Y>(this->_ptr - offset);
			}

			iterator_templ<Y> operator+=(const std::uint16_t offset)
			{
				_ptr += offset;
				return *this;
			}
			iterator_templ<Y> operator-=(const std::uint16_t offset)
			{
				_ptr -= offset;
				return *this;
			}

			std::uint16_t operator- (const iterator_templ<Y> &rhs) const
			{
				return (std::uintptr_t(_ptr) - std::uintptr_t(rhs._ptr)) / 2;
			}

			iterator_templ<Y> &operator+=(const iterator_templ<Y> &rhs)
			{
				_ptr += std::uintptr_t(rhs._ptr);
				return *this;
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

		typedef iterator_templ<T> iterator;
		typedef const iterator_templ<T> const_iterator;

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

		~DisArray()
		{
			if (!(_size >> 15))
			{
				delete[] _data;
			}
		}
	};
}
#endif