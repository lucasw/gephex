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

#ifndef INCLUDED_COLORCONV_H
#define INCLUDED_COLORCONV_H

#include <stdint.h>

/**
 * converts an image in yuv411p to an image bgra32
 * xSize and ySize must be multiples of 2
 */
void init_tabs(); // call this once
void yuv411p_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize);

void rgb32_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize);

void bgra32_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize);

#endif
