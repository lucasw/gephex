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

#include "pixelizemodule.h"

//---------------------------------------------------------------------------

static logT s_log;

static uint_32 average(const uint_32* start,
                       int bxsize,
                       int bysize, int xsize);

static void fill_block(uint_32* start,
                       int bxsize,
                       int bysize,
                       int xsize, uint_32 col);

//---------------------------------------------------------------------------

#ifndef min
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
#endif

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

  if (my == 0)
  {
	  s_log(0, "Could not allocate memory for MyInstance struct\n");
	  return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  FrameBufferAttributes attribs;

  int xsize = inst->in_src->xsize;
  int ysize = inst->in_src->ysize;
  int bsizex = trim_int(inst->in_bsize->number, 1, xsize);
  int bsizey = trim_int(inst->in_bsizey->number, 0, ysize);

  int blocks_x;
  int blocks_y;
  int xrest;
  int yrest;

  int xi, yi;
  const uint_32* src;
  uint_32* dst;
  int offset;

  if (bsizey == 0)
    bsizey = min(ysize, bsizex);

  blocks_x = xsize / bsizex;
  blocks_y = ysize / bsizey;
  xrest = xsize - blocks_x*bsizex;
  yrest = ysize - blocks_y*bsizey;

  

  if (bsizex == 1 && bsizey == 1)
    return;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  src = inst->in_src->framebuffer;
  dst = inst->out_r->framebuffer;
  offset = 0;
  for (yi = 0; yi < blocks_y; ++yi)
  {	  
	  offset = yi*bsizey*xsize;
	  for (xi = 0; xi < blocks_x; ++xi)
	  {
		  uint_32 col = average(src + offset, bsizex, bsizey, xsize);
		  fill_block(dst + offset, bsizex, bsizey, xsize, col);
		  offset += bsizex;
	  }
	  if (xrest > 0)
	  {
		  uint_32 col = average(src + offset, xrest, bsizey, xsize);
		  fill_block(dst + offset, xrest, bsizey, xsize, col);
	  }
  }
  if (yrest > 0)
  {
      offset = blocks_y*bsizey*xsize;
	  for (xi = 0; xi < blocks_x; ++xi)
	  {
		  uint_32 col = average(src + offset, bsizex, yrest, xsize);
		  fill_block(dst + offset, bsizex, yrest, xsize, col);
		  offset += bsizex;
	  }
	  if (xrest > 0)
	  {
		  uint_32 col = average(src + offset, xrest, yrest, xsize);
		  fill_block(dst + offset, xrest, yrest, xsize, col);
	  }
  }
}

void patchLayout(Instance* inst, int out2in[])
{
  int xsize = inst->in_src->xsize;
  int ysize = inst->in_src->ysize;
  int bsizex = trim_int(inst->in_bsize->number, 1, xsize);
  int bsizey = trim_int(inst->in_bsizey->number, 0, ysize);

  if (bsizey == 0)
    bsizey = min(ysize, bsizex);

  if (bsizex == 1 && bsizey == 1)
    out2in[out_r] = in_src;
}

//----------------------------------------------------------------------

static uint_32 average(const uint_32* start, int bxsize, int bysize, int xsize)
{
	const uint_32* p = start;
	uint_32 red = 0, green = 0, blue = 0;
	uint_32 avg_red, avg_green, avg_blue;
	int x, y;
	const uint_32* pp;
	uint_32 c;

	for (y = 0; y < bysize; ++y)
	{
		pp = p;
		for (x = 0; x < bxsize; ++x)
		{
			c = *(pp++);
			red   += (c & 0x00ff0000) >> 16;
			green += (c & 0x0000ff00) >> 8;
			blue  += (c & 0x000000ff);
		}
		p += xsize;
	}
	
	avg_red   = (red   / (bxsize*bysize)) & 0xff;
	avg_green = (green / (bxsize*bysize)) & 0xff;
	avg_blue  = (blue  / (bxsize*bysize)) & 0xff;

	return (avg_red << 16) + (avg_green << 8) + avg_blue;
}

static void fill_block(uint_32* start, int bxsize, int bysize,
                       int xsize, uint_32 col)
{
	uint_32* p = start;
	int x, y;
	uint_32* pp;

	for (y = 0; y < bysize; ++y)
	{
		pp = p;
		for (x = 0; x < bxsize; ++x)
		{
			*(pp++) = col;
		}
		p += xsize;
	}

}
