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

#ifndef INCLUDED_ICLIENT_SOCKET_H
#define INCLUDED_ICLIENT_SOCKET_H

#include <string>
#include <stdexcept>

#include "sotimeout.h"

namespace net
{

  class ISocket;

  /**
   * Base class for client sockets. This class provides the functionality
   * to connect to remote sockets. Once a connection is
   * established, a new ISocket is returned that represents that connection.
   *
   * @see ISocket
   * @see IClientSocket
   */
  class IClientSocket : public SOTimeout
  {

  public:
    //ServerSocket(int localPort);
    virtual ~IClientSocket() {};

    /**
     * Tries to connect to a remote host.
     * When the socket is in blocking operation (see setSOTimeout),
     * the return value is always a valid ISocket pointer (or an
     * exception). In non-blocking operation, 0 is returned,
     * when the remote host is not listening.
     * @param remoteHost the hostname of the remote host
     *        (for example "10.10.0.1" or "www.google.de")
     * @param remotePort the port on which the connection is
     *        requested	 
     * @return a new Socket that represents the connection
     */
    virtual ISocket* connect(const std::string& remoteHost,
		     int remotePort) throw(std::runtime_error) = 0;
  };

}

#endif
