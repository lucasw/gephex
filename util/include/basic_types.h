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

#ifndef INCLUDED_BASIC_TYPES_H
#define INCLUDED_BASIC_TYPES_H

#include <limits.h>

//typedef long long    int_64;
//typedef unsigned long long    uint_64;

#if _MSC_VER == 1200 //TODO
typedef unsigned int   uint32_t;
typedef signed int     int32_t;
typedef unsigned short uint16_t;
typedef signed short   int16_t;
typedef unsigned char  uint8_t;
typedef signed char    int8_t;
#else
#include <stdint.h>
#endif

typedef uint32_t uint_32;
typedef int32_t  int_32;

typedef uint16_t uint_16;
typedef int16_t int_16;

typedef uint8_t uint_8;
typedef int8_t  int_8;

#ifndef UINT32_MAX
#define UINT32_MAX UINT_MAX
#endif
#ifndef INT32_MAX
#define INT32_MAX INT_MAX
#endif

#endif

