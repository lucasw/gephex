#include "domainserversocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <winsock.h>

struct sockaddr_un {
 short sun_family;
 char sun_path[108];
};
#elif defined(OS_POSIX)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#endif

#include <sstream>

#include "netexceptions.h"
#include "socketutils.h"
#include "fdsocket.h"

#include "utils/buffer.h"

namespace net
{

  DomainServerSocket::DomainServerSocket(const std::string& basePath,
					 int localPort)

    : m_localPort(localPort), m_socket(INVALID_SOCKET)
  {
	  SocketUtils::initNetwork();
    m_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(m_socket == INVALID_SOCKET)
      {
	throw SocketException("Could not open socket");
      }

    // create the socket filename from the port
    std::ostringstream os;
    os << basePath << localPort;


    sockaddr_un local;
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, os.str().c_str());
	
    unlink(local.sun_path);
    int len = strlen(local.sun_path) + sizeof(local.sun_family);

    if (bind(m_socket, (struct sockaddr *)&local, len) == SOCKET_ERROR)
      {
	SocketUtils::closeSocket(m_socket);
	throw SocketException("Fehler beim binden bei DomainServerSocket::"
			      "DomainServerSocket() (Path = "
			      + os.str());
      }
  }

  DomainServerSocket::~DomainServerSocket()
  {
	  SocketUtils::shutDownNetwork();
    SocketUtils::closeSocket(m_socket);
  }

  void DomainServerSocket::listen() throw(std::runtime_error)
  {
    ::listen(m_socket,1);    
  }
  
  ISocket* DomainServerSocket::accept() throw(std::runtime_error)
  {
    sockaddr_un remote;
#if defined(OS_POSIX) && !defined(OS_CYGWIN)
    unsigned 
#endif
      int len = sizeof(remote);

    if (m_timeout == -1 || !SocketUtils::doesReadBlock(m_socket, m_timeout))
      {

	int newSocket = ::accept(m_socket, (sockaddr*) &remote, &len);
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
