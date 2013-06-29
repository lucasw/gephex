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
