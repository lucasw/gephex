#ifndef INCLUDED_STREAM_LOGGER_H
#define INCLUDED_STREAM_LOGGER_H

#include <iosfwd>

#include "ilogger.h"

namespace utils
{

	/** 
	 * This is a logger that writes his log messages into any
	 * ostream.
	 */
class StreamLogger : public ILogger
{
public:

	/**
	 * Creates a new StreamLogger that writes to stream.
	 * @param stream The ostream into which the log messages are written
	 */
	StreamLogger(std::ostream& stream);

	void log(const std::string& sender, const std::string& msg);
	void warning(const std::string& sender, const std::string& msg);
	void error(const std::string& sender, const std::string& msg);

private:
	std::ostream& m_stream;
};

}

#endif
