#ifndef INCLUDED_OUT_BYTE_STREAM_UTILS_H
#define INCLUDED_OUT_BYTE_STREAM_UTILS_H

#include <string>

namespace utils
{
 /**
  * Functions for writing into a bytestream.
  */
  class OutByteStream;
  class Buffer;

  OutByteStream& operator<<(OutByteStream& s, int i);

  OutByteStream& operator<<(OutByteStream& s, double i);

  OutByteStream& operator<<(OutByteStream& s, const std::string& str);

  OutByteStream& operator<<(OutByteStream& s, const utils::Buffer& buf);
  
}

#endif
