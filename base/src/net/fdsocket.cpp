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

#include "fdsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
//#include <unistd.h>
//#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <fcntl.h> 
#include <errno.h>
#endif

#include "netexceptions.h"
#include "socketutils.h"

#include "utils/buffer.h"

namespace net
{
  
  FDSocket::FDSocket(int fd, int localPort)
    : ISocket(localPort), m_fd(fd), m_isConnected(true)
  {
	  SocketUtils::initNetwork();
  }

  FDSocket::~FDSocket()
  {
    SocketUtils::closeSocket(m_fd);
	SocketUtils::shutDownNetwork();
  }
  
  int FDSocket::send(const utils::Buffer& data) 
    /*const throw (IOException,UnknownHostException)*/
  {
#if defined(OS_LINUX)
    static const int SEND_FLAGS = MSG_NOSIGNAL;
#else
    static const int SEND_FLAGS = 0;
#endif
    if (!m_isConnected)
      throw IOException("Socket not connected at FDSocket::send!");

    if (m_fd == INVALID_SOCKET)
      throw SocketException("Socket not valid at FDSocket::send!");

    int len = data.getLen();
    const unsigned char* buf = data.getPtr();
    
    int left = len;
    int sent = 0;
    do {
      len = ::send(m_fd, reinterpret_cast<const char*>(buf), left,
		   SEND_FLAGS);
      if ( len > 0 ) 
	{
	  sent += len;
	  left -= len;
	  buf += len;
	}
      else if (len == -1 && errno != EINTR)
	{
	  std::string msg = "Could not send: ";
	  msg += strerror(errno);
	  if (errno == EPIPE)
	    throw BrokenPipeException(msg);
	  else
	    throw IOException(msg);
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
  
  bool FDSocket::receive(utils::Buffer& b) throw (IOException)
  {
    static const int MAX_MSG_LEN=1024;
    static unsigned char buf[MAX_MSG_LEN];

    if (!m_isConnected)
      throw IOException("Socket not connected!");

    if (m_timeout == -1 || !SocketUtils::doesReadBlock(m_fd, m_timeout))
      {
	int len;
	errno = 0;
	do {
	  len = recv(m_fd, reinterpret_cast<char*>(buf),
		     MAX_MSG_LEN, 0);

	  if (len == -1 && errno != EINTR)
	    {
	      throw IOException("Error at FDSocket::receive()");
	    }
	  else if (len == 0)
	    {
	      //TODO: signal, that connection is closed
	      // is an exception the right thing?
	      m_isConnected = false;
	      SocketUtils::closeSocket(m_fd);
	      throw IOException("Remote host closed socket at"
				"FDSocket::receive()");
	    }
	  else
	    {
	      //TODO: use somthing like b.setData(buf,len)
	      b = utils::Buffer(buf,len);
	      return true;
	    }
	} while ( errno == EINTR );
      }
    
    return false;
  }
  
  bool FDSocket::connected() const
  {
    return m_isConnected;
  }
  
} // end of namespace net
