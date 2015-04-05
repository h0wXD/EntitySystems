#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <cstddef>
#include <cstdint>

namespace es
{
	class System
	{
		std::uint16_t _id;
	protected:
		template <class T>
		static void Remove(std::size_t index, T &t)
		{
			t.SwapRemove(index);
		}

		template <class T, class ...Y>
		static void Remove(std::size_t index, T &head, Y &...tail)
		{
			Remove(index, head);
			Remove(index, tail...);
		}

	public:
		virtual ~System() = 0;

		class Handle
		{
			friend class System;
			std::uint16_t _id;
			// std::int16_t gen;
			Handle(std::uint16_t id) : _id(id) { }
		public:
			Handle() { }
			std::uint16_t GetId()
			{
				return _id;
			}
		};

		class Reference : public Handle { };
	private: DisArray<System::Reference> _referenceArray;
	public:
		System(std::size_t size) : _referenceArray(size), _id(0) { }

	protected:	

		static void SetHandle(Handle &h, uint16_t id)
		{
			h._id = id;
		}
		
		static Handle CreateHandle(uint16_t id)
		{
			return Handle(id);
		}

		Handle CreateHandle()
		{
			return Handle(_id);
		}

		Reference Add(Handle handle)
		{
			++_id;
			auto size = _referenceArray.GetSize();
			std::uint16_t i = 0;
			for (i = 0; i < size; i++)
			{
				if (_referenceArray[i]._id == UINT16_MAX)
				{
					_referenceArray[i]._id = handle.GetId();
				}
			}
			Reference reference;
			reference._id = i;
			return reference;
		}

		void Remove(Reference reference)
		{
			reference._id = UINT16_MAX;
		}

	};
}

#endif
