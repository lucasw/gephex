#include "tcpclientsocket.h"

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

#include <cassert>

#include "netexceptions.h"
#include "socketutils.h"
#include "fdsocket.h"

#include "utils/buffer.h"


namespace net
{

  TCPClientSocket::TCPClientSocket(int localPort)
    : m_socket(INVALID_SOCKET), m_localPort(localPort)
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
	throw SocketException("Fehler beim binden (port besetzt?)");
      }

    assert(m_socket != INVALID_SOCKET);
  }

  TCPClientSocket::~TCPClientSocket()
  {
    if (m_socket != INVALID_SOCKET)
      SocketUtils::closeSocket(m_socket);

	SocketUtils::shutDownNetwork();
  }
  
  ISocket* TCPClientSocket::connect(const std::string& hostName, int portNum)
     throw(std::runtime_error)
  {
    if (m_socket == INVALID_SOCKET)
      {
	throw SocketException("Socket already connected!");
      }

    hostent* phost = gethostbyname(hostName.c_str());
    
    if (phost == 0)
      {
	throw UnknownHostException("Could not resolve hostname '"+
				   hostName + "'");
      }
    
    sockaddr_in dest_sin;
    dest_sin.sin_family = AF_INET;
    dest_sin.sin_port = htons (portNum);
    dest_sin.sin_addr = *((struct in_addr *)phost->h_addr);

    //TODO: check for timeout and blocking operation
    
    if (::connect(m_socket,(struct sockaddr*)&dest_sin,
		  sizeof(dest_sin)) != 0)
      {
	throw SocketException("Could not connect.");
      }
    
    FDSocket* newSocket = new FDSocket(m_socket, m_localPort);

    /* the new FDSocket is responsible for closing m_socket */
    m_socket = INVALID_SOCKET;

    return newSocket;
  }
  
} // end of namespace net
