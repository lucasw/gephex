#ifndef INCLUDED_UDP_SOCKET_H
#define INCLUDED_UDP_SOCKET_H

#include "isocket.h"

namespace net
{

  class UDPSocket : public ISocket
  {
  public:
    UDPSocket(int localPort = 0);
    virtual ~UDPSocket();

    virtual int send(const utils::Buffer& data) 
      /*const throw (IOException,UnknownHostException)*/;
    
    virtual void connect(const std::string& hostName, int portNum);

    virtual void disconnect();

    virtual void listen();
  
    virtual void accept() ;
    
    virtual utils::Buffer receive() 
      const throw (IOException,InterruptedIOException);
    
    virtual void setSoTimeout(int timeout);
    
    virtual int soTimeout() const;
    
    virtual int port() const;

    virtual bool connected() const;

  private:
    int localPort;
    int m_socket;
    int timeout;
	
	void* m_addr;

	bool _isConnected;
  };
  
} // end of namepsace net

#endif
