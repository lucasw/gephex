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

#include "tagger.h"

namespace net {
  
  template <typename Tag, typename TagUtil>
  Tagger<Tag, TagUtil>::Tagger()
    : m_interpreter(0)
  {
  }

  template <typename Tag, typename TagUtil>
  Tagger<Tag, TagUtil>::Tagger(ITagInterpreter<Tag>& i)
    : m_interpreter(&i)
  {
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::registerInterpreter(ITagInterpreter<Tag>& i)
  {
    m_interpreter = &i;
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::registerSender(ISender& s)
  {
    m_sender = &s;
  }
 
  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::setTag(const Tag& t)
  {
    m_tag = t;
  }

  template <typename Tag, typename TagUtil>
  int Tagger<Tag, TagUtil>::send(const utils::Buffer& b)
  {
    utils::Buffer taggedData;
    TagUtil::attachTag(taggedData, m_tag, b);

    return m_sender->send(taggedData);
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::dataReceived(const utils::Buffer& taggedData)
  {
    Tag tag;
    utils::Buffer data;

    //TODO: exceptions???
    TagUtil::removeTag(data, tag, taggedData);

    m_interpreter->dataReceived(tag, data);
  }

}
