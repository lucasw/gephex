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

#include "domainclientsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <winsock2.h>

struct sockaddr_un {
 short sun_family;
 char sun_path[108];
};
#elif defined(OS_POSIX)
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//#include <errno.h>
#endif

#if defined(OS_SOLARIS)

// Solaris seems to redefine connect which interferes with
// the connect method...

#ifdef connect
#undef connect

extern "C" {
  static int connect(int fd, const struct sockaddr *a, socklen_t l)
  {
    return __xnet_connect(fd, a, l);
  }
}
#endif

#endif

#include <sstream>
#include <cassert>

#include "netexceptions.h"
#include "socketutils.h"
#include "fdsocket.h"

#include "utils/buffer.h"


namespace net
{

  DomainClientSocket::DomainClientSocket(int localPort)
    : m_socket(INVALID_SOCKET), m_localPort(localPort)
  {
	  SocketUtils::initNetwork();
    m_socket = socket(AF_UNIX, SOCK_STREAM, 0); 
    if(m_socket == INVALID_SOCKET)
      {
	throw SocketException("Could not open socket");
      }

    assert(m_socket != INVALID_SOCKET);
  }

  DomainClientSocket::~DomainClientSocket()
  {
	  SocketUtils::shutDownNetwork();
    if (m_socket != INVALID_SOCKET)
      SocketUtils::closeSocket(m_socket);
  }
  
  ISocket* DomainClientSocket::connect(const std::string& basePath,
				       int remotePort)
    throw(std::runtime_error)
  {
    if (m_socket == INVALID_SOCKET)
      {
	throw SocketException("Socket already connected!");
      }
    
    // create the socket file name
    std::ostringstream os;
    os << basePath << remotePort;

    sockaddr_un remote;
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, os.str().c_str());

    int len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    if (::connect(m_socket, (struct sockaddr *)&remote, len) == INVALID_SOCKET)
      {
	throw SocketException("Could not connect.");
      }
    
    FDSocket* newSocket = new FDSocket(m_socket, m_localPort);

    /* the new FDSocket is responsible for closing m_socket */
    m_socket = INVALID_SOCKET;

    return newSocket;
  }
  
} // end of namespace net
