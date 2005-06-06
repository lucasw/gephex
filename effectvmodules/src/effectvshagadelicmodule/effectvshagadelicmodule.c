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

#include "effectvshagadelicmodule.h"

static logT s_log;

#ifndef M_PI
static const double M_PI = 3.14159265358979323846;
#endif

#include "libeffectv.h"
#include "sdldummy.h"
#include "shagadelic.c"

typedef struct _MyInstance {

  struct effectv_Effect* effect;

  double old_colors;

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

  my->old_colors = 0xffffff;

  my->effect = effectv_init(shagadelicRegister, 0, 0);

  if (my->effect)
    return my;
  else
    {
      free(my);
      return 0;
    }
  return my;
}

void destruct(MyInstance* my)
{
  effectv_teardown(my->effect);

  free(my);
}

void update(void* instance)
{
    InstancePtr inst = (InstancePtr) instance;
    MyInstancePtr my = inst->my;

    FrameBufferAttributes attribs;
    int xsize = inst->in_b->xsize;
    int ysize = inst->in_b->ysize;

    char buffer[128];
    int colormask;
    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attribs);


    if (inst->in_colors->number != my->old_colors) {
    colormask = trim_int(inst->in_colors->number, 0, INT_MAX);
	mask = 0;
	if(colormask & 0x01)
	    mask |= 0xff0000;
	if(colormask & 0x02)
	    mask |= 0xff00;
	if(colormask & 0x04)
	    mask |= 0xff;
	my->old_colors = inst->in_colors->number;
    }

    effectv_draw(my->effect,
		 (unsigned char*) inst->in_b->framebuffer,
		 (unsigned char*) inst->out_r->framebuffer,
		 xsize, ysize);
}

