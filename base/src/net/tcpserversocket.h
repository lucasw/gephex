#ifndef INCLUDED_TCP_SERVER_SOCKET_H
#define INCLUDED_TCP_SERVER_SOCKET_H

#include "iserversocket.h"

namespace net
{

  /**
   * Die Klasse Netstream kapselt die gesamte Netzwerkfunktionalit�t.
   * Sie ist daf�r ausgelegt nichtblockierend zu arbeiten (-> keine Threads).
   * Sie kann prinzipiell in zwei Modi arbeiten: serverMode und clientMode.
   * Im ServerMode wartet sie an einem bestimmten Port auf connections.
   * Im Clientmode ist es m�glich mit connectTo zu einem anderen Rechner
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
