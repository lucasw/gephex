#include "socketutils.h"

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <unistd.h>
#include <sys/types.h>
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
    //TODO: interrupted!

    return !FD_ISSET(fd, &readfds);
  }

  void SocketUtils::initNetwork()
  {
#if defined(OS_WIN32)
	WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;

    if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
      {
	throw SocketException("Couldn't initialize Winsock 1.1");
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
