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

#ifndef __INCLUDED_NUMBER_TYPE_H__
#define __INCLUDED_NUMBER_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "basic_types.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

typedef struct NumberType_
{
  double number;
} NumberType;

static __inline void number_initInstance(NumberType* newType)
{
	newType->number = 0;
}

static __inline NumberType* number_newInstance(void)
{
	NumberType* newType = (NumberType*) malloc(sizeof(NumberType));
	number_initInstance(newType);
	return newType;
}
static __inline void number_assign(NumberType* dst,const NumberType* src)
{
	dst->number = src->number;
}

static __inline void number_deleteInstance(NumberType* num)
{
	free(num);
}

static __inline int number_serialize(const NumberType* number,
				     char* buffer, int bufferLen)
{
	if (bufferLen < 20 || buffer == 0)
	{
		return 20;
	}
	else
	{
		snprintf(buffer, bufferLen, "%.14g", number->number);

		//	printf("Serializing number to '%s'\n", buffer);

		return strlen(buffer)+1;
	}
}

static __inline void number_deSerialize(const char* buffer,int len,
					NumberType* number)
{
	if (buffer[0] == 0)
	{
		number_initInstance(number);
	}
	else
	{
	  //		sscanf(buffer,"%f",&number->number);
	  number->number = atof(buffer);
	  //printf("De-Serializing number from '%s' to %g\n", buffer,
	  //	       number->number);
	}
}

static __inline int trim_int(double val, int low_val, int high_val)
{
  int r;
  
  if (val >= 0)
	  r = (int) (val+0.5);
  else
	  r = (int) (val-0.5);

  if (r < low_val)
    return low_val;
  else if (r > high_val)
    return high_val;

  return r;
}

static __inline int trim_bool(double val)
{
  return trim_int(val,0,1) != 0;
}

static __inline double trim_double(double val, double low_val, double high_val)
{
  if (val < low_val)
    return low_val;
  else if (val > high_val)
    return high_val;

  return val;
}

#endif
