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

#ifndef INCLUDED_LFO_TYPE_H
#define INCLUDED_LFO_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

typedef struct LfoType_
{
	double amount;
	double frequenz;
} LfoType;

static __inline void lfo_initInstance(LfoType* newType)
{
	newType->amount = 0.0;
	newType->frequenz = 0.0;
}

static __inline LfoType* lfo_newInstance(void)
{
	LfoType* newType = (LfoType*) malloc(sizeof(LfoType));
	lfo_initInstance(newType);
	return newType;
}
static __inline void lfo_assign(LfoType* dst,const LfoType* src)
{
	dst->amount = src->amount;
	dst->frequenz = src->frequenz;
}

static __inline void lfo_deleteInstance(LfoType* lfo)
{
	free(lfo);
}

static __inline int lfo_serialize(const LfoType* lfo, char* buffer, int bufferLen)
{
	if (buffer == 0 || bufferLen < 26)
		return 26;
	else
	{
		sprintf(buffer,"%g %g",lfo->amount, lfo->frequenz);
		return strlen(buffer)+1;	
	}
}

static __inline void lfo_deSerialize(const char* buffer,int len, LfoType* lfo)
{
	if (buffer[0] == 0)
	{
		lfo_initInstance(lfo);
	}
	else
	{
	  char* endptr;

	  lfo->amount = strtod(buffer, &endptr);
	  lfo->frequenz = strtod(endptr, 0);
	}
}

#endif
