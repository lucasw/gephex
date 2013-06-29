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

#include "tagdispatcher.h"

#include "idatalistener.h"

#include <sstream>

namespace net {

  template <typename Tag>
  TagDispatcher<Tag>::TagDispatcher() {}

  template <typename Tag>
  TagDispatcher<Tag>::~TagDispatcher() {}

  template <typename Tag>
  void TagDispatcher<Tag>::registerListener(const Tag& t,
					    IDataListener& listener)
  {
    m_listeners.insert(std::make_pair(t, &listener));
  }

  template <typename Tag>
  void TagDispatcher<Tag>::dataReceived(const Tag& tag, const utils::Buffer& b)
  {
    typename ListenerMap::const_iterator it = m_listeners.find(tag);
    if (it == m_listeners.end())
      {
	std::ostringstream os;
	os << "No listener found for Tag = `" << tag << "`"
	   << std::endl;

	throw std::runtime_error(os.str().c_str());
      }
    else
      {
	IDataListener* listener = it->second;
	listener->dataReceived(b);
      }
  }
}
