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

#include "overlaymodule.h"

#include <cassert>

static logT s_log;

typedef struct _MyInstance 
{
  FrameBufferType* temp_in_2;
  FrameBufferType* temp_in_control;
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
  my->temp_in_2=framebuffer_newInstance();
  my->temp_in_control=framebuffer_newInstance();

  return my;
}

void destruct(MyInstance* my)
{
  framebuffer_deleteInstance(my->temp_in_2);
  framebuffer_deleteInstance(my->temp_in_control);
  free(my);
}

static __inline
int framebuffer_compare_attributes(FrameBufferAttributes* attributes1,
				FrameBufferAttributes* attributes2)
{
  return (attributes1->xsize == attributes2->xsize && attributes1->ysize == attributes2->ysize);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  
  // Add your effect here!
  FrameBufferAttributes  in_1_attr;
  FrameBufferAttributes  in_2_attr;
  FrameBufferAttributes  in_control_attr;
  
  framebuffer_getAttributes(inst->in_1,&in_1_attr);
  framebuffer_getAttributes(inst->in_2,&in_2_attr);
  framebuffer_getAttributes(inst->in_control,&in_control_attr);
  
  // default
  FrameBufferType* in_1=inst->in_1;
  FrameBufferType* in_2=inst->in_2;
  FrameBufferType* in_control=inst->in_control;
  
  if(!framebuffer_compare_attributes(&in_1_attr,&in_control_attr))
    { // we need to convert th control image
      framebuffer_convertType(my->temp_in_control,inst->in_control , &in_1_attr);
      in_control=my->temp_in_control;
    }
  
  // check if all frame inputs have equal attributes
  if(!(framebuffer_compare_attributes(&in_1_attr,&in_2_attr))) 
  { // scale the second input frame
    framebuffer_convertType(my->temp_in_2, inst->in_2, &in_1_attr);
    in_2=my->temp_in_2;
  }
     
     // change the output size
     framebuffer_changeAttributes(inst->out_r,&in_1_attr);
     
     int size=in_1_attr.xsize*in_1_attr.ysize;
     uint32_t* in_1_ptr=in_1->data;
     uint32_t* in_2_ptr=in_2->data;
     uint32_t* in_control_ptr=in_control->data;
     uint32_t* out_r_ptr=inst->out_r->data;
     
     int tolerance=trim_int(inst->in_tolerance->number*255 + .5 ,0,255);
     
     // the three frames must have the same attributes
  {
    FrameBufferAttributes  in_1_attr;
    FrameBufferAttributes  in_2_attr;
    FrameBufferAttributes  in_control_attr;
    
    framebuffer_getAttributes(in_1,&in_1_attr);
    framebuffer_getAttributes(in_2,&in_2_attr);
    framebuffer_getAttributes(in_control,&in_control_attr);
    
    assert(framebuffer_compare_attributes(&in_1_attr,&in_2_attr)&&
	   framebuffer_compare_attributes(&in_2_attr,&in_control_attr));
  }
     
     
     while(in_1_ptr!=((in_1->data)+size))
  {
    uint8_t* color=reinterpret_cast<uint8_t*>(in_control_ptr);
    
    if(color[1]<tolerance)
      {
	*out_r_ptr=*in_1_ptr;
      }
    else
      {
	*out_r_ptr=*in_2_ptr;
      }
    
    ++in_1_ptr;++in_2_ptr;++in_control_ptr;++out_r_ptr;
  }



}

void strongDependencies(Instance* inst, int neededInputs[])
{
	// set the inputs to 0 that are not needed!
}

