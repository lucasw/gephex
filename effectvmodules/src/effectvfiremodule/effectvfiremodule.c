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

#include "effectvfiremodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "fire.c"

typedef struct _MyInstance {
  struct effectv_Effect* effect;

  double old_bg;

  char* old_mode;
} MyInstance, *MyInstancePtr;

static char* strcopy(const char* str)
{
  int l;
  char* r;

  if (str == 0)
    return 0;

  l = strlen(str) + 1;
  r = malloc(l);

  if (r == 0)
    return 0;

  memcpy(r, str, l);

  return r;
}

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

  my->old_bg   = 0;
  my->old_mode = strcopy("foreground");

  my->effect = effectv_init(fireRegister, 0, 0);

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
  if (my->old_mode)
    free(my->old_mode);

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
  const char* new_mode = inst->in_mode->text;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (inst->in_bg->number != my->old_bg)
    {
      SDL_Event ev;
      ev.type = SDL_KEYDOWN;
      ev.key.keysym.sym = SDLK_SPACE;

      event(&ev);

      my->old_bg = inst->in_bg->number;
    }

  if (strcmp(new_mode, my->old_mode) != 0)
    {
      SDL_Event ev;
      ev.type = SDL_KEYDOWN;

      if (strcmp(new_mode, "foreground") == 0)
	ev.key.keysym.sym = SDLK_1;
      else if (strcmp(new_mode, "light") == 0)
	ev.key.keysym.sym = SDLK_2;
      else if (strcmp(new_mode, "dark") == 0)
	ev.key.keysym.sym = SDLK_3;
      else
	ev.key.keysym.sym = SDLK_1;

      event(&ev);

      free(my->old_mode);
      my->old_mode = strcopy(new_mode);
    }

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}




