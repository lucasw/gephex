#ifndef INCLUDED_IN_BYTE_STREAM_UTILS_H
#define INCLUDED_IN_BYTE_STREAM_UTILS_H

#include <string>

namespace utils
{
  class InByteStream;
  class Buffer;

  InByteStream& operator>>(InByteStream& s, int& i);

  InByteStream& operator>>(InByteStream& s, double& d);

  InByteStream& operator>>(InByteStream& s, std::string& str);

  InByteStream& operator>>(InByteStream& s, utils::Buffer& buf);
}

#endif
