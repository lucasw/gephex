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

#ifndef INCLUDED_TAGGER_H
#define INCLUDED_TAGGER_H

#include "itagger.h"

namespace net {

  /**
   * This class implements the ITagger interface.
   * It uses a policy class TagUtil to actually attach and
   * remove tags to data.
   *
   * The policy class must provide two static methods:
   *
   * static void attachTag(utils::Buffer& dst,
   *			  const std::string& tag,
   *			  const utils::Buffer& b);
   *
   * static void removeTag(utils::Buffer& dst,
   *			  std::string& tag,
   *			  const utils::Buffer& src);
   *
   * For an example see tagutils.h.
   * @see StringTagUtil
   * @see UInt32TagUtil
   */
  template <typename Tag, typename TagUtil>
  class Tagger : public ITagger<Tag>
  {

    Tagger(const Tagger<Tag, TagUtil>&); // not impl.
    Tagger& operator=(const Tagger<Tag, TagUtil>&); // not impl.
  public:
    Tagger();
    Tagger(ITagInterpreter<Tag>& i);

    virtual void registerInterpreter(ITagInterpreter<Tag>& i);

    virtual void registerSender(ISender& s);
    
    virtual void setTag(const Tag& t);

    virtual int send(const utils::Buffer& b);

    virtual void dataReceived(const utils::Buffer& b);

  private:
    ITagInterpreter<Tag>* m_interpreter;
    Tag m_tag;

    ISender* m_sender;
  };
  
}

#include "net/tagger.cpp"

#endif
