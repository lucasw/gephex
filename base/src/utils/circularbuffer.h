#ifndef INCLUDED_CIRCULAR_BUFFER_H
#define INCLUDED_CIRCULAR_BUFFER_H

namespace utils
{
  class Buffer;

  /**
   * The circular buffer stores unsigned char data.
   * It supports two operations: push back n bytes and pop m bytes
   * from the front.
   *
   * pop_front is linear in the number of bytes.
   * push_back is linear if no resizing is needed.
   * If the buffer has to grow, pushing back n bytes costs
   * O(n log(n)).
   *
   * len and clear are constant time operations.
   */
  class CircularBuffer
  {
  public:
    /**
     * 
     */
    CircularBuffer();
    ~CircularBuffer();

    /**
     *
     */
    void push_back(const utils::Buffer& buf);

    /**
     * \throws std::invalid_argument if len > this->len().
     */
    Buffer pop_front(int len);

    /**
     *
     */
    int len() const;

    void clear();

  private:		
    int m_capacity;
    int m_begin;
    int m_end;
		
    unsigned char* m_data;
  };
}

#endif

