#include "UTestTestBase.h"

using namespace UTest;

TestBase::TestBase(const char* testName) :
		_testName(testName), _testResult(TestResult::NotRun)
{

}

TestBase::~TestBase()
{
}

void TestBase::run()
{
	_testResult = TestResult::Passed;
	test();
}

void TestBase::init()
{

}

void TestBase::deinit()
{

}

void TestBase::assertTrue(bool condition)
{
	if(false == condition)
	{
		this->_testResult = TestResult::Failed;
	}
}

void TestBase::assertFalse(bool condition)
{
	if(true == condition)
	{
		this->_testResult = TestResult::Failed;
	}
}

void TestBase::assertBitsSet(unsigned int flags, unsigned int mask)
{
	assertTrue((flags & mask) == mask);
}

void TestBase::assertBitsReset(unsigned int flags, unsigned int mask)
{
	assertTrue((flags & mask) == (unsigned int)0);
}

