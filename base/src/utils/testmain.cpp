
#include <iostream>

#include "TestFramework/CompositeTest.h"
#include "TestFramework/Tester.h"
#include "stringtokenizertest.h"
#include "streamtokenizertest.h"
#include "structscannertest.h"
#include "filesystemtest.h"
#include "structreadertest.h"
#include "buffertest.h"
#include "autoptrtest.h"
#include "bytestreamtest.h"
#include "bufferstreamtest.h"
#include "sharedlibrarytest.h"


void doTests()
{
	CompositeTest AllTests("Utils Tests","");

	SharedLibraryTest slt;
	AllTests.addTest(slt);
	
	StringTokenizerTest stt;
	AllTests.addTest(stt);

	StreamTokenizerTest stt_;
	AllTests.addTest(stt_);

	StructScannerTest ssc;
	AllTests.addTest(ssc);

	/*	FileSystemTest fst;
		AllTests.addTest(fst);*/

	StructReaderTest srt;
	AllTests.addTest(srt);

	BufferTest bt;
	AllTests.addTest(bt);

	AutoPtrTest apt;
	AllTests.addTest(apt);

	ByteStreamTest bst;
	AllTests.addTest(bst);

	BufferStreamTest bufst;
	AllTests.addTest(bufst);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
