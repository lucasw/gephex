#ifndef INCLUDED_BUFFERED_SENDER_H
#define INCLUDED_BUFFERED_SENDER_H

#include <memory>

#include "isender.h"

namespace utils
{
	class Buffer;
	class CircularBuffer;
}

/**
 * The BufferedSender can be disabled, in which case it ignores all data
 * that is sent or enabled, in which case it stores all data.
 *
 * When created it is disabled.
 */
class BufferedSender : public net::ISender
{
public:
	BufferedSender();
	virtual ~BufferedSender();

	void disable();
	void enable();

	int send(const utils::Buffer& buf);

	/**
	 *
	 */
	int len() const;

	/**
	 *
	 */
	utils::Buffer consume(int num_bytes);

private:
	std::auto_ptr<utils::CircularBuffer> m_buffer;
    bool m_enabled;
};

#endif
