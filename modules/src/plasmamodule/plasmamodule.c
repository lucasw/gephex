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

#include "plasmamodule.h"

#include <limits.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../libgrid/libgrid.h"

typedef struct _MyInstance {
	
  Grid grid;	
	
  int xres_old;
  int yres_old;
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
	
  my->xres_old = 0;
  my->yres_old = 0;
	
  grid_init(&my->grid,0,16,16,0,0,0);
	
  return my;
}

void destruct(MyInstance* my)
{
  grid_flush(&my->grid);
  free(my);
}


__inline int fx(int xres, int yres,int x,int y, double t, double a, double b)
{	
  double time = fmod(t, 2*M_PI);
  double d = (-4./((xres-1)*(double)(xres-1))*x + 4./((double) (xres-1)))*x;
  return (int) (x + a*(xres/4)* d * sin(b*y/yres + time));
}

__inline int fy(int xres, int yres, int x,int y,double t, double a, double b)
{
  double time = fmod(t, 2*M_PI);
  double d = (-4./((yres-1)*(double)(yres-1))*y + 4./((double)(yres-1)))*y;
  return (int) (y + a*(yres/4)*d * sin(b*x/xres + time));
}	



void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int x, y, newx, newy;

  double time      = inst->in_time->number;
  double amplitude = trim_double(inst->in_amp->number, 0, 1);
  double freq      = inst->in_frq->number;
  int xsize        = trim_int(inst->in_b->xsize,1,FRAMEBUFFER_X_MAX);
  int ysize        = trim_int(inst->in_b->ysize,1,FRAMEBUFFER_Y_MAX);

  FrameBufferAttributes attribs;

  TexturePoint* grid_points;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  grid_change_texture(&my->grid,xsize,inst->in_b->framebuffer,0);

  if (xsize != my->xres_old || ysize != my->yres_old)
    {
      grid_change_dst(&my->grid,xsize,ysize,inst->out_r->framebuffer);

      my->xres_old = xsize;
      my->yres_old = ysize;
    }

  grid_points = my->grid.points;
  for(y = 0; y <= ysize; y += LIBGRID_GRIDSIZE)
    {
      for(x = 0; x <= xsize; x += LIBGRID_GRIDSIZE)
        {
          newx = fx(xsize, ysize, x, y, time, amplitude, freq);
          newy = fy(xsize, ysize, x, y, time, amplitude, freq);
          grid_points->u = newx;
          grid_points->v = newy;
          ++grid_points;
        }
    }
	
  grid_interpolate(&my->grid);
}
