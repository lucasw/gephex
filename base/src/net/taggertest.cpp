#include "taggertest.h"

#include "isender.h"
#include "itaginterpreter.h"
#include "tagger.h"
#include "tagutils.h"

#include "block.h"

#include "utils/buffer.h"
#include "utils/bufferutils.h"

namespace net {
  typedef Tagger<std::string, StringTagUtil> Tagger_;
  typedef ITagInterpreter<std::string> ITagInterpreter_;
}

namespace tagger_test {
class TestSender : public net::ISender
{
public:
  TestSender() : m_buf(0) {}

  void setTagger(net::Tagger_& _tg)
  {
    tg = &_tg;
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

    /*int len = buf.getLen();

    static const int PACKET_SIZE = 33;

    int packets = len / PACKET_SIZE;

    for (int p = 0; p < packets; ++p)      
      {
	utils::Buffer packet(buf.getPtr() + p*PACKET_SIZE, PACKET_SIZE);
	tg->dataReceived(packet);
      }

    int rest = len - packets*PACKET_SIZE;
    if (rest != 0 || len == 0)
      {
	utils::Buffer lastPacket(buf.getPtr() + packets*PACKET_SIZE, rest);
	tg->dataReceived(lastPacket);
	}*/

    tg->dataReceived(buf);


    return buf.getLen();
  }

  unsigned char* m_buf;
  int m_len;

private:
  net::Tagger_* tg;
};

class TestInterpreter : public net::ITagInterpreter_
{
public:
  TestInterpreter() : m_command(), m_data(0), m_len(0) {}
  virtual ~TestInterpreter()
  {
    delete[] m_data;
  }

  virtual void dataReceived(const std::string& command,
			    const utils::Buffer& buf)
  {
    if (m_data != 0)
      delete[] m_data;

    m_data = new unsigned char[buf.getLen()];

    m_command = command;
    
    memcpy(m_data,buf.getPtr(),buf.getLen());
    m_len = buf.getLen();
  }

  std::string m_command;
  unsigned char* m_data;
  int m_len;
};
}

std::string TaggerTest::getName() const
{
  return "Tagger";
}

std::string TaggerTest::getDescription() const
{
  return "";
}

void TaggerTest::pre() throw(std::runtime_error)
{

}

void TaggerTest::run() throw(std::runtime_error)
{
  tagger_test::TestSender sender;
  tagger_test::TestInterpreter tip;
  net::Tagger_ tg(tip);

  tg.registerSender(sender);
  sender.setTagger(tg);

  for (int len = 0; len < 4098; ++len)
    {
      unsigned char* data = createRandomBlock(len);
      tg.setTag("1111");
      tg.send(utils::Buffer(data,len));
	
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

void TaggerTest::post() throw(std::runtime_error)
{
}
