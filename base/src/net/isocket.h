#ifndef INCLUDED_ISOCKET_H
#define INCLUDED_ISOCKET_H

#include <string>

#include "netexceptions.h"
#include "isender.h"
#include "sotimeout.h"

namespace utils {
  class Buffer;
}

namespace net
{

  /**
   * Base class for connected Sockets. It just provides the functionality
   * to configure a socket and to send and receive through it.
   * The functionality to accept connections and connect to remote
   * sockets is provided by the IServerSocket and IClientSocket classes.
   * @see IServerSocket
   * @see IClientSocket
   */

  class ISocket : public ISender, public SOTimeout
  {
  public:
    /*
     * Creates a new Socket thats bound to localhost:_portnr
     */
    explicit ISocket(int localPort);

    /*
     * Destroys the Socket
     */
    virtual ~ISocket();

    /**
     * Send a message to another socket.
     *
     * @param data the message that is sent
     *
     * @throw IOException if there is an IO Error
     * @throw SocketException: is thrown if the socket is invalid
     * @throw BrokenPipeException: is thrown if the remote side
     *            closed the connection
     */
    virtual int send(const utils::Buffer& data) 
      /*const throw (IOException,SocketException,BrokenPipeException)*/ = 0;


    /**
     * (Blocking) Receiving of a Message (see setSOTimeOut)
     *
     * @param b the data that has been received is copied here
     *
     * @return in blocking operation always true
     *         in non-blocking operation, true, iff data was received
     * 
     * @throw IOException if there is an IO Error
     */
    virtual bool receive(utils::Buffer& b) throw (IOException) = 0; 

    /**
     * Get the (local) port number to which the socket is bound.
     * @return the local port of the socket
     */
    int localPort() const;

    /**
     * Returns wether the socket is connected.
     * @return wether the socket is connected
     */
    virtual bool connected() const = 0;

  protected:
    int m_localPort;
  };

} // end of namespace net

#endif
