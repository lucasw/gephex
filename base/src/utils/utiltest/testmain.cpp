
#include <iostream>
#include <conio.h>

#include "../TestFramework/CompositeTest.h"
#include "../TestFramework/Tester.h"
#include "stringtokenizertest.h"
#include "streamtokenizertest.h"
#include "structscannertest.h"
#include "filesystemtest.h"
#include "structreadertest.h"
//#include "xmllistenertest.h"
//#include "xmlscannertest.h"
//#include "xmlreadertest.h"


void doTests()
{
	CompositeTest AllTests("Utils Tests","");

	StringTokenizerTest stt;
	AllTests.addTest(stt);

	StreamTokenizerTest stt_;
	AllTests.addTest(stt_);

	StructScannerTest ssc;
	AllTests.addTest(ssc);

	FileSystemTest fst;
	AllTests.addTest(fst);

	StructReaderTest srt;
	AllTests.addTest(srt);
	
	/*XMLListenerTest xmllt;
	AllTests.addTest(xmllt);

	XMLScannerTest xmlst;
	AllTests.addTest(xmlst);

	XMLReaderTest xmlrt;
	AllTests.addTest(xmlrt);*/

	TesterStream ts(std::cout);
	AllTests.action(ts);

}

int main(int /*argc*/,char* /*argv[]*/)
{

  doTests();

  getch();
  return 0;
}
