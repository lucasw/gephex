#include "bufferutils.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <cassert>

#include "buffer.h"
#include "xmlutils.h"

namespace utils
{

  namespace
  {
    inline char hex2int (char hex)
    {
      if (hex >= '0' && hex <= '9')
	return hex - '0';
      else if (hex >= 'a' && hex <= 'f')
	return hex - 'a' + 0xa;
      else
	    throw std::runtime_error("no hexcode (utils::hex2int()");
    }
  }
  
  std::istream& operator>>(std::istream& s, Buffer& buf)
  {
    checktag(s,"<buf>");
    checktag(s,"<l>");
    int length; // bufferlength
    s >> length;
    checktag(s,"</l>");
    checktag(s,"<d>");
    //for (const char* i = buf.getPtr();i!=buf.getPtr()+ buf.getLen();++i)
    char* tempData = new char[length*2];
    if (!s.read(tempData,length*2))
      {
	delete[] tempData;
	throw std::runtime_error("could not read buffer at "
				 "std::istream& operator>>(std::istream& s, "
				 "Buffer& buf)");
      }

    unsigned char* data = new unsigned char[length];
    int index = length-1;
    for (unsigned char* d = data+length-1; index >= 0; --index, --d)
      {
	char hihex = tempData[index<<1];
	char lowhex = tempData[(index<<1) + 1];

	*d = (hex2int(hihex)<<4)|(hex2int(lowhex));
      }
    delete[] tempData;
    checktag(s,"</d>");
    checktag(s,"</buf>");

    //buf.setData(data,length); // save the data in the buffer
    buf = Buffer(data,length);
    delete[] data; // delete temp object

    return s;
  } 	


  std::ostream& operator<<(std::ostream& s, const Buffer& buf)
  {
    int len = buf.getLen();
    s << "<buf>";
    s << "<l>" << len << "</l>";
    s << "<d>";
    char* tempData = new char[len * 2];

    int index = len-1;
    for (const unsigned char* d = buf.getPtr() + len - 1;
	 index >= 0; --d, --index)
      {
	static const char* char2hex = "0123456789abcdef";
	const char value = *d;
	tempData[index<<1]   = char2hex[(value >> 4) & 15];
	tempData[(index<<1) +1] = char2hex[value & 15];
	  //	s.put(char2hex[(value >> 4) & 15]);
	  //	s.put(char2hex[value & 15]);
      }
    s.write(tempData,len*2);
    s << "</d>";
    s << "</buf>";

    delete[] tempData;
    return s;
  }

}
