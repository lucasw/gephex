#ifndef INCLUDED_DOMAIN_SERVER_SOCKET_H
#define INCLUDED_DOMAIN_SERVER_SOCKET_H

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
  class DomainServerSocket : public IServerSocket
  {

  public:
    /**
     * Creates a domain socket bound to a file. The filename is
     * composed from basePath and localPort.
     * @param basePath the prefix of the file that is created,
     *     for example "/tmp/server_socket_".
     * @param localPort the port is appended to the basePath
     *     to complete the filename
     */
    DomainServerSocket(const std::string& basePath, int localPort);

    virtual ~DomainServerSocket();

    void listen() throw(std::runtime_error);

    ISocket* accept() throw(std::runtime_error);

  private:
    int m_localPort;
    int m_socket;
  };

}

#endif
