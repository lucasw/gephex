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
