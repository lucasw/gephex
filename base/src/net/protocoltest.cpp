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

#include "protocoltest.h"

#include "isender.h"
#include "protocol.h"
#include "block.h"

#include "utils/buffer.h"


namespace protocol_test {
class TestSender : public net::ISender
{
public:
  TestSender() : m_buf(0) {}

  void setProtocol(net::Protocol& _np)
  {
    np = &_np;
  }

  virtual ~TestSender()
  {
    delete[] m_buf;
  }

  virtual int send(const utils::Buffer& buf)
  {
    /*    if (m_buf != 0)
      delete[] m_buf;

    m_buf = new char[len];
    memcpy(m_buf,buf,len);
    m_len = len;*/

    int len = buf.getLen();

    static const int PACKET_SIZE = 33;

    int packets = len / PACKET_SIZE;

    for (int p = 0; p < packets; ++p)      
      {
	utils::Buffer packet(buf.getPtr() + p*PACKET_SIZE, PACKET_SIZE);
	np->dataReceived(packet);
      }

    int rest = len - packets*PACKET_SIZE;
    if (rest != 0 || len == 0)
      {
	utils::Buffer lastPacket(buf.getPtr() + packets*PACKET_SIZE, rest);
	np->dataReceived(lastPacket);
      }


    return buf.getLen();
  }

  unsigned char* m_buf;
  int m_len;

private:
  net::Protocol* np;
};


class TestSender2 : public net::ISender
{
public:
  TestSender2() {}
  
  virtual int send(const utils::Buffer& buf)
  {
    m_buf = buf;
	return buf.getLen();
  }

  utils::Buffer m_buf;
};

class TestInterpreter : public net::IDataListener
{
public:
  TestInterpreter() :  m_data(0), m_len(0) {}
  virtual ~TestInterpreter()
  {
    delete[] m_data;
  }

  virtual void dataReceived(const utils::Buffer& buf)
  {
    if (m_data != 0)
      delete[] m_data;

    m_data = new unsigned char[buf.getLen()];
    
    memcpy(m_data,buf.getPtr(),buf.getLen());
    m_len = buf.getLen();
  }

  unsigned char* m_data;
  int m_len;
};
}

std::string ProtocolTest::getName() const
{
  return "Protocol";
}

std::string ProtocolTest::getDescription() const
{
  return "";
}

void ProtocolTest::pre() throw(std::runtime_error)
{

}

static void test1()
{
	protocol_test::TestSender sender;
	protocol_test::TestInterpreter tip;
	net::Protocol np(tip);
	
	np.registerSender(&sender);
	sender.setProtocol(np);
	
	for (int len = 0; len < 4098; ++len)
    {
		unsigned char* data = createRandomBlock(len);
		np.send(utils::Buffer(data,len));
		
		if (!compareBlocks(data,len,tip.m_data,tip.m_len))
		{
			std::cerr << "len = " << len << std::endl;
			std::cerr << "m_len = " << tip.m_len << std::endl;
			throw std::runtime_error("Wrong data received.");
		}
		delete[] data;
		
		if (len % 128 == 0)
		{
			std::cerr << ".";
			std::cerr.flush();
		}
		
    }
}

static void test2()
{
	protocol_test::TestInterpreter tip;
	protocol_test::TestSender2 sender;
	net::Protocol np(tip);

	np.registerSender(&sender);	

	utils::Buffer buf;
	np.send(utils::Buffer((unsigned char*)"Hallo", strlen("Hallo")+1));
	buf += sender.m_buf;
	np.send(utils::Buffer((unsigned char*)"Test", strlen("Test")+1));
	buf += sender.m_buf;

	unsigned char* ptr = new unsigned char[buf.getLen()];
	memcpy(ptr, buf.getPtr(), buf.getLen());

	unsigned int* header_thingy = (unsigned int*) ptr;
	*header_thingy += 7;

	utils::Buffer mod_buf(ptr, buf.getLen());
	delete[] ptr;

	np.dataReceived(mod_buf);

    const char* text = (const char*) tip.m_data;
	if (strcmp(text, "Test") != 0)
		throw std::runtime_error("sync failed");
}

void ProtocolTest::run() throw(std::runtime_error)
{
   test1();
   test2(); 
}

void ProtocolTest::post() throw(std::runtime_error)
{
}
