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

#ifndef INCLUDED_CONVERT_BIN_H
#define INCLUDED_CONVERT_BIN_H

#include "basic_types.h"
/**
 *
 * Some functions to convert primitive data types to
 * and from a binary representation in little endian format.
 *
 */
namespace net
{
  /**
   * Casts the uint_32 to a raw representation in little endian
   * format.
   */
  void convert_uint32_to_le(uint_32 i, unsigned char raw[4]);

  /**
   * "Casts" an uint_32 from raw memory in a standard conforming
   * and platform independent way.
   * The memory is assumed to contain the uint_32 in little endian
   * format.
   * (Simply casting lead to bus errors on sparc32)
   */    
  uint_32 convert_uint32_from_le(const unsigned char* raw_data);
}

#endif
