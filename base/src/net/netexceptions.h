#ifndef INCLUDED_NET_EXCEPTIONS_H
#define INCLUDED_NET_EXCEPTIONS_H

#include <stdexcept>

namespace net
{

class IOException : public std::runtime_error
{
public:
  IOException(const std::string& text);
};

class InterruptedIOException : public std::runtime_error
{
public:
  InterruptedIOException(const std::string& text);
};

class SocketException : public std::runtime_error
{
public:
  SocketException(const std::string& text);

};

class UnknownHostException : public std::runtime_error
{
public:
  UnknownHostException(const std::string& text);
};


} // end of namespace net

#endif
