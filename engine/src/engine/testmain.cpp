#include <iostream>
#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "schedulertest.h"


void doTests()
{
	CompositeTest AllTests("Engine Tests","");

	SchedulerTest st;
	AllTests.addTest(st);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
