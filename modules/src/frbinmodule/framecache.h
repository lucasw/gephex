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

#ifndef INCLUDED_FRAME_CACHE_H
#define INCLUDED_FRAME_CACHE_H

#include <string>
#include <memory>

#include "basic_types.h"

class FrameCache
{
 public:
  FrameCache(int size_in_mbytes);
  
  ~FrameCache();

  /**
   * Store one frame in the cache.
   * The cache is new owner of framebuffer, so don't modify
   * it afterwards (and don't delete it!!!)
   *
   * framebuffer must have been allocated with new[].
   */
  void store(const std::string& file_name, int frame_number,
             int width, int height, uint_32* framebuffer);

  /**
   * Returns 0 on cache miss.
   */
  uint_32* lookup(const std::string& file_name, int frame_number,
                  int width, int height) const;

  void flush();

 private:
  class Impl;
  std::auto_ptr<Impl> m_impl;
};
#endif
