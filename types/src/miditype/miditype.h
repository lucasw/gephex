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

  newData = malloc(newSize);
  
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
  if (len == 0)
    return;

  if (dst->capacity < len)
    midi_resize(dst, len);

  assert(dst->capacity >= len);
  assert(dst->data != 0);

  memcpy(dst->data, buf, len);
  dst->len = len;
}

static __inline void midi_assign(MidiType* dst, const MidiType* src)
{
  if (src->len == 0)
    return;

  if (dst->capacity < src->len)
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

static __inline int midi_serialize(MidiType* pos, char* buffer, int bufferLen)
{
  return 0;
}

static __inline void midi_deSerialize(const char* buffer,int len,
				      MidiType* pos)
{
}

#endif
