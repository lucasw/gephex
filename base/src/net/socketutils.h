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

#ifndef INCLUDED_SOCKET_UTILS_H
#define INCLUDED_SOCKET_UTILS_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

namespace net {

#if defined(OS_POSIX)
  static const int SOCKET_ERROR = -1;
  static const int INVALID_SOCKET = -1;
#endif

class SocketUtils
  {
  public:
    static void closeSocket(int& socket);

    /**
     * Returns wether a read on fd will block.
     * @param fd the file descriptor
     * @param timeout the timeout in ms
     * @return wether a read to fd will block
     */
    static bool doesReadBlock(int fd, int timeout);

	/**
	 * For the stupid win32 WSAStartup shit
	 */
	static void initNetwork();

	/**
	 * For the stupid win32 WSACleanup shit
	 */
	static void shutDownNetwork();
  };

}
#endif
