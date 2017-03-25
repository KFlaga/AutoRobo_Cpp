#ifndef UTESTTESTRUNNER_H_
#define UTESTTESTRUNNER_H_

#include "UTestTestGroup.h"

namespace UTest
{
	class TestManager
	{
	public:
		static TestManager* getInstance()
		{
			static TestManager instance; // Works well for intended usage
			return &instance;
		}

	private:
		std::vector<TestGroup*> _testGroups;
		const char* _newLine;

	private:
		TestManager();

	public:
		~TestManager();

		void addTestGroup(TestGroup* group);

		void runAllTests();

		typedef void(*PrintFunc)(const char* str);

		void setNewLineString(const char* newLineStr)
		{
			_newLine = newLineStr;
		}

		// Prints results using 'printf'
		void printResults();

		void printResults(PrintFunc printFunc);

		std::vector<TestGroup*>& getTestGroups()
		{
			return _testGroups;
		}
	};
}

#endif /* UTESTTESTRUNNER_H_ */
