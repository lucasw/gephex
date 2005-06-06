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

#ifndef INCLUDED_FRAMEBUFFER_TYPE_H
#define INCLUDED_FRAMEBUFFER_TYPE_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "basic_types.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#define FRAMEBUFFER_X_MAX 2048
#define FRAMEBUFFER_Y_MAX 2048

typedef struct FrameBufferAttributes_
{
  int xsize;
  int ysize;
} FrameBufferAttributes;

typedef struct FrameBufferType_
{
  // ptr to first valid pixel
  uint_32* framebuffer;
  int xsize;
  int ysize;	

  uint_32* data;
  int size;
} FrameBufferType;

static __inline
void framebuffer_initInstance(FrameBufferType* newType)
{
  int i;
  newType->xsize = 1;
  newType->ysize = 1;
  newType->size = newType->xsize * newType->ysize;
  newType->data = (uint_32*) malloc(newType->size*sizeof(*newType->data));
  newType->framebuffer = newType->data;

  for (i = newType->size-1; i >= 0; --i)
    newType->framebuffer[i] = 0;
}

static __inline
FrameBufferType* framebuffer_newInstance(void)
{
  FrameBufferType* 
    newType = (FrameBufferType*) malloc(sizeof(FrameBufferType));

  framebuffer_initInstance(newType);

  return newType;
}

static __inline
void framebuffer_destroyInstance(FrameBufferType* fbuffer)
{
  if (fbuffer->data)
    free(fbuffer->data);

  fbuffer->data  = fbuffer->framebuffer = 0;
  fbuffer->xsize = fbuffer->ysize = fbuffer->size = 0;
}

static __inline
void framebuffer_deleteInstance(FrameBufferType* fbuffer)
{
  if (fbuffer == 0)
    return;

  framebuffer_destroyInstance(fbuffer);

  free(fbuffer);
}

static __inline
void framebuffer_assign(FrameBufferType* dst,
			const FrameBufferType* src)
{
  
  dst->xsize = src->xsize;
  dst->ysize = src->ysize;
	
  if(dst->size < (src->xsize * src->ysize))
    {
      if (dst->data != 0)
	free(dst->data);

      dst->size = src->xsize*src->ysize;
      dst->data = (uint_32*) malloc(dst->size * sizeof(uint_32));
    }

  dst->framebuffer = dst->data;
  memcpy(dst->framebuffer,
	 src->framebuffer,
	 src->xsize * src->ysize * sizeof(uint_32));
}


static __inline
int framebuffer_serialize(const void* type, char* buffer,
			  int bufferLen)
{
#if defined(OPT_SERIALIZE_FRAMEBUFFER)	
  FrameBufferType* fb  = (FrameBufferType*)type;
  // generate 16*16*3 preview
  char* bufPtr;
  int deltaX;
  int deltaY;
  int reqLen = 16*16*3;
  int x;
  int y;
  uint_32* dataPtr;
  uint_32* dataPtrTmp;
  
  if (bufferLen >= reqLen && buffer != 0)
    {
      bufPtr=buffer;
      dataPtr=fb->data;
      deltaX=fb->xsize/17;
      deltaY=(fb->ysize/17)*fb->xsize;

      dataPtr+=deltaX/2;
      dataPtr+=deltaY/2;

      for (y=0;y!=16;++y)
	{
	  dataPtrTmp=dataPtr;
	  for (x=0;x!=16;++x)
	    {
	      (*bufPtr)=*(((uint_8*)dataPtr)+0);
	      ++bufPtr;
	      (*bufPtr)=*(((uint_8*)dataPtr)+1);
	      ++bufPtr;
	      (*bufPtr)=*(((uint_8*)dataPtr)+2);
	      ++bufPtr;
	      dataPtr+=deltaX;
	    }
	  dataPtr=dataPtrTmp;
	  dataPtr+=deltaY;
	}
    }
  
  return reqLen;
#else
	return 0;
#endif
}

static __inline
void framebuffer_deSerialize(const char* buffer,
			     int len, void* type)
{
}

// scale src to dst
// returns 1 on success
static __inline
int framebuffer_scale(FrameBufferType* dst,
		       const FrameBufferType* src,
		       int w, int h)
{
  int y;
  uint_32 x_a, y_a;
  uint_32 A,B;
  const uint_32* src_;
  uint_32* dst_;
  double deltax=.0, deltay=.0;

  if (w < 0 || h < 0)
	  return 0;

  dst->xsize = w;
  dst->ysize = h;
	
  if(dst->size < (w*h))
    {
	  uint_32* new_data;
	  new_data = (uint_32*) malloc(w*h*sizeof(uint_32));

	  if (new_data == 0)
		  return 0;

      if (dst->data)
	    free(dst->data);
      dst->size = w*h;
      dst->data = new_data;      
    }

  dst->framebuffer = dst->data;

  deltax = (double)src->xsize / (double)w ;
  deltay = (double)src->ysize / (double)h;

  A = (uint_32) (65536.*deltax);
  B = (uint_32) (65536.*deltay);

  y_a = 0;	

  src_ = src->framebuffer;
  dst_ = dst->framebuffer;	

  for (y = h; y != 0; --y)
    {
      int x;
      const uint_32* line_base;
      x_a = 0;
      line_base = src_ + ((y_a >> 16) * src->xsize);
      for (x = w; x != 0; --x)
	{
	  *dst_= line_base[x_a >> 16];
	  ++dst_;
	  x_a += A;
	}
      y_a += B;
    }

  return 1;
}

static __inline
void framebuffer_swap(FrameBufferType* fb1, FrameBufferType* fb2)
{
  FrameBufferType temp;
  memcpy(&temp, fb1, sizeof(*fb1));
  memcpy(fb1, fb2, sizeof(*fb1));
	
  memcpy(fb2, &temp, sizeof(*fb2));
}

static __inline
int framebuffer_attributesEqual(FrameBufferType* type,
				FrameBufferAttributes* attributes)
{
  return (attributes->xsize == type->xsize && attributes->ysize == type->ysize);
}

// returns 1 on success
static __inline
int framebuffer_convertType(FrameBufferType* dstType,
			     const FrameBufferType* srcType,
			     FrameBufferAttributes* attributes)
{
  return framebuffer_scale(dstType, srcType, attributes->xsize, attributes->ysize);
}

// returns 1 on success
static __inline
int framebuffer_changeAttributes(FrameBufferType* fb,
				  FrameBufferAttributes* attributes)
{
  FrameBufferType* newFb;

  if (framebuffer_attributesEqual(fb, attributes))
    return 1;

  newFb = framebuffer_newInstance();

  if (framebuffer_convertType(newFb, fb, attributes) != 1)
  {
	  framebuffer_deleteInstance(newFb);
	  return 0;
  }

  framebuffer_swap(newFb, fb);
  framebuffer_deleteInstance(newFb);

  return 1;
}

static __inline
void framebuffer_getAttributes(FrameBufferType* fb,
			       FrameBufferAttributes* attr)
{
  attr->xsize = fb->xsize;
  attr->ysize = fb->ysize;
}	

static __inline
void framebuffer_set_default(FrameBufferType* fb)
{
  FrameBufferAttributes attribs;
  attribs.xsize = 1;
  attribs.ysize = 1;
  framebuffer_changeAttributes(fb, &attribs);
  // set black background
  *(fb->data) = 0x00000000;
}

#endif
