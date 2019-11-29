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

#include "numxfadermodule.h"

#include <math.h>

#define EPS 0.00001

static __inline int double_equals(double lhs, double rhs, double eps)
{
  return (fabs(lhs - rhs) < eps);
}

typedef struct _MyInstance {

 int dummy;

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


  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  double fader = trim_double(inst->in_x->number, 0 , 1);

  if (double_equals(fader, 0, EPS))
    inst->out_r->number = inst->in_1->number;
  else if (double_equals(fader, 1, EPS))
    inst->out_r->number = inst->in_2->number;
  else
    {
      double val1 = inst->in_1->number;
      double val2 = inst->in_2->number;
      inst->out_r->number = (val2 * fader) + (val1 * (1.0 - fader));
    }
}

void strongDependencies(Instance* inst, int neededInputs[])
{ 
  double fader = trim_double(inst->in_x->number, 0 , 1);
 
  if (double_equals(fader, 0, EPS))
    neededInputs[in_2] = 0;
  else if (double_equals(fader, 1, EPS))
    neededInputs[in_1] = 0;
}
