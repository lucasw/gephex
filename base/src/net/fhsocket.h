#ifndef INCLUDED_FH_SOCKET_H
#define INCLUDED_FH_SOCKET_H

#include "isocket.h"

namespace net
{

  /**
   * FHSocket provides socket functionality based on a win32 file handle.
   * The file descriptor has to be a valid, connected socket.
   */
  class FHSocket : public ISocket
  {
  public:
    FHSocket(void* fh, int localPort);
    virtual ~FHSocket();

    virtual int send(const utils::Buffer& data) 
      /*const throw (IOException,SocketException)*/;
    
    virtual bool receive(utils::Buffer& b) throw (IOException);
    
    virtual bool connected() const;

  private:
    void* m_fh;
    bool m_isConnected;
  };
  
} // end of namepsace net

#endif
