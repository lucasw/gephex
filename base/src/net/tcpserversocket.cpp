#include "tcpserversocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

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
	//TODO: ignore for now
	//throw SocketException("Could not set socket options");
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
	    throw SocketException("Fehler bei accept");
	  }
      }
    else
      return 0;
  }

} // end of namespace net
