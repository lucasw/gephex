#include "streamlogger.h"

#include <iostream>

namespace utils
{

StreamLogger::StreamLogger(std::ostream& stream)
 : m_stream(stream)
{
}

static std::string getTime()
{
	return "0";
}

void StreamLogger::log(const std::string& sender, const std::string& msg)
{
	std::string zeit = getTime();
	
	m_stream << "[" << zeit << "] (Log from " << sender << "): " << msg;
}

void StreamLogger::warning(const std::string& sender, const std::string& msg)
{
	std::string zeit = getTime();
	
	m_stream << "[" << zeit << "] (Warning from " << sender << "): " << msg;
}

void StreamLogger::error(const std::string& sender, const std::string& msg)
{
	std::string zeit = getTime();
	
	m_stream << "[" << zeit << "] (Error from " << sender << "): " << msg;
}

}
