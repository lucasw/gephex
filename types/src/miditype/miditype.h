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

#ifndef __INCLUDED_MIDI_TYPE_H__
#define __INCLUDED_MIDI_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "basic_types.h"

typedef struct MidiType_
{
  int len;
  int capacity;
  unsigned char* data;
} MidiType;

static __inline void midi_initInstance(MidiType* newType)
{
  newType->len = 0;
  newType->capacity = 0;
  newType->data = 0;
}

static __inline MidiType* midi_newInstance(void)
{
  MidiType* newType = (MidiType*) malloc(sizeof(MidiType));
  midi_initInstance(newType);
  return newType;
}

static __inline void midi_resize(MidiType* dst, int newSize)
{
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
}

static __inline void midi_set_buffer(MidiType* dst, unsigned char* buf,
				     int len)
{
  midi_resize(dst, len);

  assert(dst->capacity >= len);
  assert(dst->data != 0);

  memcpy(dst->data, buf, len);
  dst->len = len;
}

static __inline void midi_assign(MidiType* dst, const MidiType* src)
{
  midi_resize(dst, src->len);
  
  assert(dst->capacity >= src->len);
  assert(dst->data != 0);

  memcpy(dst->data, src->data, src->len);
  dst->len = src->len;
}

static __inline void midi_deleteInstance(MidiType* dst)
{
  if (dst->data != 0)
    free(dst->data);

  free(dst);
}

static __inline int midi_serialize(const MidiType* pos, char* buffer, int bufferLen)
{
  return 0;
}

static __inline void midi_deSerialize(const char* buffer,int len,
				      MidiType* pos)
{
}

#endif
