
#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"

void doTests()
{
	CompositeTest AllTests("Utils Tests","");
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
