#include "outbytestreamutils.h"

#include "outbytestream.h"

#include "buffer.h"

namespace utils 
{

  OutByteStream& operator<<(OutByteStream& s, int i)
  {
    const unsigned char* t = reinterpret_cast<const unsigned char*>(&i);
    
    for (unsigned int k = 0; k < sizeof(i) / sizeof(unsigned char); ++k)
      {
	s.put(t[k]);
      }

    return s;
  }

  OutByteStream& operator<<(OutByteStream& s, double d)
  {
    const unsigned char* t = reinterpret_cast<const unsigned char*>(&d);
    
    for (unsigned int k = 0; k < sizeof(d) / sizeof(unsigned char); ++k)
      {
	s.put(t[k]);
      }

    return s;
  }

  static void putArray(OutByteStream& s, const unsigned char* data, int len)
  {
    s << len;

    for (int i = 0; i < len; ++i)
      s.put(data[i]);
  }

  OutByteStream& operator<<(OutByteStream& s, const std::string& str)
  {
    const unsigned char* 
      buffer = reinterpret_cast<const unsigned char*>(str.c_str());
    
    putArray(s,buffer,str.size());
    
    return s;
  }

  OutByteStream& operator<<(OutByteStream& s, const utils::Buffer& buf)
  {
    putArray(s,buf.getPtr(), buf.getLen());

    return s;
  }
}
