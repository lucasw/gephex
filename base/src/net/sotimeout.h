#ifndef INCLUDED_SO_TIMEOUT_H
#define INCLUDED_SO_TIMEOUT_H

namespace net {

  /**
   * This class is inherited by all socket classes and
   * provides the timeout methods.
   */
  class SOTimeout
    {
    public:
      SOTimeout();
      
      /**
       * Enable/disable SO_TIMEOUT with the specified timeout
       * (in milliseconds).
       * If timeout is > 0, a call to receive() for 
       * this UDPSocket will block only for timeout ms. 
       * The option must be enabled prior to entering the blocking operation 
       * to have effect. 
       * The timeout must be >= -1. A timeout of -1 is interpreted as an 
       * infinite timeout. A timeout of 0 leads to non-blocking operation
       * If not set, the SO_TIMEOUT defaults to -1.
       */
      void setSoTimeout(int timeout);
      
      /**
       * Get the SO_TIMEOUT (see above).
       */
      int soTimeout() const;
      
    protected:
      int m_timeout;
  };
}
#endif
