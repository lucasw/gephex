/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/


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
#include "bufferstreamtest.h"
#include "sharedlibrarytest.h"
#include "circularbuffertest.h"
#include "xmlutilstest.h"

void doTests()
{
	CompositeTest AllTests("Utils Tests","");

        XmlutilsTest xut;
        AllTests.addTest(xut);

	SharedLibraryTest slt;
	AllTests.addTest(slt);
	
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

	BufferTest bt;
	AllTests.addTest(bt);

	AutoPtrTest apt;
	AllTests.addTest(apt);

	BufferStreamTest bufst;
	AllTests.addTest(bufst);

	CircularBufferTest cbtst;
	AllTests.addTest(cbtst);
	
	TesterStream ts(std::cout);
	AllTests.action(ts);
}

int main(int /*argc*/,char* /*argv[]*/)
{


  doTests();

  return 0;
}
