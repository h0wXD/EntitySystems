#include <DisArray.h>
#include <TestSystem.h>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	using es::DisArray;
	using es::System;
	using es::TestSystem;
	using es::TestInstance;
	
	DisArray<int> testArray(8);

	for (int i = 0; i < 8; i++)
	{
		testArray.PushBack(i);
	}

	for (auto t : testArray)
	{
		std::cout << t << " ";
	}

	std::unique_ptr<TestSystem> system(new TestSystem());
	for (int i = 0; i < 100; i++)
	{
		system->Process();
	}

	System::Handle handle = system->Add(5, 8, 12);
	TestInstance test = system->GetInstance(handle);
	
	std::cout << test.Test() << std::endl;
	--test.Test();
	std::cout << test.Test() << std::endl;
	
	std::cin.peek();
	return 0;
}