#include "servernetsocket.h"

#include <iostream>

#include "idatalistener.h"
#include "tcpsocket.h"
#include "udpsocket.h"

#include "utils/buffer.h"

namespace net
{
  ServerNetSocket::ServerNetSocket(int portnum, bool useUDP)
    : dListener(0)
{
  if (useUDP)
	  m_socket = utils::AutoPtr<ISocket>(new UDPSocket(portnum));
  else
	  m_socket = utils::AutoPtr<ISocket>(new TCPSocket(portnum));

  m_socket->setSoTimeout(0);

  m_socket->listen();
}

ServerNetSocket::~ServerNetSocket()
{
  m_socket->disconnect();
}

void ServerNetSocket::setDataListener(IDataListener& listener)
{
  dListener = &listener;
}


void ServerNetSocket::buildConnection() 
  throw(std::runtime_error)
{
  m_socket->accept();
  if (m_socket->connected())
	m_socket->setSoTimeout(0);
}

void ServerNetSocket::run()
{
  if (!m_socket->connected())
    return;

  utils::Buffer buf = m_socket->receive();

  if (buf.getLen() != 0 && dListener != 0)
    dListener->dataReceived(buf);
}

int ServerNetSocket::send(const utils::Buffer& data) throw(std::runtime_error)
{
  return m_socket->send(data);
}

void ServerNetSocket::disconnect()
{
  m_socket->disconnect();
}

bool ServerNetSocket::isConnected()
{
  return m_socket->connected();
}


} //end of namespace
