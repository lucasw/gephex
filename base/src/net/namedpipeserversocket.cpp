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

#include "namedpipeserversocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <iostream>
#include <sstream>

#if !defined(OS_WIN32)
#error "WIN32 only!"
#endif
#include <windows.h>

#include "fhsocket.h"
#include "netexceptions.h"

#include "utils/buffer.h"


namespace net
{

	static int release_handle(void* h)
  {
	  return DisconnectNamedPipe(h);
  }

	struct NamedPipeImpl 
	{
		NamedPipeImpl(int localPort)
			: m_localPort(localPort), m_handle(INVALID_HANDLE_VALUE)			  
		{
		}

		~NamedPipeImpl()
		{
			if (m_handle != INVALID_HANDLE_VALUE)
				CloseHandle(m_handle);
		}

	  int m_localPort;
      HANDLE m_handle;	  
	};

  NamedPipeServerSocket::NamedPipeServerSocket(int localPort)
    : m_impl(new NamedPipeImpl(localPort))
  {
	  const int OUT_BUF_SIZE = 10240*10;
	  const int IN_BUF_SIZE = 10240;
	  const int PIPE_TIMEOUT = 100;

	  // create the pipe name
	  std::ostringstream os;
	  os << "\\\\.\\pipe\\" << localPort;

	  std::string name = os.str();	  

	  //std::cout << "Creating named pipe '" << name << "'..." << std::endl;
	  m_impl->m_handle = CreateNamedPipe(name.c_str(),
		 PIPE_ACCESS_DUPLEX,      // read/write access,
         PIPE_TYPE_BYTE |      // byte-type pipe 
         /*PIPE_READMODE_BYTE |*/  // byte-read mode 
         PIPE_NOWAIT,               // blocking mode 
         1,						  // number of instances 
         OUT_BUF_SIZE,                 // output buffer size 
         IN_BUF_SIZE,                 // input buffer size 
         PIPE_TIMEOUT,            // client time-out 
         NULL);                   // no security attributes 
  
	  if (m_impl->m_handle == INVALID_HANDLE_VALUE)
	  {
		  delete m_impl;
			throw SocketException("Could not create named pipe '" + name + "'");
	  }
	  //std::cout << "... success!!!" << std::endl;
  }

  NamedPipeServerSocket::~NamedPipeServerSocket()
  {
   delete m_impl;
  }

  void NamedPipeServerSocket::listen() throw(std::runtime_error)
  {
   
  }
  
  ISocket* NamedPipeServerSocket::accept() throw(std::runtime_error)
  {
	 //std::cout << "Accepting on named pipe..." << std::endl;
	int error = ConnectNamedPipe(m_impl->m_handle, 0);
	int e = GetLastError();
	if (error == 0)
	{
		switch(e)
		{
		case 0:
			//std::cout << "... success!!!" << std::endl;
		    return new FHSocket(m_impl->m_handle,
								release_handle,
				                m_impl->m_localPort);
		case ERROR_PIPE_CONNECTED:
			//std::cout << "... pipe connected" << std::endl;
			return new FHSocket(m_impl->m_handle,
								release_handle,
				                m_impl->m_localPort);			
		case ERROR_PIPE_LISTENING:
			//std::cout << "... no connection" << std::endl;
			return 0;
		case ERROR_NO_DATA:
			std::cout << "... no data" << std::endl;
			DisconnectNamedPipe(m_impl->m_handle);
			return 0;
		default:
			std::cout << "... unknown error\n";
			return 0;
			
		}
	}
	else
	{
		//std::cout << "... nonzero return\n";
		return 0;
		/*return new FHSocket(m_impl->m_handle,
								release_handle,
				                m_impl->m_localPort);*/
	}

  }

} // end of namespace net
