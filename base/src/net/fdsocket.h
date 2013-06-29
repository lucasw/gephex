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
