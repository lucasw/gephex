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

#include "taggertest.h"

#include <sstream>

#include "isender.h"
#include "itaginterpreter.h"
#include "tagger.h"
#include "tagutils.h"

#include "block.h"

#include "utils/buffer.h"
#include "utils/bufferutils.h"

namespace tagger_test {
class TestSender : public net::ISender
{
public:
  TestSender() : m_buf(0) {}

  void setListener(net::IDataListener& l)
  {
    m_listener = &l;
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

    m_listener->dataReceived(buf);

    return buf.getLen();
  }

  unsigned char* m_buf;
  int m_len;

private:
  net::IDataListener* m_listener;
};

template <typename Tag>
class TestInterpreter : public net::ITagInterpreter<Tag>
{
public:
  TestInterpreter() : m_data(0), m_len(0) {}
  virtual ~TestInterpreter()
  {
    delete[] m_data;
  }

  virtual void dataReceived(const Tag& tag,
			    const utils::Buffer& buf)
  {
    if (m_data != 0)
      delete[] m_data;

    m_data = new unsigned char[buf.getLen()];

    m_tag = tag;
    
    memcpy(m_data,buf.getPtr(),buf.getLen());
    m_len = buf.getLen();
  }

  Tag m_tag;
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

template <class Tag, class TagUtil>
static void test_tagutil(const Tag& t)
{
  TagUtil u;
  utils::Buffer b1;
  utils::Buffer b2;
  u.attachTag(b1, t, utils::Buffer());
  
  Tag v;
  u.removeTag(b2, v, b1);

  if (t != v)
    {
      std::ostringstream os;
      os << "Tag corrupt: '" << t << "' != '" << v << "'";
      throw std::runtime_error(os.str().c_str());
    }
}

template <class Tag, class TagUtil>
static void test_tagger(const Tag& t)
{
  tagger_test::TestSender sender;
  tagger_test::TestInterpreter<Tag> tip;
  net::Tagger<Tag, TagUtil> tg(tip);

  tg.registerSender(sender);
  sender.setListener(tg);

  for (int len = 0; len < 4098; ++len)
    {
      unsigned char* data = createRandomBlock(len);
      tg.setTag(t);
      tg.send(utils::Buffer(data,len));
	
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

void TaggerTest::pre() throw(std::runtime_error)
{

}

void TaggerTest::run() throw(std::runtime_error)
{
  test_tagutil<std::string, net::StringTagUtil>("harr harr horr");
  test_tagutil<uint_32, net::UInt32TagUtil>(192837465);

  test_tagger<std::string, net::StringTagUtil>("1111");
  test_tagger<uint_32, net::UInt32TagUtil>(1111);
}

void TaggerTest::post() throw(std::runtime_error)
{
}
