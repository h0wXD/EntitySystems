#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <cstddef>

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
		virtual void Process() = 0;
		virtual ~System() = 0;
	};
}

#endif
