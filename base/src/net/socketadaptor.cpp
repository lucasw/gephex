#include "socketadaptor.h"

#include "isocket.h"
#include "idatalistener.h"

#include "utils/buffer.h"

namespace net {
  SocketAdaptor::SocketAdaptor(ISocket* socket, IDataListener* listener)
    : m_socket(socket), m_listener(listener)
  {
  }

  void SocketAdaptor::setSocket(ISocket& socket)
  {
    m_socket = &socket;
  }

  void SocketAdaptor::registerDataListener(IDataListener& listener)
  {
    m_listener = &listener;
  }


  void SocketAdaptor::run()
  {
    if (m_socket == 0)
      return;

    utils::Buffer b;
    bool dataArrived = m_socket->receive(b);

    if (dataArrived && m_listener)
      m_listener->dataReceived(b);
  }
}
