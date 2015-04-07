#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <DisArray.h>

#include <cstddef>
#include <cstdint>
#include <algorithm>


namespace es
{
	class System
	{ 
		DisArray<std::uint16_t> _referenceArray;
	protected:
		std::uint16_t _elementCount;

		template <class T>
		static void Remove(std::uint16_t destination, std::uint16_t source, T &t)
		{
			t.Move(destination, source);
		}

		template <class T, class ...Y>
		static void Remove(std::uint16_t destination, std::uint16_t source, T &head, Y &...tail)
		{
			Remove(destination, source, head);
			Remove(destination, source, tail...);
		}


	public:
		virtual ~System() = 0;

		class Handle
		{
			friend class System;
			friend class Reference;
			std::uint16_t _id;
			Handle(std::uint16_t id) : _id(id) { }
		public:
			std::uint16_t GetId()
			{
				return _id;
			}
		};

		class Reference
		{
			friend class System;
			std::uint16_t _id;
		public:
			Reference(std::uint16_t id) : _id(id) { }
			Reference() : _id(UINT16_MAX) { }
		};
	
		System(std::size_t size) : _referenceArray(size), _elementCount(0)
		{ 
			std::fill(_referenceArray.begin(), _referenceArray.end(), UINT16_MAX);
		}

	protected:	

		static void SetHandle(Handle &h, std::uint16_t id)
		{
			h._id = id;
		}
		
		static Handle CreateHandle(std::uint16_t id)
		{
			return Handle(id);
		}

		Handle CreateHandle()
		{
			return Handle(_elementCount);
		}

		static std::uint16_t GetReferenceId(const Reference &ref)
		{
			return ref._id;
		}

		Reference Add(Handle handle)
		{
			
			auto ref = std::find_if(_referenceArray.begin(), _referenceArray.end(), [&](const Reference &ref)
			{ 
				return GetReferenceId(ref) == UINT16_MAX;
			});
			*ref = _elementCount;
			++_elementCount;
			return Reference(ref - _referenceArray.begin());
		}

		void Remove(Reference ref)
		{
			--_elementCount;
			auto it = std::find(_referenceArray.begin(), _referenceArray.end(), _elementCount);
			*it = _referenceArray[ref._id];
			_referenceArray[ref._id] = UINT16_MAX;
			
		}

	public:

		Handle GetHandle(Reference ref)
		{
			return CreateHandle(_referenceArray[ref._id]);
		}
	};
}

#endif
