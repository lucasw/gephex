#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
//#include "modeltest.h"
//#include "datatreetest.h"

void doTests()
{
	CompositeTest AllTests("Alle Tests","");

	/*ModelTest mt;
	AllTests.addTest(mt);*/

	//DataTreeTest dtt;
	//AllTests.addTest(dtt);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{
  doTests();
  return 0;
}
