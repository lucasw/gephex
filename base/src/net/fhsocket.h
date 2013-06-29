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
	  
    typedef int (*fh_release_function_t)(void*);
	  /**
	   * @param localPort ignored 	  
       */
	  FHSocket(void* fh, fh_release_function_t release_function, int localPort);
    virtual ~FHSocket();

    virtual int send(const utils::Buffer& data) 
      /*const throw (IOException,SocketException)*/;
    
    virtual bool receive(utils::Buffer& b) throw (IOException);
    
    virtual bool connected() const;

  private:
    void* m_fh;
    bool m_isConnected;
	fh_release_function_t m_release_function;
  };
  
} // end of namepsace net

#endif
