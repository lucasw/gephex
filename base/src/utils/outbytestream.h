#ifndef INCLUDED_OUT_BYTE_STREAM_H
#define INCLUDED_OUT_BYTE_STREAM_H

#include <vector>

//#include "buffer.h"

namespace utils
{

	class Buffer;

	/**
	 * Class for the output of binary data.
	 */

  class OutByteStream
  {
  public:
    OutByteStream();
    
	/**
	 * Puts a single byte into the stream.
	 * @param c the nyte that is written into the stream.
	 */
    void put(unsigned char c);

	/**
	 * Returns all written bytes.
	 * @return a buffer that contains all bytes that were written
	 *         into the stream.
	 */
    utils::Buffer getBuffer() const;

  private:
    std::vector<unsigned char> m_data;
  };

}
#endif
