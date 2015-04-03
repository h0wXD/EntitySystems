#ifndef ES_TEST_PRINT_MANAGER_H
#define ES_TEST_PRINT_MANAGER_H

#include <DisArray.h>
#include <iostream>
#include <type_traits>

namespace es
{
	template <class T>
	class TestPrintManager
	{
	public:
		static void Process(const DisArray<T> &array)
		{
			for (auto elem : array)
			{
				std::cout << elem << std::endl;
			}
		}
	};
}

#endif