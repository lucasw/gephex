#ifndef INCLUDED_NET_DISPATCHER_H
#define INCLUDED_NET_DISPATCHER_H

#include <map>

#include "inetdispatcher.h"

namespace net
{

  class PortControlBlock;

  class NetDispatcher : public INetDispatcher
  {
  public:
    virtual ~NetDispatcher();

    virtual void createClientPort(const std::string& rHost, int rPort,
								  bool useUDP);

    virtual void createServerPort(int lPort,bool useUDP);

    virtual ISender& getSender(int portNum) throw (std::runtime_error);

    virtual void registerDataListener(int portNum,IDataListener&)
      throw (std::runtime_error);

    virtual void disconnect();
    
    virtual bool isConnected(int port) const;

    virtual bool run();

  private:
    typedef std::map<int,PortControlBlock*> PortMap;
    PortMap m_ports;
  };
}

#endif
