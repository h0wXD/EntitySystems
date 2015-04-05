#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <cstddef>
#include <cstdint>

namespace es
{
	class System
	{
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

	protected:
		static void SetHandle(Handle &h, uint16_t id)
		{
			h._id = id;
		}
		
		static Handle CreateHandle(uint16_t id)
		{
			return Handle(id);
		}
	};
}

#endif
