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

#ifndef INCLUDED_PROTOCOL_H
#define INCLUDED_PROTOCOL_H

#include <map>
#include <string>
#include <stdexcept>

#include "idatalistener.h"
#include "isender.h"

namespace utils {
  class Buffer;
}

namespace net
{

/**
 * The Protocol class makes sure that data sent/received through
 * it is sent/received in complete packages only.
 *
 * Some implementation of ISender don't have the property that
 * data is sent in whole packages. They repackage the data and it may
 * be received in multiple smaller packages.
 *
 * The Protocol class can simply be inserted into the sender/receiver
 * chain (because it implements ISender and IDataListener) and makes
 * sure that data is delivered in whole packages only.
 *
 */
class Protocol : public ISender, public IDataListener
{
public:
  Protocol();
  Protocol(IDataListener&);

  virtual ~Protocol();

  /**
   * Sets the data-istener, to whom received data is forwarded.
   * @param listener the data-listener that receives incoming data.
   */
  void registerListener(IDataListener& listener);
  
  /**
   * Sets the sender which is used for forwarding the data. 
   * The sender has to be set before send() is called.
   * @param sender The sender that is used for forwarding, if 0 the data is lost
   */
  void registerSender(ISender* sender);

  virtual int send(const utils::Buffer&);

  virtual void dataReceived(const utils::Buffer& buf);

  /**
   * Resets the protocol. All data in the buffer is discarded.
   * Use with care!
   */
  void reset();

private:
  ISender* m_sender;
  IDataListener* m_listener;

  unsigned char* bufferBegin;
  unsigned char* bufferPos;
  unsigned char* bufferEnd;

  bool m_silent_mode;
  void read(const unsigned char*& dataPos,const unsigned char* dataEnd,
	    int bytesToRead, int& bytesLeft);
};


} //end of namespace

#endif
