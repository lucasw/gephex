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


__inline int fx(int xres, int yres,int x,int y,int t, double a, double b)
{	
	double d = (-4./((xres-1)*(double)(xres-1))*x + 4./((double) (xres-1)))*x;
	return (int) x + a*(xres/4)* d * sin(b*y/yres + t*(2*M_PI-1)/255);
}

__inline int fy(int xres, int yres, int x,int y,int t, double a, double b)
{
	double d = (-4./((yres-1)*(double)(yres-1))*y + 4./((double)(yres-1)))*y;
	return (int) y + a*(yres/4)*d * sin(b*x/xres + t*(2*M_PI-1)/255);
}	



void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	
	
	int x, y, newx, newy, u=0, v=0;
	
	int time = inst->in_time->number >> 24;
	double amplitude = inst->in_amp->number / (double) UINT_MAX;
	double frequence = inst->in_frq->number / (double) UINT_MAX; 
	int xsize = inst->in_b->xsize;
	int ysize = inst->in_b->ysize;
	
	FrameBufferAttributes attribs;

	TexturePoint* grid_points;
	
	attribs.xsize = xsize;
	attribs.ysize = ysize;
	framebuffer_changeAttributes(inst->out_r, &attribs);

	if (xsize != my->xres_old || ysize != my->yres_old)
	{
		grid_change_texture(&my->grid,xsize,inst->in_b->framebuffer,0);
		grid_change_dst(&my->grid,xsize,ysize,inst->out_r->framebuffer);		
		
		my->xres_old = xsize;
		my->yres_old = ysize;				
	}
	
	grid_points = my->grid.points;
	for(y= 0; y<= ysize; y+=LIBGRID_GRIDSIZE)
	{		
		for(x= 0; x<= xsize; x+=LIBGRID_GRIDSIZE)
		{
			newx = fx(xsize, ysize, x,y,time, amplitude, frequence);
			newy = fy(xsize, ysize, x,y,time, amplitude, frequence);
			grid_points->u = newx;	
			grid_points->v = newy;
			++grid_points;
		}
	}
	
	grid_interpolate(&my->grid);
	
}
