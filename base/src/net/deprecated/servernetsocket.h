#ifndef INCLUDED_SERVER_NETSOCKET_H
#define INCLUDED_SERVER_NETSOCKET_H

#include "inetsocket.h"

#include "utils/autoptr.h"

namespace net
{

  class IDataListener;
  class ISocket;


  /**
   * Die Klasse Netstream kapselt die gesamte Netzwerkfunktionalität.
   * Sie ist dafür ausgelegt nichtblockierend zu arbeiten (-> keine Threads).
   * Sie kann prinzipiell in zwei Modi arbeiten: serverMode und clientMode.
   * Im ServerMode wartet sie an einem bestimmten Port auf connections.
   * Im Clientmode ist es möglich mit connectTo zu einem anderen Rechner
   * in Verbindung zu treten.
   */
  class ServerNetSocket : public INetSocket {
  private:
    IDataListener* dListener;

    utils::AutoPtr<ISocket> m_socket;

    std::string m_remoteHost;
    int m_remotePort;

  public:
    ServerNetSocket(int port, bool useUDP = false);
    virtual ~ServerNetSocket();

    void setDataListener(IDataListener& listener);

    void buildConnection() throw(std::runtime_error);

    void run();
	
    void disconnect();
    bool isConnected();

    virtual int send(const utils::Buffer& buf) throw(std::runtime_error);
  };

}

#endif
