#include "tcpsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

//#include <iostream>

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

#include "utils/buffer.h"

namespace net
{

#if defined(OS_POSIX)
  static const int SOCKET_ERROR = -1;
  static const int INVALID_SOCKET = -1;
#endif

  static void closeSocket(int& socket)
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

  
  TCPSocket::TCPSocket(int localPort_)
    : localPort(localPort_), serverSocket(INVALID_SOCKET),
      readySocket(INVALID_SOCKET), timeout(0), _isConnected(false)
  {

#if defined(OS_WIN32)
    /* Start up the windows networking */
    WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;

    if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
      {
	throw SocketException("Couldn't initialize Winsock 1.1");
      }
#endif

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if(serverSocket == INVALID_SOCKET)
      {
	throw SocketException("Could not open socket");
      }

#if defined(OS_POSIX)
    int yes = 1;
#elif defined(OS_WIN32)
    char yes = '1';
#endif
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR,
		   &yes, sizeof(yes)) == SOCKET_ERROR)
      {
	throw SocketException("Could not set socket options");
      }

    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;
    local_sin.sin_port = htons (localPort);
    local_sin.sin_addr.s_addr = htonl (INADDR_ANY);

	
    if (bind (serverSocket, (struct sockaddr *) &local_sin, 
	      sizeof (local_sin)) == SOCKET_ERROR)
      {
	closeSocket(serverSocket);
	throw SocketException("Fehler beim binden (port besetzt?)");
      }
  }

  TCPSocket::~TCPSocket()
  {
    closeSocket(readySocket);
    closeSocket(serverSocket);//TODO
      
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
  
  int TCPSocket::send(const utils::Buffer& data) 
    /*const throw (IOException,UnknownHostException)*/
  {
    if (!_isConnected)
      throw IOException("Socket not connected at TCPSocket::send!");

    if (readySocket == INVALID_SOCKET)
      throw SocketException("Socket not valid at TCPSocket::send!");

    int len = data.getLen();
    const unsigned char* buf = data.getPtr();
    
    int left = len;
    int sent = 0;
    do {
      len = ::send(readySocket, reinterpret_cast<const char*>(buf), left, 0);
      if ( len > 0 ) 
	{
	  sent += len;
	  left -= len;
	  buf += len;
	}
      else if (len == -1)
	{	  
	  if (errno != EINTR)
	    {
	      std::string msg = "Couldnt send: ";
	      msg += strerror(errno);		  
	      throw IOException(msg);
	    }
	}
    }
#if defined(OS_WIN32)
    while ( (left > 0) && ((len > 0) || errno == EINTR 
			   || errno == 0) );
#elif defined(OS_POSIX)
    while ( (left > 0) && ((len > 0) || errno == EINTR) );
#endif
    
    return sent;
  }

  void TCPSocket::connect(const std::string& hostName, int portNum)
  {
    if (_isConnected)
      return;
    
    hostent* phost = gethostbyname(hostName.c_str());
    
    if (phost == 0)
      {
	throw UnknownHostException("Couldnt resolve hostname.");
      }
    
    readySocket = socket (AF_INET,SOCK_STREAM,0);
    
    if (readySocket == INVALID_SOCKET)
      {
	throw SocketException("Couldnt open socket.");
      }
    
    sockaddr_in dest_sin;
    dest_sin.sin_family = AF_INET;
    dest_sin.sin_port = htons (portNum);
    dest_sin.sin_addr = *((struct in_addr *)phost->h_addr);
    
    if (::connect(readySocket,(struct sockaddr*)&dest_sin,
		  sizeof(dest_sin)) != 0)
      {
	throw SocketException("Could not connect.");
      }
    
    _isConnected = true;		
  }

  void TCPSocket::disconnect()
  {
    _isConnected = false;

    closeSocket(readySocket);
  }

  void TCPSocket::listen()
  {
    ::listen(serverSocket,1);    
  }
  
  void TCPSocket::accept()
  {
    if (_isConnected)
      return;
    
    sockaddr accept_sin;
#if defined(OS_POSIX)
    unsigned 
#endif
      int len = sizeof(accept_sin); //TODO
    readySocket = ::accept(serverSocket, &accept_sin, &len);
    if(readySocket != INVALID_SOCKET)
      {
	_isConnected=true;
      }
    else
      {
	//throw SocketException("Fehler bei accept"); //TODO
      }	
  }
  
  utils::Buffer TCPSocket::receive() const throw (IOException,
						  InterruptedIOException)
  {
    static const int MAX_MSG_LEN=1024;
    static unsigned char buf[MAX_MSG_LEN];

    if (!_isConnected)
      throw IOException("Socket not connected!");

    int len;
    bool doRecv = true;

    if (timeout >= 0)
      {
	fd_set readfds;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = timeout*1000;
	FD_ZERO(&readfds);
	FD_SET(readySocket,&readfds);
	select(readySocket+1,&readfds,0,0,&tv);
	//TODO: interrupted!

	if (!FD_ISSET(readySocket, &readfds))
	  doRecv = false;
      }
    
    if (doRecv)
      {
	errno = 0;
	do {
	  len = recv(readySocket, reinterpret_cast<char*>(buf),
		     MAX_MSG_LEN, 0);
	  if (len == -1)
	    {
	      throw IOException("Fehler bei recv.");
	    }
	  else
	    {
	      return utils::Buffer(buf,len);
	    }
	} while ( errno == EINTR );
      }
    
    return utils::Buffer(0,0);
  }
  
  void TCPSocket::setSoTimeout(int timeout_)
  {
    timeout = timeout_;
  }
  
  int TCPSocket::soTimeout() const
  {
    return timeout;
  }
  
  int TCPSocket::port() const
  {
    return localPort;
  }

  bool TCPSocket::connected() const
  {
    return _isConnected;
  }
  
} // end of namespace net
