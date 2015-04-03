#ifndef ES_DISARRAY_H
#define ES_DISARRAY_H

#include <cstddef>

namespace es
{
	/**
	 * Static sized array that gets allocated at runtime.
	 */
	template <class T>
	class DisArray
	{
		T *_data;
		std::size_t _size;
		std::size_t _endIndex;
	public:

		DisArray(std::size_t size) :
			_size(size),
			_endIndex(0)
		{
			_data = new T[size];
		}

		T *GetRaw()
		{
			return _data;
		}

		std::size_t GetSize() const
		{
			return _size;
		}

		std::size_t GetEndIndex() const
		{
			return _endIndex;
		}

		void PushBack(T &&t)
		{
			_data[_endIndex++] = t;
		}

		void PushBack(const T &t)
		{
			_data[_endIndex++] = t;
		}

		void SwapRemove(std::size_t index)
		{
			--_endIndex;
			_data[index] = _data[_endIndex];
		}

		template <class Y>
		class iterator_templ
		{
			T *_ptr;
		public:
			iterator_templ(T *ptr) : _ptr(ptr) {}

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

			T &operator*()
			{
				return *_ptr;
			}

			T *operator->()
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

		iterator begin() const
		{
			return iterator(_data);
		}

		iterator end() const
		{
			return iterator(_data + _endIndex);
		}

		T &operator[](std::size_t index)
		{
			return _data[index];
		}

		~DisArray()
		{
			delete[] _data;
		}
	};
}
#endif