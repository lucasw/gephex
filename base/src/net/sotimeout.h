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

#ifndef INCLUDED_SO_TIMEOUT_H
#define INCLUDED_SO_TIMEOUT_H

namespace net {

  /**
   * This class is inherited by all socket classes and
   * provides the timeout methods.
   */
  class SOTimeout
    {
    public:
      SOTimeout();
      
      /**
       * Enable/disable SO_TIMEOUT with the specified timeout
       * (in milliseconds).
       * If timeout is > 0, a call to receive() for 
       * this UDPSocket will block only for timeout ms. 
       * The option must be enabled prior to entering the blocking operation 
       * to have effect. 
       * The timeout must be >= -1. A timeout of -1 is interpreted as an 
       * infinite timeout. A timeout of 0 leads to non-blocking operation
       * If not set, the SO_TIMEOUT defaults to -1.
       */
      void setSoTimeout(int timeout);
      
      /**
       * Get the SO_TIMEOUT (see above).
       */
      int soTimeout() const;
      
    protected:
      int m_timeout;
  };
}
#endif
