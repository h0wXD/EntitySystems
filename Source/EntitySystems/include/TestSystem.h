#ifndef ES_TEST_SYSTEM_H
#define ES_TEST_SYSTEM_H

#include <System.h>
#include <DisArray.h>
#include <TestPrintManager.h>

namespace es
{
	//class TestSystem;
	class TestInstance
	{
		friend class TestSystem;
		TestSystem *_system;
		System::Handle _handle;
		// std::int_16t _systemGeneration;

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
	public:

		TestSystem() : _testArray(50), _testArray2(50), _testArray3(50)
		{ 
			for (unsigned i = 0; i < _testArray.GetSize(); i++)
			{
				_testArray.PushBack(int(i));
				_testArray2.PushBack(i * 0.5f);
				_testArray3.PushBack(i * 2);
			}
		}

		Handle Add(int i, float f, short s)
		{
			Handle handle;
			SetHandle(handle, _testArray.GetEndIndex());
			_testArray.PushBack(i);
			_testArray2.PushBack(f);
			_testArray3.PushBack(s);
			return handle;
		}
		
		TestInstance GetInstance(Handle h)
		{
			return TestInstance(this, h);
		}

		void Process() override
		{
			if (_testArray.GetEndIndex() > 0)
			{
				System::Remove(0, _testArray, _testArray2, _testArray3);
			}
			TestPrintManager<int>::Process(_testArray);
			TestPrintManager<float>::Process(_testArray2);
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