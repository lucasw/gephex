#ifndef INCLUDED_TCP_CLIENT_SOCKET_H
#define INCLUDED_TCP_CLIENT_SOCKET_H

#include "iclientsocket.h"

namespace net
{

  /**
   * Die Klasse Netstream kapselt die gesamte Netzwerkfunktionalität.
   * Sie ist dafür ausgelegt nichtblockierend zu arbeiten (-> keine Threads).
   * Sie kann prinzipiell in zwei Modi arbeiten: serverMode und clientMode.
   * Im ServerMode wartet sie an einem bestimmten Port auf connections.
   * Im Clientmode ist es möglich mit connectTo zu einem anderen Rechner
   * in Verbindung zu treten.
   */
  class TCPClientSocket : public IClientSocket
  {

  public:
    explicit TCPClientSocket(int localPort = 0);
    virtual ~TCPClientSocket();

    ISocket* connect(const std::string& remoteHost,
		     int remotePort) throw(std::runtime_error);

  private:
    int m_socket;
    int m_localPort;
  };

}

#endif
