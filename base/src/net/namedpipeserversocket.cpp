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

	struct NamedPipeImpl 
	{
		NamedPipeImpl(int localPort)
			: m_localPort(localPort), m_handle(INVALID_HANDLE_VALUE)			  
		{
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

	  std::cout << "Creating named pipe '" << name << "'..." << std::endl;
	  m_impl->m_handle = CreateNamedPipe(name.c_str(),
		 PIPE_ACCESS_DUPLEX,      // read/write access,
         PIPE_TYPE_BYTE |      // byte-type pipe 
         /*PIPE_READMODE_BYTE |*/  // byte-read mode 
         PIPE_WAIT,               // blocking mode 
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
	  std::cout << "... success!!!" << std::endl;
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
	 std::cout << "Accepting on named pipe..." << std::endl;
	int error = ConnectNamedPipe(m_impl->m_handle, 0);
	int e = GetLastError();
	if (error == 0 && e != ERROR_PIPE_CONNECTED)
	{
		std::cout << "... no connection" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "... success!!!" << std::endl;
		return new FHSocket(m_impl->m_handle, m_impl->m_localPort);
	}

  }

} // end of namespace net
