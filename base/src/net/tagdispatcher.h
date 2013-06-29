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

#ifndef INCLUDED_TAG_DISPATCHER_H
#define INCLUDED_TAG_DISPATCHER_H

#include <map>

#include "itaginterpreter.h"

namespace net {

  class IDataListener;

  /**
   * Dispatches incoming tagged data depending on the tag to
   * different listeners.
   *
   * For example, you could use a TagDispatcher<int> to model
   * data that is sent to different ports. The TagDispatcher will
   * then automatically dispatch on the port number and forward
   * the data to the correct receiver.
   */
  template<typename Tag>
  class TagDispatcher : public ITagInterpreter<Tag>
  {
  public:
    TagDispatcher();
    virtual ~TagDispatcher();

    /**
     * Registers a data-listener for a tag.
     * For every Tag t, there can be at most one listener.
     * If this method id called more than once with the same Tag,
     * only the last listener is used.
     *
     * @param tag the tag for which the listener wants to receive data
     * @param listener the listener that will receive the data
     */
    void registerListener(const Tag& tag, IDataListener& listener);

    /**
     * Tells the TagDispatcher that new tagged data has arrived.
     * If there is no listener for this tag, an std::runtime_error
     * is thrown.
     * @param tag the tag of the data
     * @param b the data itself
     */
    virtual void dataReceived(const Tag& tag, const utils::Buffer& b);


  private:
    typedef std::map<Tag, IDataListener*> ListenerMap;
    ListenerMap m_listeners;
  };
}

#include "tagdispatcher.cpp"
#endif
