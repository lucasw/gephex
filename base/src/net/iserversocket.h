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
