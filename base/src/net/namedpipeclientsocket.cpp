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

  static int release_handle(void* h)
  {
	  return CloseHandle(h);
  }

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

	  //std::cout << "Trying to connect to Pipe '" << name << "'..." << std::endl;
	  
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
		  //std::cout << "... not connected" << std::endl;
		  int error = GetLastError(); //TODO
		return 0;
	  }
	  else
	  {
		  //std::cout << "... success!!!" << std::endl;
		  return new FHSocket(m_handle, release_handle, 0);
	  }
  }
  
} // end of namespace net
