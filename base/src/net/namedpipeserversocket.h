#ifndef INCLUDED_NAMED_PIPE_SERVER_SOCKET_H
#define INCLUDED_NAMED_PIPE_SERVER_SOCKET_H

#include "iserversocket.h"

namespace net
{
  class NamedPipeImpl;
  /**
   * Implementation of a server socket with named pipes (win32 only)
   */
  class NamedPipeServerSocket : public IServerSocket
  {

  public:
	/**
	 * The name of the pipe will be \\.\pipe\<localPort>,
	 * where <localPort> is the character representation (to the base 10)
	 * of localPort.
	 */
	  explicit NamedPipeServerSocket(int localPort);
	  virtual ~NamedPipeServerSocket();

    void listen() throw(std::runtime_error);

    ISocket* accept() throw(std::runtime_error);

  private:
	  NamedPipeImpl* m_impl;
  };

}

#endif
