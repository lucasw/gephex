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

#include "effectvsimuramodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "simura.c"

typedef struct _MyInstance {

  struct effectv_Effect* effect;

    double old_color;
    double old_mirror;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

static char *strcopy(const char *s)
{
    int l;
    char *r;

    if(!s)
	return(0);
    l = strlen(s) + 1;
    if(!(r = malloc(l)))
	return(0);
    memcpy(r, s, l);
	return r;
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->old_color = 0;
  my->old_mirror = 0;

  my->effect = effectv_init(simuraRegister, 0, 0);

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

  if (inst->in_color->number != my->old_color) {
      color = colortable[trim_int(inst->in_color->number, 0, INT_MAX)];
      my->old_color = inst->in_color->number;
     } 

  if (inst->in_mirror->number != my->old_mirror) {
      mirror = trim_int(inst->in_mirror->number, 0, INT_MAX);
    my->old_mirror = inst->in_color->number;
     } 

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

