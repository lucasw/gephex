#include "netexceptions.h"

namespace net
{


  IOException::IOException(const std::string& text)
    : std::runtime_error(text.c_str())
  {
  }

  InterruptedIOException::InterruptedIOException(const std::string& text)
    : std::runtime_error(text.c_str())
  {
  }

  SocketException::SocketException(const std::string& text)
    : std::runtime_error(text.c_str())
  {
  }

  UnknownHostException::UnknownHostException(const std::string& text)
    : std::runtime_error(text.c_str())
  {
  }

  BrokenPipeException::BrokenPipeException(const std::string& text)
    : std::runtime_error(text.c_str())
  {
  }

} // end of namesapce net
