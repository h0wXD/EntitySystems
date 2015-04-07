#include <ES/DisArray.h>
#include <ES/TestSystem.h>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	using es::DisArray;
	using es::System;
	using es::TestSystem;
	using es::TestInstance;
	
	std::unique_ptr<TestSystem> system(new TestSystem());
	System::Reference firstItem = system->Add(0, 1, 2);
	System::Reference toRemove = system->Add(1, 2, 3);
	System::Reference reference = system->Add(2, 3, 4);

	TestInstance instance = system->GetInstance(system->GetHandle(reference));
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;
	
	system->Remove(toRemove);

	instance = system->GetInstance(system->GetHandle(reference));
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;

	instance = system->GetInstance(firstItem);
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;
	
	System::Handle handle = system->GetHandle(reference);
	reference = system->GetReference(handle);
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;

	DisArray<int> array(20);
	{
		int i = 0;
		std::generate(array.begin(), array.end(), [&i]()
		{
			return i++;
		});
	}

	DisArray<int> slice;
	array.Slice(&slice, array, 5, 5);
	es::TestPrintManager<int>::Process(slice, slice.GetSize());
	
	std::cin.peek();
	return 0;
}