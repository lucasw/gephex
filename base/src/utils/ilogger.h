#ifndef INCLUDED_ILOGGER_H
#define INCLUDED_ILOGGER_H

#include <string>

namespace utils
{

	/**
	* Abstract base class for logging services.
	*/

class ILogger
{
public:

	/**
	 * Produces a log message.
	 * @param sender the producer of the message
	 * @param msg the message text
	 */
	virtual void log(const std::string& sender, const std::string& msg) = 0;

	/**
	 * Produces a warning message.
	 * @param sender the producer of the message
	 * @param msg the message text
	 */
	virtual void warning(const std::string& sender, const std::string& msg) = 0;

	/**
	 * Produces a error message.
	 * @param sender the producer of the message
	 * @param msg the message text
	 */
	virtual void error(const std::string& sender, const std::string& msg) = 0;
};

}

#endif
