#include "netdispatcher.h"

#include <algorithm>
#include <iostream>

#include "clientnetsocket.h"
#include "servernetsocket.h"

#include "utils/autoptr.h"

namespace net
{

  class PortControlBlock
  {
  public:
    PortControlBlock(int lPort)
    {
	ns = utils::AutoPtr<INetSocket>(new ServerNetSocket(lPort));
    }

    PortControlBlock(const std::string& rHost,
		     int rPort)
    {
	ns = utils::AutoPtr<INetSocket>(new ClientNetSocket(rHost,rPort));
    }


    void setDataListener(IDataListener& listener)
    {
      ns->setDataListener(listener);
    }

    ISender& getSender()
    {
      return *ns;
    }

    bool isConnected() const
    {
      return ns->isConnected();
    }

    void disconnect()
    {
      ns->disconnect();
    }

    bool run()
    {
      if (!ns->isConnected())
		ns->buildConnection();
      else
		ns->run();

      return true;
    }

  private:
    utils::AutoPtr<INetSocket> ns;
  };


  class DoRun
  {
  public:
	  void operator()(const std::pair<int,PortControlBlock*>& p)
    {
      p.second->run();
    }
  };

  class DoDisconnect
  {
  public:
	  void operator()(const std::pair<int,PortControlBlock*>& p)
    {
      p.second->disconnect();
    }
  };

  class DoDelete
  {
  public:
	  void operator()(const std::pair<int,PortControlBlock*>& p)
    {
      delete p.second;
    }
  };

  NetDispatcher::~NetDispatcher()
  {
    std::for_each(m_ports.begin(), m_ports.end(),  DoDelete());
  }

  void NetDispatcher::createClientPort(const std::string& rHost,
				       int rPort, bool useUDP)
  {
    PortMap::const_iterator it = m_ports.find(rPort);
    if (it != m_ports.end())
      throw std::runtime_error("Port already exists!");

    PortControlBlock* newPort = new PortControlBlock(rHost,rPort);
    m_ports[rPort] = newPort;
  }

  void NetDispatcher::createServerPort(int lPort, bool useUDP)
  {
    PortMap::const_iterator it = m_ports.find(lPort);
    if (it != m_ports.end())
      throw std::runtime_error("Port already exists!");

    PortControlBlock* newPort = new PortControlBlock(lPort);
    m_ports[lPort] = newPort;
  }

  ISender& NetDispatcher::getSender(int portNum)
    throw (std::runtime_error)
  {
    PortMap::const_iterator it = m_ports.find(portNum);
    if (it == m_ports.end())
      throw std::runtime_error("Port doesnt exist!");

    return it->second->getSender();
  }

  void NetDispatcher::registerDataListener(int portNum,
					   IDataListener& listener)
    throw (std::runtime_error)
  {
    PortMap::const_iterator it = m_ports.find(portNum);
    if (it == m_ports.end())
      throw std::runtime_error("Port doesnt exist!");

    it->second->setDataListener(listener);
  }

  void NetDispatcher::disconnect()
  {
    std::for_each(m_ports.begin(), m_ports.end(),  DoDisconnect());
  }
    
  bool NetDispatcher::isConnected(int port) const
  {
    PortMap::const_iterator it = m_ports.find(port);
    if (it == m_ports.end())
      throw std::runtime_error("Port doesnt exist!");

    return it->second->isConnected();
  }

  bool NetDispatcher::run()
  {
    try
      {
		std::for_each(m_ports.begin(), m_ports.end(),  DoRun());
      }
    catch (std::runtime_error& e)
      {
		std::cerr << e.what() << std::endl;
		throw e;
      }

    return true;
  }

} // end of namespace net
