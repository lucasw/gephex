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

#include "socketutils.h"

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> //needed for struct timeval in netbsd
#include <sys/socket.h>
#include <errno.h>
#endif

#include "netexceptions.h"

namespace net {

  void SocketUtils::closeSocket(int& socket)
  {
    if (socket != INVALID_SOCKET)
      {
#if defined(OS_POSIX)
	close(socket);
#elif defined(OS_WIN32)
	closesocket(socket);
#endif
      }
    
    socket = INVALID_SOCKET;
  }

  bool SocketUtils::doesReadBlock(int fd, int timeout)
  {
    fd_set readfds;
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = timeout*1000;
    FD_ZERO(&readfds);
    FD_SET(fd,&readfds);
    select(fd+1,&readfds,0,0,&tv);
    //TODO: handle EINTR

    return !FD_ISSET(fd, &readfds);
  }

  void SocketUtils::initNetwork()
  {
#if defined(OS_WIN32)
	WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;

    if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
      {
	throw SocketException("Could not initialize Winsock 1.1");
      }
#endif
  }

  void SocketUtils::shutDownNetwork()
  {
#if defined(OS_WIN32)
    if ( WSACleanup() == SOCKET_ERROR ) 
      {
	if ( WSAGetLastError() == WSAEINPROGRESS ) 
	  {
	    WSACancelBlockingCall();
	    WSACleanup();
	  }
      }
#endif

  }
}
