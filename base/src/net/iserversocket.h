#ifndef INCLUDED_ISERVER_SOCKET_H
#define INCLUDED_ISERVER_SOCKET_H

#include <stdexcept>

#include "sotimeout.h"

namespace net
{

  class ISocket;

  /**
   * Base class for server sockets. This class provides the functionality
   * to accept connections from remote sockets. Once a connection is
   * established, a new ISocket is returned that represents that connection.
   *
   * @see ISocket
   * @see IClientSocket
   */
  class IServerSocket : public SOTimeout {

  public:
    //ServerSocket(int localPort);
    virtual ~IServerSocket() {};

    /**
     * Tells the ServerSocket to listen for incoming ocnnection
     * requests. Must be called before accept.
     */
    virtual void listen() throw(std::runtime_error) = 0;

    /**
     * Accepts an incoming connection request.
     * If the socket is set to non-blocking operation (see setSOTimeout),
     * then 0 is returned when there is no pending connection request.
     * In blocking operation, the return value is always a valid socket
     * (or an exception).
     *
     * accept() can be called multiple times, resulting in new connections
     * every time.
     *
     * @return A new socket that represents the connection that was accepted.
     *     0 is returned in non-blocking operation, when there is no
     *     connection request.
     */
    virtual ISocket* accept() throw(std::runtime_error) = 0;
  };

}

#endif
