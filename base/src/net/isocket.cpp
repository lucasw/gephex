#include "isocket.h"

namespace net {
  ISocket::ISocket(int localPort)
    : m_localPort(localPort)
  {
  }

  ISocket::~ISocket() {}

  int ISocket::localPort() const
  {
    return m_localPort;
  }
}
