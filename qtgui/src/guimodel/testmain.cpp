
#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "actionsequencerwrappertest.h"

void doTests()
{
	CompositeTest AllTests("Utils Tests","");

	ActionSequencerWrapperTest aswt;
	AllTests.addTest(aswt);
 
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
