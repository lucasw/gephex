#ifndef INCLUDED_ISENDER_H
#define INCLUDED_ISENDER_H

#include <stdexcept>

namespace utils {
  class Buffer;
}

namespace net
{

  /**
   * Abstract base class for all classes that can send data.
   *
   * @see IDataListener
   */

  class ISender
    {
    public:

      /**
       * Sends some data.
       * @param buf the data that is sent.
       */
      virtual int send(const utils::Buffer& buf) = 0;
    };
  
} //end of namespace

#endif
