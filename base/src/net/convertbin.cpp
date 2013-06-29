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

#include "convertbin.h"

namespace net
{
    void convert_uint32_to_le(uint_32 i, unsigned char raw[4])
    {
      raw[0] = static_cast<unsigned char>((i & 0x000000ff) >> 0);
      raw[1] = static_cast<unsigned char>((i & 0x0000ff00) >> 8);
      raw[2] = static_cast<unsigned char>((i & 0x00ff0000) >> 16);
      raw[3] = static_cast<unsigned char>((i & 0xff000000) >> 24);
    }

    uint_32 convert_uint32_from_le(const unsigned char* raw_data)
    {
      return raw_data[0] | (raw_data[1] << 8) | (raw_data[2] << 16)
        | (raw_data[3] << 24);
    }
}
