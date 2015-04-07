#ifndef ES_TEST_PRINT_MANAGER_H
#define ES_TEST_PRINT_MANAGER_H

#include <DisArray.h>
#include <iostream>

namespace es
{
	template <class T>
	class TestPrintManager
	{
	public:
		static void Process(const DisArray<T> &arr, const std::uint16_t elementCount)
		{
			for (auto elem = arr.begin(); elem < arr.end(); ++elem)
			{
				std::cout << *elem << std::endl;
			}
		}
	};
}

#endif