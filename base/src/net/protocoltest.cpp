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

void ProtocolTest::run() throw(std::runtime_error)
{
  protocol_test::TestSender sender;
  protocol_test::TestInterpreter tip;
  net::Protocol np(tip);

  np.registerSender(sender);
  sender.setProtocol(np);

  for (int len = 0; len < 4098; ++len)
    {
      unsigned char* data = createRandomBlock(len);
      np.send(utils::Buffer(data,len));
	
      if (!compareBlocks(data,len,tip.m_data,tip.m_len))
	{
	  std::cerr << "len = " << len << std::endl;
	  std::cerr << "m_len = " << tip.m_len << std::endl;
	  throw std::runtime_error("Da ist nicht das Richtige"
				   " beim Richtigen ankegommen hier.");
	}
      delete[] data;

      if (len % 128 == 0)
	{
	  std::cerr << ".";
	  std::cerr.flush();
	}

    }
}

void ProtocolTest::post() throw(std::runtime_error)
{
}
