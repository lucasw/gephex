#ifndef INCLUDED_TCP_SERVER_SOCKET_H
#define INCLUDED_TCP_SERVER_SOCKET_H

#include "iserversocket.h"

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
  class TCPServerSocket : public IServerSocket
  {

  public:
    explicit TCPServerSocket(int localPort);
    virtual ~TCPServerSocket();

    void listen() throw(std::runtime_error);

    ISocket* accept() throw(std::runtime_error);

  private:
    int m_localPort;
    int m_socket;
  };

}

#endif
