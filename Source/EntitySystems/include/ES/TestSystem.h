#ifndef ES_TEST_SYSTEM_H
#define ES_TEST_SYSTEM_H

#include <System.h>
#include <DisArray.h>
#include <TestPrintManager.h>

namespace es
{
	class TestInstance
	{
		friend class TestSystem;
		TestSystem *_system;
		System::Handle _handle;

		TestInstance(TestSystem * system, const System::Handle &handle) :
			_system(system),
			_handle(handle) { }
	public:
		int &Test();
		float &Test2();
		short &Test3();
	};

	class TestSystem : public System
	{
		friend class TestInstance;
		DisArray<int> _testArray;
		DisArray<float> _testArray2;
		DisArray<short> _testArray3;

		void Remove(Handle handle)
		{
			System::Remove(handle.GetId(), _elementCount - 1, _testArray, _testArray2, _testArray3);
		}
	public:

		TestSystem() : _testArray(50), _testArray2(50), _testArray3(50), System(50)
		{ 
			int i = 0;
			float f = 0;
			short s = 0;
			std::generate(_testArray.begin(), _testArray.end(), [&i]() { return i++; });
			std::generate(_testArray2.begin(), _testArray2.end(), [&f]() { return f += 0.5f; });
			std::generate(_testArray3.begin(), _testArray3.end(), [&s]() { return s += 2; });
		}

		Reference Add(int i, float f, short s)
		{
			Handle handle = CreateHandle();
			Reference ref = System::Add(handle);
			auto index = handle.GetId();
			_testArray[index] = i;
			_testArray2[index] = f;
			_testArray3[index] = s;
			return ref;
		}
		
		void Remove(Reference ref)
		{
			Remove(GetHandle(ref));
			System::Remove(ref);
		}

		TestInstance GetInstance(Handle h)
		{
			return TestInstance(this, h);
		}

		TestInstance GetInstance(Reference r)
		{
			return GetInstance(GetHandle(r));
		}

		void Process()
		{
			if (_elementCount > 0)
			{
				Remove(System::CreateHandle(0));
			}
			TestPrintManager<int>::Process(_testArray, _elementCount);
			TestPrintManager<float>::Process(_testArray2, _elementCount);
		}
	};

	int &TestInstance::Test()
	{
		return _system->_testArray[_handle.GetId()];
	}

	float &TestInstance::Test2()
	{
		return _system->_testArray2[_handle.GetId()];
	}

	short &TestInstance::Test3()
	{
		return _system->_testArray3[_handle.GetId()];
	}

}

#endif