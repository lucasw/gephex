#ifndef INCLUDED_BUFFER_STREAM_H
#define INCLUDED_BUFFER_STREAM_H

#include <iostream>

namespace utils
{

  class Buffer;

  /**
   * This is a std::istream that reads from a buffer.
   * (Similair to std::istrstream).
   */
  class IBufferStream : public std::istream
  {
    typedef std::istream inherited;

  public:
    IBufferStream(const Buffer&);

    virtual ~IBufferStream();
  };

  /**
   * This is a std::ostream that writes to a buffer.
   * (Similair to std::ostrstream).
   */
  class OBufferStream : public std::ostream
  { 
    typedef std::ostream inherited;

  public: 
    OBufferStream(Buffer&);

    virtual ~OBufferStream();
  };

}

#endif
