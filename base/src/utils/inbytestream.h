#ifndef INCLUDED_IN_BYTE_STREAM_H
#define INCLUDED_IN_BYTE_STREAM_H

namespace utils
{

  class Buffer;

  /** 
   * Stream for reading binary data
   */

  class InByteStream
  {
  public:
	/** 
	  * Creates a new Stream that reads from a Buffer.
	  * @param b the Buffer that is read.
	  */
    InByteStream(const utils::Buffer& b);

	/**
	 * Destroys the stream.
	 */
    ~InByteStream();

	/**
	 * Are there any more bytes to read?
	 * @return true if there are some bytes left, false otherwise
	 */
    bool hasMore() const;

	/**
	 * Returns the next Byte. If !hasMore(), the behaviour is undefined.
	 * @return the next byte of the stream
	 */
    unsigned char get();

	/**
	 * Puts the last Byte back into the stream.
	 * If no Byte has been read the behaviour is undefined.
	 * If unget() has been called before and no get() has been
	 * called in between, the behaviour is undefined.
	 */
    void unget();

  private:
    unsigned char* begin;
    unsigned char* end;
    unsigned char* current;
  };

}
#endif
