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

#include "twolayermodule.h"
#if defined(HAVE_STDINT_H)
#include <stdint.h>
#else
typedef uint_32 uint32_t;
#endif
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

inline int grey(uint32_t& rgb)
{
  return ((rgb>>8)&0xFF);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  
  // set the attribs of the output equal to the input
  FrameBufferAttributes attribs;
  framebuffer_getAttributes(inst->in_b, &attribs);
  framebuffer_changeAttributes(inst->out_r, &attribs);

  
  int xsize      = inst->in_b->xsize;
  int ysize      = inst->in_b->ysize;
  uint_32* fb    = inst->in_b->framebuffer;
  uint_32* outfb = inst->out_r->framebuffer;
  
  std::vector<unsigned int> hist(256,0);

  // create histogramm
  for (uint_32* pixel=fb;pixel!=fb+(xsize*ysize);++pixel)
    {
      ++hist[static_cast<unsigned char>(grey(*pixel))];
    }

  // calc th
  int th=127;
  int th_old=0;

  while (th!=th_old)
    {
      th_old=th;
      // calc low
      double num = 0;
      double val = 0;
      for (int i= (int)(th-1); i!= -1; --i)
	{
	  num += hist[i];
	  val += hist[i]*i;
	}
      unsigned char low = static_cast<unsigned char>(val/num);

      // clac hi
      for (unsigned int i=th;i!=256;++i)
	{
	  num += hist[i];
	  val += hist[i]*i;
	}
      unsigned char hi = static_cast<unsigned char>(val/num);

      th = (low + hi) / 2;
    }
  
  // create b/w image with the th value
  {
	uint_32* outpixel= outfb;
	uint_32* pixel=fb;
	while(pixel!=fb+(xsize*ysize))
	  {
	    if (grey(*pixel)<th)
	      *outfb=0x00000000;
	    else
	      *outfb=0xFFFFFFFE;
	    ++outfb;
	    ++pixel;
	  }
      }  
}

