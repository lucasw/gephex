#include <iostream>


#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "protocoltest.h"
#include "tcpsockettest.h"
#if defined(OS_POSIX)
#include "domainsockettest.h"
#endif
#if defined(OS_WIN32)
#include "namedpipesockettest.h"
#endif
#include "taggertest.h"
#include "tagdispatchertest.h"


void doTests()
{
	CompositeTest AllTests("Net Tests","");

	TaggerTest tt;
	AllTests.addTest(tt);

	ProtocolTest pt;
	AllTests.addTest(pt);

	TCPSocketTest tcpst;
	AllTests.addTest(tcpst);

#if defined(OS_POSIX)
	DomainSocketTest domst;
	AllTests.addTest(domst);
#endif

#if defined(OS_WIN32)
	NamedPipeSocketTest npst;
	AllTests.addTest(npst);
#endif

	TagDispatcherTest tdt;
	AllTests.addTest(tdt);

	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv*/[])
{
  doTests();

  return 0;
}
