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

#ifndef __INCLUDED_POSITION_TYPE_H__
#define __INCLUDED_POSITION_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

typedef struct PositionType_
{
	double x;
	double y;
} PositionType;

static __inline void pos_initInstance(PositionType* newType)
{
	newType->x = 0;
	newType->y = 0;
}

static __inline PositionType* pos_newInstance(void)
{
	PositionType* newType = (PositionType*) malloc(sizeof(PositionType));
	pos_initInstance(newType);
	return newType;
}
static __inline void pos_assign(PositionType* dst,const PositionType* src)
{
	dst->x = src->x;
	dst->y = src->y;
}

static __inline void pos_deleteInstance(PositionType* pos)
{
	free(pos);
}

static __inline int pos_serialize(const PositionType* pos, char* buffer, int bufferLen)
{
	if (buffer == 0 || bufferLen < 26)
		return 26;
	else
	{
		sprintf(buffer,"%g %g",pos->x, pos->y);
		return strlen(buffer)+1;	
	}
}

static __inline void pos_deSerialize(const char* buffer,int len, PositionType* pos)
{
	if (buffer[0] == 0)
	{
		pos_initInstance(pos);
	}
	else
	{
	  char* endptr;

	  pos->x = strtod(buffer, &endptr);
	  pos->y = strtod(endptr, 0);
	}
}

#endif
