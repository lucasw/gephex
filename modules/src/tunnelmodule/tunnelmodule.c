#include "tunnelmodule.h"

#include <limits.h>
#include <math.h>
#include "../libgrid/libgrid.h"

#define TEX_SIZE_LOG 9
#define TEX_SIZE (1<<TEX_SIZE_LOG)

#define GRID_OPTIONS (LIBGRID_POWER_OF_2)


const int DIRECTION_Z = 200;

#ifdef M_PI
#undef M_PI
#endif

const double M_PI = 3.14159265358979323846;

typedef struct _MyInstance 
{
	int xres_old;
	int yres_old;

	int libgrid_flags;
	Grid grid;
	
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
	return 1;
}

void shutDown(void)
{}

MyInstance* construct()
{
	MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	
	my->libgrid_flags = GRID_OPTIONS;

	grid_init(&my->grid,0,16,16,0,0,my->libgrid_flags);
	
	my->xres_old = 0;
	my->yres_old = 0;
	return my;
}

void destruct(MyInstance* my)
{
	grid_flush(&my->grid);
	free(my);
}


typedef struct Vector_{
	double x,y,z;
}Vector;

__inline void normalize(Vector* vec){
	double len =1.0 / sqrt(vec->x*vec->x+vec->y*vec->y+vec->z*vec->z);
	vec->x*=len;
	vec->y*=len;
	vec->z*=len;
}

__inline void rotate(Vector* vec, double ca, double sa)
{
	double a = vec->x*ca - vec->y*sa;
	double b = vec->x*sa + vec->y*ca;
	vec->x=a;
	vec->y=b;
}

__inline double minimum(double a, double b){
	return (a<b) ? a : b;
}

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;


	double a,b,c,delta,t,rot_angle;

	int x,y,u,v,z;
	Vector dir, intersection, origin;
	double cosa, sina;
	
	TexturePoint* gridpointer;	
	
	int xres = trim_int(inst->in_xres->number, 0, 1024);
	int yres = trim_int(inst->in_yres->number, 0, 1024);

	double radius = 160.*inst->in_radius->number  + 40.;

	double shading_factor;

	if (inst->in_shading->number == 0)
		my->libgrid_flags &= (~LIBGRID_USE_Z);
	else
		my->libgrid_flags |= LIBGRID_USE_Z;

	shading_factor = 3.5* (inst->in_shading->number / 10.) + 2.;
		
	grid_change_texture(&my->grid,TEX_SIZE_LOG,
						inst->in_b->framebuffer, my->libgrid_flags);

	if (my->xres_old !=  xres || my->yres_old != yres)
	{		
		FrameBufferAttributes attribs;

		attribs.xsize = xres;
		attribs.ysize = yres;
		framebuffer_changeAttributes(inst->out_r, &attribs);

		grid_change_dst(&my->grid,xres,yres,inst->out_r->framebuffer);		
		
		my->xres_old = xres;
		my->yres_old = yres;				
	}
	
	//set up viewpoint
	origin.x = (inst->in_pos->x*(radius*1.5) - radius*0.75);
	origin.y = (inst->in_pos->y*(radius*1.5) - radius*0.75);
	origin.z = (inst->in_t->number*(-2000.)) +1000.;
	
	rot_angle = ((inst->in_rot->number/360) * 2* M_PI) - M_PI;
	cosa = cos(rot_angle);
	sina = sin(rot_angle);
	
	gridpointer = my->grid.points;

	//compute a grid of GRID_SIZExGRID_SIZE blocks
	for(y=0; y<=yres; y += LIBGRID_GRIDSIZE)
    {
		for(x=0; x<=xres; x += LIBGRID_GRIDSIZE)
		{
			//intersection = t*direction
			dir.x = x-xres/2; //TODO
			dir.y = y-yres/2; //TODO
			dir.z = DIRECTION_Z;
			rotate(&dir, cosa,sina);
			normalize(&dir);
			
			a = dir.x*dir.x + dir.y*dir.y;
			b = 2*(origin.x*dir.x+origin.y*dir.y);
			c = origin.x*origin.x+origin.y*origin.y- radius*radius;
			
			delta = b*b-4*a*c;
			
			if(delta<=0)
			{
				u = TEX_SIZE/2;
				v = TEX_SIZE/2;
				z = 255;
			} 
			else 
			{
				double t_;
				//only the nearer point's of interest
				t = minimum((-b-sqrt(delta))/(2*a), (-b+sqrt(delta))/(2*a));
				t_ = fabs(t);
				
				intersection.x = origin.x+t*dir.x; 
				intersection.y = origin.y+t*dir.y;
				intersection.z = origin.z+t*dir.z;
				
				//apply cylindric texture-mapping
				u = (int)(fabs(intersection.z)*0.2);
				v = (int)(fabs(atan2(intersection.y,intersection.x)*TEX_SIZE/M_PI));
				if (t_ > DIRECTION_Z)
					z = (int) (minimum (255, shading_factor*(sqrt(t_-DIRECTION_Z))));
				else
					z = 0;
			}
			
			gridpointer->u = u % TEX_SIZE;
			gridpointer->v = v % TEX_SIZE;
			gridpointer->z = z;
			++gridpointer;
		}
    }
	
	grid_interpolate(&my->grid);
}

