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

#include "blurmodule.h"

#include <limits.h>
typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

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

	framebuffer_getAttributes(inst->in_b, &attribs);
	framebuffer_changeAttributes(inst->out_r, &attribs);
  
	{
  int offset;

  unsigned char left_r, right_r, up_r, down_r;
  /*, upperleft_r, lowerleft_r, 
    upperright_r, lowerright_r;*/
  unsigned char left_g, right_g, up_g, down_g;
  /*, upperleft_g, lowerleft_g, 
    upperright_g, lowerright_g;*/

  unsigned char left_b, right_b, up_b, down_b;
  /*, upperleft_b, lowerleft_b, 
    upperright_b, lowerright_b;*/

//  unsigned char left_a, right_a, up_a, down_a;
  /*, upperleft_a, lowerleft_a, 
    upperright_a, lowerright_a;*/
  unsigned char *dst_left, *dst_right, *dst_up, *dst_down;
  /*, *dst_upperleft, *dst_lowerleft,
   *dst_upperright, *dst_lowerright;*/
	
  //destination rgba vals
  //unsigned int r,g,b/*,a*/;

  int xsize = inst->in_b->xsize;
  int xsize_x_4 = xsize * 4;
  int ysize = inst->in_b->ysize;
  int maxPixelOffset = xsize*ysize;
 
  unsigned char* src = 
    (unsigned char*)(inst->in_b->framebuffer + maxPixelOffset-1-(2*xsize));

  unsigned char* result = (unsigned char*) (inst->out_r->framebuffer + maxPixelOffset-1-(2*xsize));
  int blurFactor = trim_int(inst->in_x->number, 0, 400);


  // TODO: ersten zwei und letzten zwei zeilen erstmal rausgelassen
  for(offset=maxPixelOffset-1-(2*xsize); offset>=(2*xsize); --offset)
    {
      dst_left = src-(blurFactor);
      dst_right = src+(blurFactor);
      dst_up = src+xsize_x_4;
      dst_down = src-xsize_x_4;
      /*dst_upperleft = src+xsize_x_4-blurFactor;
	dst_lowerleft = src-xsize_x_4-blurFactor;
	dst_upperright= src+xsize_x_4+blurFactor;
	dst_lowerright = src-xsize_x_4+blurFactor;*/

      left_r = *(dst_left );
      right_r = *(dst_right);
      up_r = *(dst_up);
      down_r = *(dst_down);
      /*upperleft_r = *(dst_upperleft);
	lowerleft_r = *(dst_lowerleft); 
	upperright_r = *(dst_upperright);
	lowerright_r = *(dst_lowerright);*/

      left_g = *(dst_left+1);
      right_g = *(dst_right+1);
      up_g = *(dst_up+1);
      down_g = *(dst_down+1);
      /*upperleft_g = *(dst_upperleft+1);
	lowerleft_g = *(dst_lowerleft+1); 
	upperright_g = *(dst_upperright+1);
	lowerright_g = *(dst_lowerright+1);*/

      left_b = *(dst_left+2);
      right_b = *(dst_right+2);
      up_b = *(dst_up+2);
      down_b = *(dst_down+2);
      /*upperleft_b = *(dst_upperleft+2);
	lowerleft_b = *(dst_lowerleft+2); 
	upperright_b = *(dst_upperright+2);
	lowerright_b = *(dst_lowerright+2);*/
	
      /*left_a = *(dst_left+3);
      right_a = *(dst_right+3);
      up_a = *(dst_up+3);
      down_a = *(dst_down+3);*/
      /*upperleft_a = *(dst_upperleft+3);
	lowerleft_a = *(dst_lowerleft+3); 
	upperright_a = *(dst_upperright+3);
	lowerright_a = *(dst_lowerright+3);*/

      *result = (left_r + right_r + up_r + down_r /*+ upperleft_r + lowerleft_r + 
					      upperright_r + lowerright_r*/) >> 2;
      *(result+1) = (left_g + right_g + up_g + down_g /*+ upperleft_g + lowerleft_g + 
					      upperright_g + lowerright_g*/) >> 2;
      *(result+2) = (left_b + right_b + up_b + down_b /*+ upperleft_b + lowerleft_b +							
					      upperright_b + lowerright_b*/) >> 2;
      //a = (left_a + right_a + up_a + down_a /*+ upperleft_a + lowerleft_a +
		//			      upperright_a + lowerright_a*/) >> 2;
		

      //*result	= /*(a<<24)|*/(b<<16)|(g<<8)|r;
      result-= 4;		
      src-=4;
    }
	}
}

