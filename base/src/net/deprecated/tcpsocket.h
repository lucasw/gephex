#ifndef INCLUDED_TCP_SOCKET_H
#define INCLUDED_TCP_SOCKET_H

#include "isocket.h"

namespace net
{

  class TCPSocket : public ISocket
  {
  public:
    TCPSocket(int localPort = 0);
    virtual ~TCPSocket();

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
    int serverSocket;
    int readySocket;
    int timeout;

    bool _isConnected;
  };
  
} // end of namepsace net

#endif
