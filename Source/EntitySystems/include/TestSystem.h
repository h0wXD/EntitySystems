#ifndef ES_TEST_SYSTEM_H
#define ES_TEST_SYSTEM_H

#include <System.h>
#include <DisArray.h>
#include <TestPrintManager.h>

namespace es
{
	class TestSystem : public System
	{
		DisArray<int> testArray;
		DisArray<float> testArray2;
		DisArray<short> testArray3;
	public:
		TestSystem() : testArray(50), testArray2(50), testArray3(50)
		{ 
			for (decltype(testArray.GetSize()) i = 0; i < testArray.GetSize(); i++)
			{
				testArray.PushBack(int(i));
				testArray2.PushBack(i * 0.5f);
				testArray3.PushBack(i * 2);
			}
		}
		
		void Process() override
		{
			if (testArray.GetEndIndex() > 0)
			{
				System::Remove(0, testArray, testArray2, testArray3);
			}
			TestPrintManager<int>::Process(testArray);
			TestPrintManager<float>::Process(testArray2);
		}
	};
}

#endif