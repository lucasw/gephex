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

#include "numbermodule.h"

#include "crandgen.h"

typedef struct _MyInstance {
  double lastnoise;
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

  my->lastnoise = 0;

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
  double newnoise;
  double feedback;
  double min;
  double max;
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  feedback = trim_double(inst->in_tpf->number, 0.0, 1.0);
  min      = inst->in_min->number;
  max      = inst->in_max->number;

  newnoise = ((double)rnd_mt19937() / (double)(0xFFFFFFFF));
  
  my->lastnoise = ((1.0-feedback)*newnoise) + (feedback)*my->lastnoise;
  if (min<max)
    {
      inst->out_r->number = min + my->lastnoise*(max-min);
    }
  else
    {
      inst->out_r->number = max + my->lastnoise*(min-max);
    }

}
