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

#include "effectvpupmodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "pup.c"

static char *modes[] = { "vertical", "horizontal", "diagonal", "dissolution", "random", "raster" };
typedef struct _MyInstance {

  struct effectv_Effect* effect;

    char *old_mode;
    double old_paraminc;

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

  my->old_paraminc = 0;
  my->old_mode = strdup("vertical");
  my->effect = effectv_init(pupRegister, 0, 0);

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
    int i;
    InstancePtr inst = (InstancePtr) instance;
    MyInstancePtr my = inst->my;

    FrameBufferAttributes attribs;
    int xsize = inst->in_b->xsize;
    int ysize = inst->in_b->ysize;

    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attribs);

    if (inst->in_paraminc->number != my->old_paraminc) {
	my->old_paraminc = inst->in_paraminc->number;
    }

    if(strcmp(inst->in_mode->text, my->old_mode)) {
	for(i = 0; i < 6; i++) {
	    if(!strcmp(modes[i], inst->in_mode->text)) {
		mode = i;
		break;
	    }
	}


	if(my->old_mode)
	    free(my->old_mode);

	my->old_mode = strdup(inst->in_mode->text);
    }
    effectv_draw(my->effect,
		 (unsigned char*) inst->in_b->framebuffer,
		 (unsigned char*) inst->out_r->framebuffer,
		 xsize, ysize);
}

