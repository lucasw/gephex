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

#ifndef __INCLUDED_IFS_TYPE_H__
#define __INCLUDED_IFS_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

#define IFS_MAX_FUN 32

typedef struct IfsType_
{
  double ifs[IFS_MAX_FUN][6];
  int numfun;
} IfsType;


static __inline void ifs_initInstance(IfsType* newType)
{
	newType->numfun = 0;
}


static __inline IfsType* ifs_newInstance(void)
{
	IfsType* newType = (IfsType*) malloc(sizeof(IfsType));
	ifs_initInstance(newType);
	return newType;
}


static __inline void ifs_assign(IfsType* dst,const IfsType* src)
{
  memcpy(dst->ifs,src->ifs,sizeof(IfsType));
}


static __inline void ifs_deleteInstance(IfsType* num)
{
	free(num);
}

#endif
