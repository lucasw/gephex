#ifndef INCLUDED_SOCKET_ADAPTOR_H
#define INCLUDED_SOCKET_ADAPTOR_H

namespace net {
  class IDataListener;
  class ISocket;

  /**
   * This adaptor turns a socket into a datasender. You can
   * register a datalistener that receives the data that
   * arrives on the socket.
   * It turns the synchronous socket interface into the asynchronous
   * datalistener interface.
   */
  class SocketAdaptor
  {
  public:
    explicit SocketAdaptor(ISocket* socket = 0, IDataListener* listener = 0);

    void setSocket(ISocket& socket);

    void registerDataListener(IDataListener& listener);

    /**
     * Give control to the adaptor. This call is blocking
     * iff the underlying sockets receive method is blocking.
     */
    void run();

  private:
    ISocket* m_socket;
    IDataListener* m_listener;
  };
}

#endif
