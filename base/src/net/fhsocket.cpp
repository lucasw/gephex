#include "fhsocket.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if !defined(OS_WIN32)
#error "only win32"
#endif

#include <windows.h>

#include "netexceptions.h"

#include "utils/buffer.h"

namespace net
{
	
	FHSocket::FHSocket(void* fh, int localPort)
		: ISocket(localPort), m_fh(fh), m_isConnected(true)
	{
	}
	
	FHSocket::~FHSocket()
	{
		//TODO
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
		
		int left = len;
		int sent = 0;
		do {
			WriteFile(m_fh, reinterpret_cast<const char*>(buf), left, &len, 0);      
			if ( len > 0 ) 
			{
				sent += len;
				left -= len;
				buf += len;
			}
			else if (len == 0)
			{	  
				std::string msg = "Couldnt send: ";				
				throw IOException(msg);
			}
		}
		while ( (left > 0) && (len > 0) );
		
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
	
} // end of namespace net
