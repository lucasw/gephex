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

#include <stdlib.h>
#include <stdio.h>

#include "basic_types.h"

typedef struct RGBType_
{
	float r;
	float g;
	float b;
} RGBType;

static __inline void rgb_initInstance(RGBType* newType)
{
	newType->r = 0.f;
	newType->g = 0.f;
	newType->b = 0.f;
}

static __inline RGBType* rgb_newInstance(void)
{
	RGBType* newType = (RGBType*) malloc(sizeof(RGBType));
	rgb_initInstance(newType);
	return newType;
}
static __inline void rgb_assign(RGBType* dst,const RGBType* src)
{
	dst->r = src->r;
	dst->g = src->g;
	dst->b = src->b;
}

static __inline void rgb_deleteInstance(RGBType* rgb)
{
	free(rgb);
}

static __inline int rgb_serialize(const RGBType* rgb, char* buffer,
				  int bufferLen)
{
	int reqLen = 5*3 + 2 + 1;

	if (bufferLen >= reqLen && buffer != 0)
	{
	  sprintf(buffer,"%.3f %.3f %.3f", rgb->r, rgb->g, rgb->b);
	}

	return reqLen;
}

static __inline void rgb_deSerialize(const char* buffer, int len, RGBType* rgb)
{
	if (buffer[0] == 0)
	{
		rgb_initInstance(rgb);
	}
	else
	{
		sscanf(buffer,"%f %f %f",&rgb->r, &rgb->g, &rgb->b);
	}
}

static __inline uint_8 color_comp_to_byte(double c)
{
  return (uint_8) (c * 255 +.5);
}
