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

#include "tagdispatchertest.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "tagdispatcher.h"
#include "idatalistener.h"
#include "block.h"

#include "utils/buffer.h"

std::string TagDispatcherTest::getName() const
{
	return "TagDispatcherTest";
}

std::string TagDispatcherTest::getDescription() const
{
	return "Ein bedeutender Test";
}

class TestListener : public net::IDataListener
{
public:
  TestListener() {}

  virtual ~TestListener() {}

  void dataReceived(const utils::Buffer& buf)
  {
    m_buf = buf;
  }

  utils::Buffer buffer() const
  {
    return m_buf;
  }

private:
  utils::Buffer m_buf;
};

void TagDispatcherTest::pre() throw(std::runtime_error)
{
}

void TagDispatcherTest::run() throw(std::runtime_error)
{

  net::TagDispatcher<int> dispatcher;

  TestListener tl0;
  TestListener tl100;

  dispatcher.registerListener(0, tl0);
  dispatcher.registerListener(100, tl100);

  bool exceptionThrown = false;

  try {
    dispatcher.dataReceived(10, utils::Buffer((unsigned char*) "Hallo",6));
  }
  catch(...) {
    exceptionThrown = true;
  }

  if (!exceptionThrown) {
    throw std::runtime_error("dispatcher did not throw an exception "
			     "when a taglistener was missing");
  }
  
  for (int len = 1; len <= 1024; len += 1)
    {
      unsigned char* data = createRandomBlock(len);

      dispatcher.dataReceived(0, utils::Buffer(data,len));
  
      utils::Buffer buf = tl0.buffer();
      if (!compareBlocks(data,len,buf.getPtr(),buf.getLen()))
	{
	  std::ostringstream os;
	  os << "Falsche Daten. len = " << len << "." << std::endl;
	  //	  printBlock(os,data,len);
	  os << std::endl;
	  //	  printBlock(os,buf.getPtr(),buf.getLen());
	  os << len << "," << buf.getLen() << std::endl;
	  std::string msg = os.str();
	  throw std::runtime_error(msg.c_str());
	}

      data = createRandomBlock(len);

      dispatcher.dataReceived(100, utils::Buffer(data,len));
  
      buf = tl100.buffer();
      if (!compareBlocks(data,len,buf.getPtr(),buf.getLen()))
	{
	  std::ostringstream os;
	  os << "Falsche Daten. len = " << len << "." << std::endl;
	  //	  printBlock(os,data,len);
	  os << std::endl;
	  //	  printBlock(os,buf.getPtr(),buf.getLen());
	  os << len << "," << buf.getLen() << std::endl;
	  std::string msg = os.str();
	  throw std::runtime_error(msg.c_str());
	}

      if (len % 128 == 0)
	{
	  std::cerr << ".";
	  std::cerr.flush();
	}

      delete[] data;
    }

}

void TagDispatcherTest::post() throw(std::runtime_error)
{
}
