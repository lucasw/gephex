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

#include "rangeconvertmodule.h"

#include <math.h>
#include <assert.h>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

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

  double delta_in = inst->in_max_in->number - inst->in_min_in->number;
  double delta_out = inst->in_max_out->number - inst->in_min_out->number;

  double in = trim_double(inst->in_n->number, inst->in_min_in->number,
			  inst->in_max_in->number);
  double result;

  if (fabs(delta_in) < 0.000001)
    {
      result = inst->in_min_out->number + 0.5*delta_out;
    }
  else if (delta_in < 0)
    {
      result = inst->in_n->number;
    }
  else
    {
      result = (in - inst->in_min_in->number) * (delta_out / delta_in)
	+ inst->in_min_out->number;

      /*      assert(inst->in_min_out->number <= result &&
	      result <= inst->in_max_out->number);*/
    }


  inst->out_r->number = result;
}

