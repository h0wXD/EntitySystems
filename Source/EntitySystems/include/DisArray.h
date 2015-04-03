#ifndef ES_DISARRAY_H
#define ES_DISARRAY_H

#include <cstddef>

namespace es
{
	template <class T>
	class DisArray
	{
		T *_data;
		std::size_t _size;
		std::size_t _endIndex;
	public:

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
			return _size;
		}

		template <class Y>
		class iterator_templ
		{
			T *_ptr;
			iterator_templ(T *ptr) : _ptr(ptr) {}
		public:
			iterator_templ<Y> &operator++()
			{
				return _ptr++;
			}

			iterator_templ<Y> &operator--()
			{
				return _ptr--;
			}

			bool &operator==(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr == rhs._ptr;
			}

			bool &operator!=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr != rhs._ptr;
			}

			bool &operator<(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr < rhs._ptr;
			}

			bool &operator>(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr > rhs._ptr;
			}

			bool &operator<=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr <= rhs._ptr;
			}

			bool &operator>=(const iterator_templ<Y> &rhs) const
			{
				return this->_ptr >= rhs._ptr;
			}

			friend class DisArray;
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
	};
}
#endif