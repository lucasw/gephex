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

#ifndef INCLUDED_BLOCK_H
#define INCLUDED_BLOCK_H

#include <cstdlib>
#include <iostream>

#include "config.h"


inline unsigned char* createRandomBlock(int len)
{
  unsigned char* data = new unsigned char[len];
  for (int i = 0; i < len; ++i)
#ifdef OS_POSIX
	data[i] = (char) (((double) random() / RAND_MAX) * 255.);
#endif
#ifdef OS_WIN32
    data[i] = (char) (((double) rand() / RAND_MAX) * 255.);
#endif
  return data;
}

inline bool compareBlocks(const unsigned char* d1, int l1,
			  const unsigned char* d2, int l2)
{
  if (l1 != l2)
    return false;

  for (int i = 0; i < l1; ++i)
    {
      if (d1[i] != d2[i])
	return false;
    }

  return true;
}

inline void printBlock(std::ostream& s,const unsigned  char* d, int l)
{
  s << l << '[';
  for (int i = 0; i < l; ++i)
    {
      s << (int) d[i];
      if (i != l-1)
	s << ',';
    }
  s << ']';
}
#endif
