#ifdef WIN32
#pragma warning( disable : 4786 )  
#endif 

#include <iostream>

#include "testframework/compositetest.h"
#include "testframework/tester.h"
#include "sequencertest.h"

void doTests()
{
	CompositeTest AllTests("Utils Tests","");

	SequencerTest test;
	AllTests.addTest(test);

	TesterStream ts(std::cout);
	AllTests.action(ts);

}

int main(int /*argc*/,char* /*argv[]*/)
{

  doTests();

  return 0;
}


