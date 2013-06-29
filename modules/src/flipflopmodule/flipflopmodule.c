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

#include "flipflopmodule.h"

static logT s_log;

typedef struct _MyInstance {

  double old_clk;
  double old_d;

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

  my->old_clk = 0;
  my->old_d = 0;

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
  double clk = inst->in_clk->number;
  double tol = inst->in_tol->number;

  if (clk > my->old_clk && clk - my->old_clk > tol)
    {
      my->old_d = inst->in_d->number;
    }

  inst->out_r->number = my->old_d;
  my->old_clk = clk;
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  double tol     = inst->in_tol->number;
  double clk     = inst->in_clk->number;
  double old_clk = inst->my->old_clk;
  if (clk <= old_clk || clk - old_clk <= tol)
    neededInputs[in_d] = 0;
}

