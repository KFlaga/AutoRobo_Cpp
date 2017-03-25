

#ifndef UTESTTESTGROUP_H_
#define UTESTTESTGROUP_H_

#include "UTestTestBase.h"
#include <vector>

namespace UTest
{

/*
 * Test group holds tests from one test suite.
 *
 * To create new suite, subclass TestGroup and add all tests
 * via 'addTest' in subclass constructor.
 * Pointers to tests are not owned by TestGroup and are not deleted from within (at least not from base)
 * Group is automatically added to TestManager in constructor.
 *
 * Subclasses may override 'init' and 'deinit' methods which are called
 * before first test run in group and after last one ended.
 *
 * All tests are run in same order as they are added.
 */
class TestGroup
{
private:
	std::vector<TestBase*> _tests;
	const char* _groupName;

	bool _endOnFail;

protected:
	TestGroup(const char* groupName);

public:
	virtual ~TestGroup();

	void runAllTests();

	void addTest(TestBase* test);

	// If true, testing ends after one test failed
	bool isEndOnFail() const { return _endOnFail; }
	void setIsEndOnFail(bool val) { _endOnFail = val; }

	const char* getName() const { return _groupName; }

	std::vector<TestBase*>& getTests() { return _tests; }

	virtual void init();
	virtual void deinit();
};

}

#endif /* UTESTTESTGROUP_H_ */
