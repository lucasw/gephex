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

#include "tcpserversocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <iostream>

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/poll.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h> 
#include <errno.h>
#endif

#include "netexceptions.h"
#include "socketutils.h"
#include "fdsocket.h"

#include "utils/buffer.h"


namespace net
{

  TCPServerSocket::TCPServerSocket(int localPort)
    : m_localPort(localPort), m_socket(INVALID_SOCKET)
  {
    SocketUtils::initNetwork();

    m_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if(m_socket == INVALID_SOCKET)
      {
	throw SocketException("Could not open socket");
      }

#if defined(OS_POSIX)
    int yes = 1;
#elif defined(OS_WIN32)
    char yes = '1';
#endif
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR,
		   &yes, sizeof(yes)) == SOCKET_ERROR)
      {
	    // this throws on win98 - no need to abort here
	    //throw SocketException("Could not set socket options");
		std::cerr << "Could not set socket options\n";
      }

    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;
    local_sin.sin_port = htons (localPort);
    local_sin.sin_addr.s_addr = htonl (INADDR_ANY);

	
    if (bind (m_socket, (struct sockaddr *) &local_sin, 
	      sizeof (local_sin)) == SOCKET_ERROR)
      {
	SocketUtils::closeSocket(m_socket);
	throw SocketException("Error at bind() (port occupied?)");
      }
  }

  TCPServerSocket::~TCPServerSocket()
  {
    SocketUtils::closeSocket(m_socket);
      
	SocketUtils::shutDownNetwork();
  }

  void TCPServerSocket::listen() throw(std::runtime_error)
  {
    ::listen(m_socket,1);    
  }
  
  ISocket* TCPServerSocket::accept() throw(std::runtime_error)
  {
    sockaddr accept_sin;
#if defined(OS_POSIX) && !defined(OS_CYGWIN)
    unsigned 
#endif
  int len = sizeof(accept_sin);

    if (m_timeout == -1 || !SocketUtils::doesReadBlock(m_socket, m_timeout))
      {

	int newSocket = ::accept(m_socket, &accept_sin, &len);
	if(newSocket != INVALID_SOCKET)
	  {
	    return new FDSocket(newSocket, m_localPort);
	  }
	else
	  {
	    throw SocketException("Error at accept()");
	  }
      }
    else
      return 0;
  }

} // end of namespace net
