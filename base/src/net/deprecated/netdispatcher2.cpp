#include "netdispatcher2.h"

#include <algorithm>
#include <sstream>
#include <map>

#include "clientnetsocket.h"
#include "servernetsocket.h"
#include "idatalistener.h"

#include "protocol.h"
#include "tagger.h"
#include "itaginterpreter.h"
#include "tagutils.h"

#include "utils/buffer.h"
#include "utils/stringtokenizer.h"

namespace net
{

  class IPortDataListener
  {
  public:
    virtual void dataReceived(int port, const utils::Buffer&) = 0;
  };

  typedef Tagger<uint_32, UInt32TagUtil> PortTagger;
  class PortSenderWrapper : public ISender
  {
  public:
    PortSenderWrapper(int port, PortTagger& pp)
      : m_port(port), m_pp(pp)
    {
    }

    virtual int send(const utils::Buffer& b)
    {
      m_pp.setTag(m_port);
      m_pp.send(b);
      return 0;
    }

  private:
    int m_port;
    PortTagger& m_pp;
  };

  class PortDispatcher : public ITagInterpreter<uint_32>
  {
  public:
    void registerDataListener(int port, IDataListener& dl)
    {			
      m_listeners[port] = &dl;			
    }

    virtual void dataReceived(const uint_32& port, const utils::Buffer& b)
    {
      ListenerMap::const_iterator it = m_listeners.find(port);
      if (it != m_listeners.end())
	{
	  it->second->dataReceived(b);
	}
      else
	{
	  std::ostringstream stream;
	  stream << "No PortDataListener for port " << port << "!";
	  throw std::runtime_error(stream.str().c_str());
	}
    }

  private:
    typedef std::map<int, IDataListener*> ListenerMap;
    ListenerMap m_listeners;
  };
 
  NetDispatcher2::NetDispatcher2(const std::string& hostName, int netPort,
				 bool server)
  {
    if (server)
	{
      ns = utils::AutoPtr<INetSocket>(new ServerNetSocket(netPort));
	  nsUDP = utils::AutoPtr<INetSocket>(new ServerNetSocket(netPort+1, true));
	}
    else
	{
      ns = utils::AutoPtr<INetSocket>(new ClientNetSocket(hostName,netPort));
	  nsUDP = utils::AutoPtr<INetSocket>(new ClientNetSocket(hostName,netPort+1,true));
	}

    tagger = utils::AutoPtr<PortTagger>(new PortTagger());	
    prot = utils::AutoPtr<Protocol>(new Protocol(*tagger));
    prot->registerSender(*ns);

    tagger->registerSender(*prot);

    ns->setDataListener(*prot);
	//nsUDP->setDataListener(*ppUDP);

    pDisp = utils::AutoPtr<PortDispatcher>(new PortDispatcher());	

    tagger->registerInterpreter(*pDisp);	
  }

  NetDispatcher2::~NetDispatcher2()
  {	  
  }

  void NetDispatcher2::createClientPort(const std::string& rHost,
					int rPort, bool useUDP)
  {
	m_isUDP.insert(std::make_pair(rPort,useUDP));
  }

  void NetDispatcher2::createServerPort(int lPort, bool useUDP)
  {
    m_isUDP.insert(std::make_pair(lPort,useUDP));
  }

  ISender& NetDispatcher2::getSender(int portNum)
    throw (std::runtime_error)
  {	  
	  if (m_isUDP[portNum] != true)
	  {
		  utils::AutoPtr<PortSenderWrapper> 
			  newSender (new PortSenderWrapper(portNum, *tagger));

		 m_senders.push_back(newSender);
    
	    return *newSender;
	  }
	  else
	  {
		  
		return *nsUDP;
	  }		
  }

  void NetDispatcher2::registerDataListener(int portNum,
					    IDataListener& listener)
    throw (std::runtime_error)
  {
	if (m_isUDP[portNum] == false)
		pDisp->registerDataListener(portNum,listener);    
	else
		nsUDP->setDataListener(listener);
  }

  void NetDispatcher2::disconnect()
  {
    ns->disconnect();
  }
    
  bool NetDispatcher2::isConnected(int port) const
  {
    return ns->isConnected();
  }

  bool NetDispatcher2::run()
  {
    if (!ns->isConnected())
      ns->buildConnection();
    else
      ns->run();

	if (!nsUDP->isConnected())
      nsUDP->buildConnection();
    else
      nsUDP->run();

    return true;
  }

} // end of namespace net
