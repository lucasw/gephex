#include "planemodule.h"

#include <limits.h>
#include <math.h>
#include "../libgrid/libgrid.h"

#define TEX_SIZE_LOG 8
#define TEX_SIZE (1<<TEX_SIZE_LOG)

#define GRID_OPTIONS (LIBGRID_POWER_OF_2)


const int DIRECTION_Z = 200;

#ifdef M_PI
#undef M_PI
#endif

static const double M_PI = 3.14159265358979323846;

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


  double t,rot_angle;

  int x,y,u,v,z,d;
  Vector dir, intersection, origin;
  double cosa, sina;
	
  TexturePoint* gridpointer;	
	
  int xres = trim_int(inst->in_xres->number, 0, 1024);
  int yres = trim_int(inst->in_yres->number, 0, 1024);

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
	
  d = 50+(int)(650. * trim_double(inst->in_d->number, 0, 1));

  //set up viewpoint
  origin.x = (trim_double(inst->in_pos->x,0,1)*5000. - 2500);
  origin.y = (trim_double(inst->in_pos->y,0,1)*d);
  origin.z = (inst->in_t->number*5000.);
	
  rot_angle = ((inst->in_rot->number/ 180.) * M_PI);
  cosa = cos(rot_angle);
  sina = sin(rot_angle);
	
  gridpointer = my->grid.points;

  //compute a grid of GRID_SIZExGRID_SIZE blocks
  for(y=0; y<=yres; y += LIBGRID_GRIDSIZE)
    {
      for(x=0; x<=xres; x += LIBGRID_GRIDSIZE)
        {
          //intersection = t*direction
          dir.x = fabs(x-xres/2); //TODO
          dir.y = fabs(y-yres/2); //TODO
          dir.z = DIRECTION_Z;
          rotate(&dir, cosa, sina);
          normalize(&dir);
			
          if(dir.y <= 0.001)
            {
              u = 0;
              v = 0;
              z = 255;
            }
          else
            {
              t = (d - origin.y)/dir.y;
              intersection.x = t * dir.x + origin.x;
              intersection.z = t * dir.z + origin.z;
	
              u = (int)fmod(fabs(intersection.x/4.), TEX_SIZE);
              v = (int)fmod(fabs(intersection.z/4.), TEX_SIZE);

              if(u> TEX_SIZE-4 || u<4 || v> TEX_SIZE-4 || v<4)
                {
                  z = 255;
                }
              else if (t > DIRECTION_Z)
                z = (int) (minimum(255, shading_factor*(sqrt(t-DIRECTION_Z))));
              else
                z = 0;
            }
			
          gridpointer->u = u;
          gridpointer->v = v;
          gridpointer->z = z;
          ++gridpointer;
        }
    }
	
  grid_interpolate(&my->grid);
}

