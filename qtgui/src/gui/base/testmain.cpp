
#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "keytest.h"


void doTests()
{
	CompositeTest AllTests("Gui Base Tests","");

	KeyTest kt;
	AllTests.addTest(kt);

	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
