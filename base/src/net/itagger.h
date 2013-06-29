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

#ifndef INCLUDED_ITAGGER_H
#define INCLUDED_ITAGGER_H

#include "isender.h"
#include "idatalistener.h"

namespace net {

  template <typename Tag>
  class ITagInterpreter;

  /**
   * ITagger is the abstract base class for classes that attach and
   * remove tags to data and forward it at the same time.
   * 
   * 
   */

  template <typename Tag>
  class ITagger : public ISender, public IDataListener
  {
  public:
    virtual ~ITagger() {}

    /**
     * Registers an interpreter for tagged data.
     *
     * @param interpreter the tag-interpreter that is called when
     *    tagged data is received
     */
    virtual void registerInterpreter(ITagInterpreter<Tag>& interpreter) = 0; 

    /**
     * Registers a sender object, that is internally used to forward
     * the data.
     * 
     * @param sender the sender object that is used for forwarding data
     */
    virtual void registerSender(ISender& sender) = 0;
    
    /**
     * Sets the tag that is attached to the data in future calls
     * to send.
     *
     * @param tag The tag that will be attached.
     */
    virtual void setTag(const Tag& tag) = 0;
  };
  
}

#endif
