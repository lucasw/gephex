#include <iostream>

#include "../TestFramework/CompositeTest.h"
#include "../TestFramework/Tester.h"
#include "threadtest.h"



void doTests()
{
	CompositeTest AllTests("Thread Tests","");

	ThreadTest tt;
	AllTests.addTest(tt);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
