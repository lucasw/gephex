/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
