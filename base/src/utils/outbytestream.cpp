#include "outbytestream.h"

#include "buffer.h"

namespace utils
{

 
  OutByteStream::OutByteStream()
  {
  }
  
  void OutByteStream::put(unsigned char c)
  {
    m_data.push_back(c);
  }
  
  utils::Buffer OutByteStream::getBuffer() const
  {
    if (!m_data.empty())
      return utils::Buffer(&m_data[0], m_data.size());
    else
      return utils::Buffer(reinterpret_cast<const unsigned char*>(""),1); //TODO!!!!
  }


}
