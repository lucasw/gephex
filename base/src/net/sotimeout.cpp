#include "sotimeout.h"

namespace net {

  SOTimeout::SOTimeout()
    : m_timeout(-1)
  {
  }

  void SOTimeout::setSoTimeout(int timeout)
  {
    m_timeout = timeout;
  }

  int SOTimeout::soTimeout() const
  {
    return m_timeout;
  }

}
