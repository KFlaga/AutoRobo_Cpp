#include "UTestTestGroup.h"
#include "UTestTestManager.h"

using namespace UTest;

TestGroup::TestGroup(const char* name) :
		_groupName(name)
{
	TestManager::getInstance()->addTestGroup(this);
}

TestGroup::~TestGroup()
{

}

void TestGroup::runAllTests()
{
	init();
	for(auto test : _tests)
	{
		test->init();
		test->run();
		if(true == _endOnFail
				&& TestBase::TestResult::Failed == test->getResult())
		{
			test->deinit();
			break;
		}
		test->deinit();
	}
	deinit();
}

void TestGroup::addTest(TestBase* test)
{
	_tests.push_back(test);
}

void TestGroup::init()
{

}

void TestGroup::deinit()
{

}

