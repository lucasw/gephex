#include <iostream>

#include "../TestFramework/CompositeTest.h"
#include "../TestFramework/Tester.h"

#include "loadmoduletest.h"


void doTests()
{
	CompositeTest AllTests("DllLoader Tests","");

	
	LoadModuleTest lmt;
	AllTests.addTest(lmt);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{
  doTests();
  return 0;
}
