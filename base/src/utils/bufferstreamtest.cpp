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

#include "bufferstreamtest.h"

#include <sstream>
#include <iostream>

#include "bufferstream.h"

#include "string_.h"
#include "buffer.h"

#include "block.h"
/*---------------------------------------------------------------------------*/

BufferStreamTest::BufferStreamTest()
  : EasyTest("BufferStreamTest","")
{
}

BufferStreamTest::~BufferStreamTest()
{
}

void BufferStreamTest::pre() throw(std::runtime_error)
{
}

void BufferStreamTest::run() throw(std::runtime_error)
{
  {
    utils::Buffer buf(100);
    utils::OBufferStream obs(buf);
    obs << 1 << "Hallo";
    obs.flush();
  
    utils::IBufferStream ibs(buf);
    int test;
    std::string str;
    ibs >> test >> str;

    if (test != 1 || str != "Hallo")
      {
	std::ostringstream msg;
	msg << "fehler: <" << str << "> != <Hallo> oder " << test << " != 1.";
	throw std::runtime_error(msg.str().c_str());
      }
  }

  {
    utils::Buffer buf(100);
    utils::OBufferStream obs(buf);

    obs << 5 << ' ' << utils::String("Das ist ein Test.") << ' ' 
	<< 1 << ' ' << 11;
    obs.flush();

    utils::IBufferStream ibs(buf);
    utils::String test("");
    int i, j,k;
    ibs >> i >> test >> j  >> k;

    if (test != utils::String("Das ist ein Test.") || i != 5 || j != 1
	|| k != 11)
      {
	std::ostringstream msg;
	msg << "fehler: <" << test << "> != <Das ist ein Test.> oder "
	    << i << " != 5 oder " << j << " != 1 oder " << k << " != 11.";
	throw std::runtime_error(msg.str().c_str());
      }

    // TODO: rewrite this test so that it does not need
    // the bufferutils
    /*    int index = 0;
    for (unsigned int u = 1; u < 1024*1024; u*=2)
      {
	++index;
	  {
	    std::cout << ".";
	    std::cout.flush();
	  }

	unsigned char* block = createRandomBlock(u);
	utils::Buffer quelle(block,u);
	delete[] block;
	utils::Buffer medium(u*2+100);
	utils::OBufferStream os(medium);
	
	os << quelle;
	os.flush();


	utils::IBufferStream is(medium);
	utils::Buffer ziel(u);
	is >> ziel;

	if (!compareBlocks(ziel.getPtr(),ziel.getLen(),
			   quelle.getPtr(),quelle.getLen()))
	  {
	    std::cerr << "u = " << u << std::endl;
	    std::cerr << ziel << std::endl;
	    std::cerr << quelle  << std::endl;
	    throw std::runtime_error("IBufferStream hat mist gebaut!");
	  }
          }*/
  }
}

void BufferStreamTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
