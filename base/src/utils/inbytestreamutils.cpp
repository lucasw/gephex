#include "inbytestreamutils.h"

#include "inbytestream.h"

#include "buffer.h"

namespace utils
{
  
  InByteStream& operator>>(InByteStream& s, int& i)
  {
    unsigned char* temp = reinterpret_cast<unsigned char*>(&i);

    for (unsigned int k = 0; k < sizeof(i) / sizeof(unsigned char); ++k)
      {
	temp[k] = s.get();
      }

    return s;
  }

  
  InByteStream& operator>>(InByteStream& s, double& d)
  {
    unsigned char* temp = reinterpret_cast<unsigned char*>(&d);

    for (unsigned int k = 0; k < sizeof(d) / sizeof(unsigned char); ++k)
      {
	temp[k] = s.get();
      }

    return s;
  }

  void readArray(InByteStream& s, int& size, unsigned char*& data)
  {
    s >> size;
    
    data = new unsigned char[size+1];
    for (int i = 0; i < size; ++i)
      data[i] = s.get();
  }

  InByteStream& operator>>(InByteStream& s, std::string& str)
  {
    int size;
    unsigned char* data;

    readArray(s,size,data);

    char* c_str = reinterpret_cast<char*>(data);
    c_str[size] = 0;

    str = std::string(c_str);

    delete[] data;

    return s;
  }

  InByteStream& operator>>(InByteStream& s, utils::Buffer& buf)
  {
    int size;
    unsigned char* data;

    readArray(s,size,data);

    buf = utils::Buffer(data,size);    

    delete[] data;
    return s;
  }
}
