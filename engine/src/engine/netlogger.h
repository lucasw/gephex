#ifndef INCLUDED_NET_LOGGER_H
#define INCLUDED_NET_LOGGER_H

#include "utils/ilogger.h"

class IErrorReceiver;

namespace engine
{

	class NetLogger : public utils::ILogger
	{
	public:
		NetLogger(IErrorReceiver& ier);
		virtual void log(const std::string& sender, const std::string& msg);
		virtual void warning(const std::string& sender, const std::string& msg);
		virtual void error(const std::string& sender, const std::string& msg);

	private:
		IErrorReceiver& m_receiver;
	};
}

#endif
