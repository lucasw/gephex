#ifndef INCLUDED_NAMED_PIPE_CLIENT_SOCKET_H
#define INCLUDED_NAMED_PIPE_CLIENT_SOCKET_H

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
  class NamedPipeClientSocket : public IClientSocket
  {

  public:
    NamedPipeClientSocket();
    virtual ~NamedPipeClientSocket();

    ISocket* connect(const std::string& remoteHost,
		     int remotePort) throw(std::runtime_error);

  private:
    void* m_handle;    
  };

}

#endif
