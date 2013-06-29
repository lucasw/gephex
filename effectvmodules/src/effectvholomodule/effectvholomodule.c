/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 Sven Schnelle <schnelle@kabelleipzig.de>

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

#include "effectvholomodule.h"

static logT s_log;
static int doublebuf = 0;
#include "libeffectv.h"
#include "sdldummy.h"
#include "holo.c"

typedef struct _MyInstance {

  struct effectv_Effect* effect;

  double old_bg;

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

  my->old_bg = 0;

  my->effect = effectv_init(holoRegister, 0, 0);

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

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (inst->in_bg->number != my->old_bg) {
      framenumber = 0;
      my->old_bg = inst->in_bg->number;
    }

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

