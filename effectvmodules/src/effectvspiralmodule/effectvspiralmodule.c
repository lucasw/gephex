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

#include "effectvspiralmodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "spiral.c"

typedef struct _MyInstance {

  struct effectv_Effect* effect;

    double old_animate_focus;
    double old_toggle_xor;
    double old_focus_interval;
    double old_focus_increment;
    double old_depth_shift;
    char *old_text;
    double old_focus_x;
    double old_focus_y;
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

    l = strlen(s)+1;
    if(!(r = malloc(l)))
	return(0);
    memcpy(r, s, l);
    return r;
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->old_toggle_xor = 0;
  my->old_focus_x = 0.5;
  my->old_focus_y = 0.5;
  my->old_text = strcopy("Concentric A");
  my->effect = effectv_init(spiralRegister, 0, 0);

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
    char buffer[64];
    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attribs);

    
    if(inst->in_animate_focus->number != my->old_animate_focus) {
	g_animate_focus = (int)inst->in_animate_focus->number;
	my->old_animate_focus = inst->in_animate_focus->number;
    }

    if(inst->in_toggle_xor->number != my->old_toggle_xor) {
	g_toggle_xor = (int)inst->in_toggle_xor->number;
	my->old_toggle_xor = inst->in_toggle_xor->number;
    }

    if(inst->in_focus_increment->number != my->old_focus_increment) {
	g_focus_increment = FOCUS_INCREMENT_PRESET * (inst->in_focus_increment->number);
	spiralSetName();
	my->old_focus_increment = inst->in_focus_increment->number;
    }

    if(inst->in_focus_interval->number != my->old_focus_interval) {
	g_focus_interval = inst->in_focus_interval->number;
	spiralSetName();
	my->old_focus_interval = inst->in_focus_interval->number;
    }

    if(inst->in_depth_shift->number != my->old_depth_shift) {
	g_depth_shift = inst->in_depth_shift->number;
	spiralSetName();
	spiralCreateMap();
    }

    if(inst->in_focus->x != my->old_focus_x ||
       inst->in_focus->y != my->old_focus_y) {
	g_focus_x = inst->in_focus->x * video_width;
	g_focus_y = inst->in_focus->y * video_height;
	my->old_focus_x = inst->in_focus->x;
	my->old_focus_y = inst->in_focus->y;
	spiralCreateMap();
    }

    if(strcmp(inst->in_wave_names->text, my->old_text)) {
	for(i = 0; i < WAVE_COUNT; i++) {
	    if(!strcmp(g_wave_names[i], inst->in_wave_names->text)) {
		mode = i;
		spiralSetName();
		spiralCreateMap();
		break;
	    }
	}

	if(my->old_text)
	    free(my->old_text);

	my->old_text = strcopy(inst->in_wave_names->text);
    }


    effectv_draw(my->effect,
		 (unsigned char*) inst->in_b->framebuffer,
		 (unsigned char*) inst->out_r->framebuffer,
		 xsize, ysize);
}

