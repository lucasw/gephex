#include "bufferedsender.h"

#include "utils/buffer.h"
#include "utils/circularbuffer.h"

BufferedSender::BufferedSender()
: m_buffer(new utils::CircularBuffer()), m_enabled(false)
{
   
}

BufferedSender::~BufferedSender()
{
}

void BufferedSender::disable()
{
  m_buffer->clear();
  m_enabled = false;
}

void BufferedSender::enable()
{
	m_enabled = true;
}

int BufferedSender::send(const utils::Buffer& buf)
{
	if (m_enabled)
	    m_buffer->push_back(buf);

	return buf.getLen();
}

/**
 *
 */
int BufferedSender::len() const
{
	return m_buffer->len();
}

/**
 *
 */
utils::Buffer BufferedSender::consume(int num_bytes)
{
	return m_buffer->pop_front(num_bytes);
}
