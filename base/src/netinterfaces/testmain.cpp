
#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "classinfotest.h"
#include "nodelcontrolreceivertest.h"


void doTests()
{
	CompositeTest AllTests("Utils Tests","");

	ClassInfoTest cit;
	AllTests.addTest(cit);

	NodelControlReceiverTest ncrt;
	AllTests.addTest(ncrt);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
