#include "netlogger.h"

#include <iostream>

#include "interfaces/ierrorreceiver.h"

namespace engine
{
	NetLogger::NetLogger(IErrorReceiver& ier)
		: m_receiver(ier)
	{
	}

	void NetLogger::log(const std::string& sender, const std::string& msg)
	{
		std::cerr<<msg<<std::endl;
		m_receiver.exceptionThrown(msg);
	}

	void NetLogger::warning(const std::string& sender, const std::string& msg)
	{
		std::cerr<<msg<<std::endl;
		m_receiver.exceptionThrown(msg);
	}

	void NetLogger::error(const std::string& sender, const std::string& msg)
	{
		std::cerr<<msg<<std::endl;
		m_receiver.exceptionThrown(msg);
	}
}