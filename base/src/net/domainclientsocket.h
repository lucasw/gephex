#ifndef INCLUDED_DOMAIN_CLIENT_SOCKET_H
#define INCLUDED_DOMAIN_CLIENT_SOCKET_H

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
  class DomainClientSocket : public IClientSocket
  {

  public:
    explicit DomainClientSocket(int localPort = 0);
    virtual ~DomainClientSocket();

    /**
     * Connects do another domainsocket.
     * @param basePath the prefix of the file that is accepting the
     *     connection, for example "/tmp/server_socket_".
     * @param remotePort the port is appended to the basePath
     *     to complete the filename
     */
    ISocket* connect(const std::string& basePath,
		     int remotePort) throw(std::runtime_error);

  private:
    int m_socket;
    int m_localPort;
  };

}

#endif
