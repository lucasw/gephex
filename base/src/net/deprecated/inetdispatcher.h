#ifndef INCLUDED_INET_DISPATCHER_H
#define INCLUDED_INET_DISPATCHER_H

#include <stdexcept>
#include "interfaces/itask.h"

namespace net
{

  class ISender;
  class IDataListener;

  class INetDispatcher : public ITask
{
 public:
  virtual void createClientPort(const std::string& rHost, int rPort, bool useUDP = false) = 0;

  virtual void createServerPort(int lPort, bool useUDP = false) = 0;

  virtual ISender& getSender(int portNum) throw (std::runtime_error) = 0;

  virtual void registerDataListener(int portNum, IDataListener&)
    throw (std::runtime_error) = 0;

  virtual void disconnect() = 0;

  virtual bool isConnected(int port) const = 0;

  //  virtual bool run() = 0;

};

}

#endif

