#include "domainsockettest.h"
#include "idatalistener.h"

#include "isocket.h"
#include "domainserversocket.h"
#include "domainclientsocket.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "block.h"

#include "utils/buffer.h"

std::string DomainSocketTest::getName() const
{
	return "DomainSocketTest";
}

std::string DomainSocketTest::getDescription() const
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

void DomainSocketTest::pre() throw(std::runtime_error)
{
}

void DomainSocketTest::run() throw(std::runtime_error)
{

  net::DomainServerSocket server("/tmp/test_",1234);
  net::DomainClientSocket client;

  net::ISocket* sock1;
  net::ISocket* sock2;

  server.listen();

  sock2 = client.connect("/tmp/test_",1234);

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

  delete sock1;
  delete sock2;
}

void DomainSocketTest::post() throw(std::runtime_error)
{
}



 

