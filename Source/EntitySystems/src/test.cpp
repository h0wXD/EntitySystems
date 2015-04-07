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
	system->Add(0, 1, 2);
	System::Reference toRemove = system->Add(1, 2, 3);
	System::Reference reference = system->Add(2, 3, 4);

	TestInstance instance = system->GetInstance(system->GetHandle(reference));
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;
	
	system->Remove(toRemove);

	instance = system->GetInstance(system->GetHandle(reference));
	std::cout << instance.Test() << " " << instance.Test2() << " " << instance.Test3() << std::endl;

	std::cin.peek();
	return 0;
}