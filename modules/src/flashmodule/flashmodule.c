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

#include "flashmodule.h"

typedef struct _MyInstance {

 double old_trigger;
 int counter;
 int dont_update;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->counter = 0;
  my->old_trigger = 0;
  my->dont_update = 0;

  return my;
}

void destruct(MyInstance* my)
{  
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  FrameBufferAttributes attribs;

  int fadeValue;
  int negfadeValue;
  int xsize = inst->in_src->xsize;
  int ysize = inst->in_src->ysize;
  int c;  

  int attack  = trim_int(inst->in_attack->number, 0, 10);
  int sustain = trim_int(inst->in_sustain->number, 0, 10);
  int decay   = trim_int(inst->in_decay->number, 0, 25);
  int maxcount = attack + sustain + decay;

  double trigger = inst->in_trigger->number;

  if (my->dont_update)
	  return;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (trigger != my->old_trigger)
  {
	  my->counter = maxcount;
	  my->old_trigger = trigger;
  }

  c = maxcount - my->counter;

  if (c < attack)
  {

	  fadeValue = (int) ((0.5 + 255 * c) / (double) attack);
      negfadeValue = 255 - fadeValue;
  }
  else if (c < attack + sustain)
  {
	  fadeValue = 255;
	  negfadeValue = 0;
  }
  else //decay
  {
	fadeValue = (int) ((0.5 + 255 * my->counter)/ (double) decay);
	negfadeValue = 255 - fadeValue;
  }
  
  
  fadeValue *= 255; // 8 bit fixed point arithmetic

  {
	unsigned char* result    = (unsigned char*) inst->out_r->framebuffer;
	unsigned char* framebuf1 = (unsigned char*) inst->in_src->framebuffer;
    unsigned char* end	     = result + (xsize*ysize)*4;
    
		
      while (result != end)
	  {
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  ++framebuf1;
		  ++result;
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  ++framebuf1;
		  ++result;
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  framebuf1 += 2; 
		  result += 2;
	  }
  }

  my->counter -= 1;
  if (my->counter < 0)
	  my->counter = 0;
	  
}

void patchLayout(Instance* inst, int out2in[])
{
   double trigger = inst->in_trigger->number;

   if (trigger == inst->my->old_trigger && inst->my->counter == 0)
   {
	   inst->my->dont_update = 1;
	   out2in[out_r] = in_src;
   }
   else
	   inst->my->dont_update = 0;
}
