#include "namedpipeclientsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if !defined(OS_WIN32)
#error "win32 only!"
#endif

#include <iostream>
#include <sstream>

#include <cassert>

#include <windows.h>

#include "netexceptions.h"
#include "socketutils.h"
#include "fhsocket.h"

#include "utils/buffer.h"


namespace net
{

  NamedPipeClientSocket::NamedPipeClientSocket()
    : m_handle(INVALID_HANDLE_VALUE)
  {
	
  }

  NamedPipeClientSocket::~NamedPipeClientSocket()
  {
    
  }
  
  ISocket* NamedPipeClientSocket::connect(const std::string& hostName, int portNum)
     throw(std::runtime_error)
  {
	//create the pipe name
	  std::ostringstream os;
	  os << "\\\\" << hostName << "\\pipe\\" << portNum;
	  std::string name = os.str();

	  std::cout << "Trying to connect to Pipe '" << name << "'..." << std::endl;
	  
	  if (m_timeout >= 0)
	  {
		  WaitNamedPipe(name.c_str(), m_timeout);
	  }
      else if (m_timeout == -1)
		  WaitNamedPipe(name.c_str(), NMPWAIT_WAIT_FOREVER);

	  m_handle = CreateFile(name.c_str(),
							GENERIC_READ | GENERIC_WRITE,
							0,0,OPEN_EXISTING,0,0);


	  if (m_handle == INVALID_HANDLE_VALUE)
	  {
		  std::cout << "... not connected" << std::endl;
		  int error = GetLastError();
		return 0;
	  }
	  else
	  {
		  std::cout << "... success!!!" << std::endl;
		  return new FHSocket(m_handle, 0);
	  }
  }
  
} // end of namespace net
