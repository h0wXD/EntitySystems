#include <DisArray.h>
#include <TestSystem.h>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	es::DisArray<int> test(8);

	for (int i = 0; i < 8; i++)
	{
		test.PushBack(i);
	}

	for (auto t : test)
	{
		std::cout << t << " ";
	}

	std::unique_ptr<es::System> system(new es::TestSystem());
	for (int i = 0; i < 100; i++)
	{
		system->Process();
	}
	
	std::cin.peek();
	return 0;
}