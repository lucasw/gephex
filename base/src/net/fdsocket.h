#ifndef INCLUDED_FD_SOCKET_H
#define INCLUDED_FD_SOCKET_H

#include "isocket.h"

namespace net
{

  /**
   * FDSocket provides socket functionality based on a file descriptor.
   * The file descriptor has to be a valid, connected socket.
   */
  class FDSocket : public ISocket
  {
  public:
    FDSocket(int fd, int localPort);
    virtual ~FDSocket();

    virtual int send(const utils::Buffer& data) 
      /*const throw (IOException,SocketException)*/;
    
    virtual bool receive(utils::Buffer& b) throw (IOException);
    
    virtual bool connected() const;

  private:
    int m_fd;
    bool m_isConnected;
  };
  
} // end of namepsace net

#endif
