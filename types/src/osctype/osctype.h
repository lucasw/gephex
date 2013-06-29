/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#ifndef __INCLUDED_OSC_TYPE_H__
#define __INCLUDED_OSC_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "basic_types.h"

typedef struct OscType_
{
  int len;
  int capacity;
  unsigned char* data;
} OscType;

static __inline int osc_invariant(const OscType* osc)
{
  return (osc->len % 4) == 0;
}

static __inline void osc_initInstance(OscType* newType)
{
  newType->len = 0;
  newType->capacity = 0;
  newType->data = 0;
  assert( osc_invariant(newType) );
}

static __inline OscType* osc_newInstance(void)
{
  OscType* newType = (OscType*) malloc(sizeof(OscType));
  osc_initInstance(newType);
  assert( osc_invariant(newType) );
  return newType;
}

static __inline void osc_resize(OscType* dst, int newSize)
{
  assert( osc_invariant(dst) );
  unsigned char* newData;
  
  if (newSize < dst->len)
    return;

  newData = (unsigned char*) malloc(newSize);
  
  if (dst->data != 0)
    {
      memcpy(newData, dst->data, dst->len);
      free(dst->data);
    }

  dst->capacity = newSize;
  dst->data = newData;
  assert( osc_invariant(dst) );
}

static __inline void osc_set_buffer(OscType* dst, unsigned char* buf,
				     int len)
{
  assert( osc_invariant(dst) );

  osc_resize(dst, len);

  assert(dst->capacity >= len);
  assert(dst->data != 0);

  memcpy(dst->data, buf, len);
  dst->len = len;
  assert( osc_invariant(dst) );
}

static __inline void osc_assign(OscType* dst, const OscType* src)
{
  assert( osc_invariant(dst) );
  assert( osc_invariant(src) );
  
  osc_resize(dst, src->len);
  
  assert(dst->capacity >= src->len);
  assert(dst->data != 0);

  memcpy(dst->data, src->data, src->len);
  dst->len = src->len;

  assert( osc_invariant(dst) );
  assert( osc_invariant(src) );
}

static __inline void osc_deleteInstance(OscType* dst)
{
  assert( osc_invariant(dst) );

  if (dst->data != 0)
    free(dst->data);

  free(dst);
}

static __inline int osc_serialize(const OscType* pos, char* buffer, int bufferLen)
{
  assert( osc_invariant(pos) );
  return 0;
}

static __inline void osc_deSerialize(const char* buffer,int len,
				      OscType* pos)
{
    assert( osc_invariant(pos) );
}

#endif
