#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"

#include "graphparsertest.h"

void doTests()
{
	CompositeTest AllTests("Alle Tests","");

	GraphParserTest gpt;
	AllTests.addTest(gpt);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{
  doTests();
  return 0;
}
