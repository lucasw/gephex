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

typedef unsigned int uint_32;
typedef signed int   int_32;

typedef unsigned short uint_16;
typedef signed short int_16;

typedef unsigned char uint_8;
typedef signed char int_8;

#define UINT32_MAX UINT_MAX
#define INT32_MAX INT_MAX

#endif

