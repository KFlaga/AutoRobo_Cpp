#include "UTestTestManager.h"
#include <stdio.h>

using namespace UTest;

TestManager::TestManager()
{
	_newLine = "\n";
}

TestManager::~TestManager()
{

}

void TestManager::addTestGroup(TestGroup* group)
{
	_testGroups.push_back(group);
}

void TestManager::runAllTests()
{
	for(auto group : _testGroups)
	{
		group->runAllTests();
	}
}

void TestManager::printResults()
{
	printResults([](const char* str)-> void
	{
		printf(str);
	});
}

void TestManager::printResults(PrintFunc printFunc)
{
	// Print layout:
	//
	// Test Results:
	//   Group : [group_name]
	//     Test : [test_name] -> [test_result]

	printFunc("Test Results:");
	printFunc(_newLine);

	for(auto group : _testGroups)
	{
		printFunc("  Group : ");
		printFunc(group->getName());
		printFunc(_newLine);

		for(auto test : group->getTests())
		{
			printFunc("    Test : ");
			printFunc(test->getName());
			printFunc(" -> ");
			switch(test->getResult())
			{
				case TestBase::TestResult::Failed :
					printFunc("Failed");
					break;
				case TestBase::TestResult::Passed :
					printFunc("Passed");
					break;
				case TestBase::TestResult::NotRun :
				default:
					printFunc("Not Run");
					break;
			}
			printFunc(_newLine);
		}
	}
}

