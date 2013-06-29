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

#include "namedpipesockettest.h"
#include "idatalistener.h"

#include "isocket.h"
#include "namedpipeserversocket.h"
#include "namedpipeclientsocket.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "block.h"

#include "utils/buffer.h"

std::string NamedPipeSocketTest::getName() const
{
	return "NamedPipeSocketTest";
}

std::string NamedPipeSocketTest::getDescription() const
{
	return "Ein bedeutender Test";
}

class TestDataListener : public net::IDataListener
{
public:
	TestDataListener() : m_data(0), m_len(0), _ready(false) {}

	void dataReceived(const utils::Buffer& buf)
	{
		delete[] m_data;
		m_len = buf.getLen();;
		m_data = new char[m_len];

		memcpy(m_data,buf.getPtr(),m_len);

		_ready = true;
	}

  bool isReady() { return _ready; }
  void reset() { _ready = false; }

  char* m_data;
  int m_len;

private:
  bool _ready;
};

void NamedPipeSocketTest::pre() throw(std::runtime_error)
{
}

void NamedPipeSocketTest::run() throw(std::runtime_error)
{

  net::NamedPipeServerSocket server(1234);
  net::NamedPipeClientSocket client;

  net::ISocket* sock1;
  net::ISocket* sock2;

  server.listen();

  sock2 = client.connect(".",1234);

  //  std::cout << "Na los, ich warte!" << std::endl;

  //  while (!sock1->connected())
    {
      sock1 = server.accept();  
    }

  //  assert(client.connected());
  //  std::cout << "verbunden!!" << std::endl;

    //  sock1->setSoTimeout(0);
    //  sock2->setSoTimeout(0);

  
  for (int len = 1; len <= 1024; len += 1)
    {
      unsigned char* data = createRandomBlock(len);
      sock2->send(utils::Buffer(data,len));

      utils::Buffer buf;

      sock1->receive(buf);
  
      if (!compareBlocks(data,len,buf.getPtr(),buf.getLen()))
	{
	  std::ostringstream os;
	  os << "Wrong data. len = " << len << "." << std::endl;
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

  delete sock1;
  delete sock2;
}

void NamedPipeSocketTest::post() throw(std::runtime_error)
{
}



 

