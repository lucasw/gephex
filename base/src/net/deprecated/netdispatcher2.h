#ifndef INCLUDED_NET_DISPATCHER2_H
#define INCLUDED_NET_DISPATCHER2_H

#include <list>
#include <map>

#include "inetdispatcher.h"

#include "utils/autoptr.h"

#include "basic_types.h"



namespace net
{

  class INetSocket;

  class UInt32TagUtil;
  template <typename Key,class TagUtil>
  class Tagger;

  class Protocol;

  class PortDispatcher;
  class PortSenderWrapper;

  class NetDispatcher2 : public INetDispatcher
  {
  public:
    NetDispatcher2(const std::string& hostName,int netPort,
		   bool server);

    virtual ~NetDispatcher2();

	//TODO: BIS JETZT KANN ES NUR GENAU EINEN UDP PORT GEBEN!!!!
    virtual void createClientPort(const std::string& rHost, int rPort, bool useUDP=false);

	//TODO: BIS JETZT KANN ES NUR GENAU EINEN UDP PORT GEBEN!!!!
    virtual void createServerPort(int lPort, bool useUDP=false);

    virtual ISender& getSender(int portNum) throw (std::runtime_error);

    virtual void registerDataListener(int portNum,IDataListener&)
      throw (std::runtime_error);

    virtual void disconnect();
    
    virtual bool isConnected(int port) const;

    virtual bool run();

  private:
    utils::AutoPtr<INetSocket> ns;
    utils::AutoPtr<Tagger<uint_32, UInt32TagUtil> > tagger;
    utils::AutoPtr<INetSocket> nsUDP;
    utils::AutoPtr<Protocol> prot;
	
	
    utils::AutoPtr<PortDispatcher> pDisp;
	

    std::list<utils::AutoPtr<PortSenderWrapper> > m_senders;

    std::map<int,bool> m_isUDP;
  };
}

#endif
