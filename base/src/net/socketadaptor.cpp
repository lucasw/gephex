/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "socketadaptor.h"

#include "isocket.h"
#include "idatalistener.h"

#include "utils/buffer.h"

namespace net {
  SocketAdaptor::SocketAdaptor(ISocket* socket, IDataListener* listener)
    : m_socket(socket), m_listener(listener)
  {
  }

  void SocketAdaptor::setSocket(ISocket* socket)
  {
    m_socket = socket;
  }

  void SocketAdaptor::registerDataListener(IDataListener& listener)
  {
    m_listener = &listener;
  }


  int SocketAdaptor::run()
  {
    if (m_socket == 0)
      return 0;

    utils::Buffer b(1024);
    bool dataArrived = m_socket->receive(b);

    if (dataArrived && m_listener)
      m_listener->dataReceived(b);

	return b.getLen();
  }
}
