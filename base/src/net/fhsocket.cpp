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

#include "fhsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if !defined(OS_WIN32)
#error "only win32"
#endif

#include <sstream>
#include <cassert>

#include <windows.h>

#include "netexceptions.h"
#include "utils/buffer.h"

namespace net
{
	static std::string get_error_text();
  	
	FHSocket::FHSocket(void* fh, fh_release_function_t release_function, int localPort)
		: ISocket(localPort), m_fh(fh), m_isConnected(true),
		   m_release_function(release_function)
	{
	}
	
	FHSocket::~FHSocket()
	{
		m_release_function(m_fh);
}
	
	int FHSocket::send(const utils::Buffer& data) 
		/*const throw (IOException,UnknownHostException)*/
	{
		if (!m_isConnected)
			throw IOException("Socket not connected at FHSocket::send!");
		
		if (m_fh == INVALID_HANDLE_VALUE)
			throw SocketException("Socket not valid at FHSocket::send!");
		
		unsigned long len = data.getLen();
		const unsigned char* buf = data.getPtr();

		if (len == 0)
			return 0;
		
		int left = len;
		int sent = 0;
		int zero_send = 2; // to prevent infinite cycle
		do {
			BOOL success = WriteFile(m_fh, reinterpret_cast<const char*>(buf), left, &len, 0);      
			if ( success && len > 0 ) 
			{
				sent += len;
				left -= len;
				buf += len;
			}
			else if (!success || len < 0)
			{	  
				std::ostringstream os;
				os << "Couldnt send: '" << get_error_text() << "'";
				throw IOException(os.str());
			}
			else
			{
				assert(len == 0);
				--zero_send;
			}
		}
		while ( (left > 0) && (len > 0) && zero_send);
		
		return sent;
	}
	
	bool FHSocket::receive(utils::Buffer& b) throw (IOException)
	{
		static const int MAX_MSG_LEN=1024;
		static unsigned char buf[MAX_MSG_LEN];
		
		if (!m_isConnected)
			throw IOException("Socket not connected!");
		
		
		unsigned long len;

		// see if there is data to be read
		if (!PeekNamedPipe(m_fh, 0, 0, 0, &len, 0))
		{
			throw IOException("Error at PeekNamedPipe!");
		}
  
		if (len > 0)
		{
		
			ReadFile(m_fh, reinterpret_cast<char*>(buf), MAX_MSG_LEN, &len, 0);
		
			if (len == 0)
			{
				throw IOException("Error at FHSocket::receive()");
			}			
			else
			{
				//TODO: use somthnh like b.setData(buf,len)
				b = utils::Buffer(buf,len);
				return true;
			}		
		}
		else
			return false;
	}
	
	bool FHSocket::connected() const
	{
		return m_isConnected;
	}

	//------------------------------------------------------------------

	static std::string get_error_text()
  {
    LPVOID lpMsgBuf;
    FormatMessage( 
                  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM | 
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR) &lpMsgBuf,
                  0,
                  NULL 
                  );

    char buffer[1024];
    _snprintf(buffer, sizeof(buffer), "%s", (LPCTSTR) lpMsgBuf);
    LocalFree( lpMsgBuf );

    return std::string(buffer, sizeof(buffer));
  }

} // end of namespace net
