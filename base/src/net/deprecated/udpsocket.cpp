#include "udpsocket.h"

//#include <iostream>

#include <cassert>

#include "config.h"

#ifdef OS_WIN32
#include <windows.h>
#endif
#ifdef OS_POSIX
const int SOCKET_ERROR = -1;
const int INVALID_SOCKET = -1;

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

  static void closeSocket(int& socket)
  {
    if (socket != INVALID_SOCKET)
      {
#ifdef OS_POSIX
	close(socket);
#endif
#ifdef OS_WIN32
	closesocket(socket);
#endif
      }

    socket = INVALID_SOCKET;
  }

  static void setNonBlocking(int socket)
  {
    //set socket to non-blocking
#ifdef OS_WIN32
    unsigned long mode = 1;
    int err = ioctlsocket (socket, FIONBIO, &mode);

	if (err != 0)
	{
		throw std::runtime_error("Couldnt set socket to non-blocking");
	}
#endif
#ifdef OS_POSIX
    long save_file_flags = fcntl(socket, F_GETFL);            
    save_file_flags |= O_NONBLOCK;
    fcntl(socket, F_SETFL, save_file_flags);
#endif	
  }

  //TODO!!!!!!!!!!!! wie geht das?????
  static void setBlocking(int socket)
  {
    //set socket to non-blocking
#ifdef OS_WIN32
    unsigned long mode = 0; //TODO
    ioctlsocket (socket, FIONBIO, &mode);
#endif
#ifdef OS_POSIX
    long save_file_flags = fcntl(socket, F_GETFL);
    save_file_flags |= ~O_NONBLOCK; //TODO
    fcntl(socket, F_SETFL, save_file_flags);
#endif	
  }


  
  UDPSocket::UDPSocket(int localPort_)
    : localPort(localPort_), m_socket(INVALID_SOCKET),
      timeout(0), _isConnected(false), m_addr(0)
  {

#ifdef OS_WIN32
    /* Start up the windows networking */
    WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;

    if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
      {
	throw SocketException("Couldn't initialize Winsock 1.1");
      }
#endif

    m_socket = socket(AF_INET, SOCK_DGRAM, 0); 
    if(m_socket == INVALID_SOCKET)
      {
	throw SocketException("Could not open socket");
      }

    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;
    local_sin.sin_port = htons (localPort);
    local_sin.sin_addr.s_addr = htonl (INADDR_ANY);

	
    if (bind (m_socket, (struct sockaddr *) &local_sin, 
	      sizeof (local_sin)) == SOCKET_ERROR)
      {
	closeSocket(m_socket);
	throw SocketException("Fehler beim binden (port besetzt?)");
      }
  }

  UDPSocket::~UDPSocket()
  {    
    closeSocket(m_socket);

    if (m_addr)
	  delete (sockaddr*) m_addr;
	
#ifdef OS_WIN32
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
  
  int UDPSocket::send(const utils::Buffer& data) 
    /*const throw (IOException,UnknownHostException)*/
  {
	if (!_isConnected)
      throw IOException("Socket not connected at UDPSocket::send!");	

    int len = data.getLen();
    const unsigned char* buf = data.getPtr();

	sockaddr* addr = static_cast<sockaddr*>(m_addr);
    
    int left = len;
    int sent = 0;
    do {
      len = ::sendto(m_socket, reinterpret_cast<const char*>(buf), left, 0,
					  addr, sizeof(*addr));
      if ( len > 0 ) 
	{
	  sent += len;
	  left -= len;
	  buf += len;
	}
      else if (len == -1)
	{	  
	   //std::cerr << "sleeping..." << std::endl;
#ifdef OS_POSIX
	  usleep(10*1000);
#endif
#ifdef OS_WIN32
	  Sleep(10);
#endif
	  // perhaps it would be better wo wait with select until
	  // the socket can send again...
	  /*std::cerr << "done!" << std::endl;
	  std::cerr << "errno = " << errno << std::endl;
	  std::cerr << "EINTR = " << EINTR << std::endl;
	  std::cerr << "EAGAIN = " << EAGAIN << std::endl;*/

#ifdef OS_WIN32
	  if (errno != EAGAIN && errno != EINTR && errno != 0)
#endif
#ifdef OS_POSIX
	  if (errno != EAGAIN && errno != EINTR)
#endif
	  {
		  std::string msg = "Couldnt send: ";
		  msg += strerror(errno);		  
		  throw IOException(msg);
	  }
	}
    } 
#ifdef OS_WIN32
	while ( (left > 0) && ((len > 0) || errno == EAGAIN || errno == EINTR || errno == 0) );
#endif
#ifdef OS_POSIX
	while ( (left > 0) && ((len > 0) || errno == EAGAIN || errno == EINTR) );
#endif    
    
    return sent;
  }

  void UDPSocket::connect(const std::string& hostName, int portNum)
  {
	  static const std::string CONNECT_COMMAND = "connect";

    if (_isConnected)
      return;
    
    hostent* phost = gethostbyname(hostName.c_str());
    
    if (phost == 0)
      {
	throw UnknownHostException("Couldnt resolve hostname.");
      }

    assert(m_addr == 0);
    sockaddr_in* addr = new sockaddr_in;

    m_addr = addr;

    addr->sin_family = AF_INET;
    addr->sin_port = htons (portNum);
    addr->sin_addr = *((struct in_addr *)phost->h_addr);
    
    int len = ::sendto(m_socket,CONNECT_COMMAND.c_str(),
						CONNECT_COMMAND.length()+1,0,
						reinterpret_cast<sockaddr*>(addr),
					  sizeof(sockaddr));

	if (len > 0)
		_isConnected = true;		
	else
	{
#ifdef OS_WIN32
		int error = WSAGetLastError();
#endif
		throw std::runtime_error("Could not udp connect!");
	}
  }

  void UDPSocket::disconnect()
  {
    _isConnected = false;

    closeSocket(m_socket);

	assert(m_addr);
	delete (sockaddr*)m_addr;
	m_addr = 0;
  }

  void UDPSocket::listen()
  {
    //::listen(m_socket,1);    
  }
  
  void UDPSocket::accept()
  {	  
    if (_isConnected)
      return;
    
    sockaddr* from = new sockaddr;
#ifdef OS_POSIX
    unsigned 
#endif
      int fromLen;
	char buf[1024];

	int err = recvfrom(m_socket, buf, 1024, 0,from, &fromLen);

	if (err != SOCKET_ERROR)
	{
		m_addr = from;
		_isConnected = true;
	}
	else if (err != 0)
	{
		//FEHLER!
		delete from;
		//throw SocketException("Fehler bei accept");
	}




  }
  
  utils::Buffer UDPSocket::receive() const throw (IOException,
						  InterruptedIOException)
  {
    static const int MAX_MSG_LEN=1024;
    static unsigned char buf[MAX_MSG_LEN];

    if (!_isConnected)
      throw IOException("Socket not connected!");

    int len;

    if (timeout > 0)
      {
	fd_set readfds;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = timeout*1000;
	FD_SET(m_socket,&readfds);
	select(m_socket+1,&readfds,0,0,&tv);
	//TODO: interrupted!
      }

    errno = 0;
    do {
      len = recv(m_socket, reinterpret_cast<char*>(buf), MAX_MSG_LEN, 0);
      if (len == -1)
	{
	  // throw IOException("Fehler bei recv.");
	  // do nothing
	  //	  std::cerr << "mist" << std::endl;
	}
      else
	{
	  return utils::Buffer(buf,len);
	}
    } while ( errno == EINTR );
    
    return utils::Buffer(0,0);
  }
  
  void UDPSocket::setSoTimeout(int timeout_)
  {
    timeout = timeout_;
    if (timeout == -1)
      {
		setBlocking(m_socket);	
      }
    else if (timeout >= 0)
      {
		setNonBlocking(m_socket);	
      }
  }
  
  int UDPSocket::soTimeout() const
  {
    return timeout;
  }
  
  int UDPSocket::port() const
  {
    return localPort;
  }

  bool UDPSocket::connected() const
  {
    return _isConnected;
  }
  
} // end of namespace net
