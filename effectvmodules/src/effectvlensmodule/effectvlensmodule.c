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

#include "effectvlensmodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#define init initLENSLENSLENS
#include "lens.c"
#undef init

typedef struct _MyInstance {
  struct effectv_Effect* effect;
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

  my->effect = effectv_init(lensRegister, 0, 0);

  if (my->effect)
    return my;
  else
    {
      free(my);
      return 0;
    }
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

  int size = trim_int(inst->in_size->number, 10, 500);
  int xpos = (int) (trim_double(inst->in_pos->x, 0, 1) * (xsize-size));
  int ypos = (int) (trim_double(inst->in_pos->y, 0, 1) * (ysize-size));
  int interactive = trim_bool(inst->in_interactive->number);
  int mag = trim_int(inst->in_mag->number, 5, 200);

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (size != lens_width)
    {
      SDL_Event ev;

      ev.type = SDL_MOUSEMOTION;
      ev.button.button = SDL_BUTTON_LEFT;
      ev.motion.yrel = -lens_width + size;

      event(&ev);
    }

  if (xpos != x || ypos != y)
    {
      SDL_Event ev;

      ev.type = SDL_MOUSEMOTION;
      ev.button.button = 0;
      ev.motion.xrel = -x + xpos;
      ev.motion.yrel = -y + ypos;

      event(&ev);
    }

  if (mag != lens_zoom)
    {
      SDL_Event ev;

      ev.type = SDL_MOUSEMOTION;
      ev.button.button = 2;
      ev.motion.yrel = -lens_zoom + mag;

      event(&ev);

      //      printf("lens_zoom = %i\t mag = %i\n", lens_zoom, mag);
    }

  if (interactive != mode)
    {
      SDL_Event ev;

      ev.type = SDL_KEYDOWN;
      ev.key.keysym.sym = SDLK_SPACE;

      event(&ev);
    }

  /*  if (inst->in_bg->number != my->old_bg)
    {
      SDL_Event ev;
      ev.type = SDL_KEYDOWN;
      ev.key.keysym.sym = SDLK_SPACE;

      event(&ev);

      my->old_bg = inst->in_bg->number;
      }*/

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

