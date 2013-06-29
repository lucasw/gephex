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

#ifndef INCLUDED_INETSOCKET_H
#define INCLUDED_INETSOCKET_H

#include <string>
#include <stdexcept>

#include "isender.h"

namespace net
{

  class IDataListener;

  /**
   *  This class provides a high level interface for network sockets.
   */
  class INetSocket : public ISender
  {
  public:

    /**
     * TODO
     */
    virtual void setDataListener(IDataListener& listener) = 0;

    /** 
     * Versucht eine Verbindung aufzubauen. Wenn isConnected() == true
     * passiert nix. Wenn die Verbindung nicht aufgebaut werden kann
     * wird eine Exception geworfen //TODO!!!!!
     * Ob die Methode blockiert hängt von der konkreten Implementierung ab.
     */
    virtual void buildConnection() throw(std::runtime_error) = 0;

    /**
     *
     */
    //    virtual int send(const utils::Buffer& buf) throw(std::runtime_error);


    /**
     * Schau ob Daten angekommen sind. Wenn ja wird der DataListener
     * aufgerufen.
     * Ob die Methode blockiert hängt von der konkreten Implementierung ab.
     */
    virtual void run() = 0;
	
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;
  };

} // end of namespace net

#endif
