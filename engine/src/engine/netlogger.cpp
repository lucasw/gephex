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
    std::string report = "[" + sender + "]:> " + msg;

    std::cerr << "@log@ " << report << std::endl;
    m_receiver.log(report);
  }

  void NetLogger::warning(const std::string& sender, const std::string& msg)
  {
    std::string report = "[" + sender + "]:> " + msg;

    std::cerr << "@warning@ " << report << std::endl;
    m_receiver.warning(report);
  }

  void NetLogger::error(const std::string& sender, const std::string& msg)
  {
    std::string report = "[" + sender + "]:> " + msg;

    std::cerr << "@error@ "<< report << std::endl;
    m_receiver.error(report);
  }
}
