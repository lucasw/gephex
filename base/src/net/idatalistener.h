#ifndef INCLUDED_IDATA_LISTENER_H
#define INCLUDED_IDATA_LISTENER_H

namespace utils {
  class Buffer;
}

namespace net
{

  /**
   * Abstract base class for all classes that can receive data.
   *
   * @see ISender
   */
  class IDataListener
  {
  public:
    
    /**
     * Is called when data has been received.
     * @param buf the actual data
     */
    virtual void dataReceived(const utils::Buffer& buf) = 0;
  };
  
} //end of namespace

#endif

