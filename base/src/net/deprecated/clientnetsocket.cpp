#include "clientnetsocket.h"

#include <iostream>

#include "idatalistener.h"
#include "tcpsocket.h"
#include "udpsocket.h"

#include "utils/buffer.h"

namespace net
{
  ClientNetSocket::ClientNetSocket(const std::string& remoteHost,
				   int remotePort, bool useUDP)
    : dListener(0),
    m_remoteHost(remoteHost), m_remotePort(remotePort)
{
  if (useUDP)
	  m_socket = utils::AutoPtr<ISocket>(new UDPSocket());
  else
	  m_socket = utils::AutoPtr<ISocket>(new TCPSocket());

  m_socket->setSoTimeout(0);
}

ClientNetSocket::~ClientNetSocket()
{
  m_socket->disconnect();
}

void ClientNetSocket::setDataListener(IDataListener& listener)
{
  dListener = &listener;
}

void ClientNetSocket::buildConnection() 
  throw(std::runtime_error)
{
  m_socket->connect(m_remoteHost,m_remotePort);
  m_socket->setSoTimeout(0);
}

void ClientNetSocket::run()
{
  if (!m_socket->connected())
    return;

  utils::Buffer buf = m_socket->receive();

  if (buf.getLen() != 0 && dListener != 0)
    dListener->dataReceived(buf);
}

int ClientNetSocket::send(const utils::Buffer& data) /*throw(std::runtime_error)*/
{
  return m_socket->send(data);
}

void ClientNetSocket::disconnect()
{
  m_socket->disconnect();
}

bool ClientNetSocket::isConnected()
{
  return m_socket->connected();
}


} //end of namespace
