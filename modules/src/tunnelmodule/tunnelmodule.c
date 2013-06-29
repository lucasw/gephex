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

#include "tunnelmodule.h"

#include <limits.h>
#include <math.h>

#include "../libgrid/libgrid.h"

#if defined (_MSC_VER)
#define lrint(a) ((int_32) (a))
#endif

#ifdef M_PI
#undef M_PI
#endif

const double M_PI = 3.1415926535897932384;

#define GRIDSIZE_LOG 2
#define GRIDSIZE (1 << GRIDSIZE_LOG)

static logT s_log = 0;

typedef struct _MyInstance 
{
  int xres_old;
  int yres_old;

  int libgrid_flags;
  Grid grid;
	
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  return 1;
}

void shutDown(void)
{}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	
  if (my == 0)
    {
      s_log(0, "Could not allocate MyInstance");
      return 0;
    }

  my->libgrid_flags = 0;

  if (grid_init(&my->grid,GRIDSIZE_LOG,0,16,16,0,0,my->libgrid_flags) == 0)
    {
      free(my);
      s_log(0, "Could not init grid");
      return 0;
    }
	
  my->xres_old = 0;
  my->yres_old = 0;

  return my;
}

void destruct(MyInstance* my)
{
  grid_flush(&my->grid);
  free(my);
}

struct vector_t {
  double x,y,z;
};


#define minimum(a, b) (((a) < (b)) ? (a) : (b))

static __inline double angle(double x, double y)
{
  double alpha = atan2(y, x);

  if (alpha < 0)
    return 2*M_PI + alpha;
  else
    return alpha;
}

/*
 * Intersect the line p + lambda * d with a cylinder of radius
 * r (parallel to the z-axis) (x*x + y*y = r).
 * Returns the positive lambda value if any.
 * If the whole line is in the cylinder, 0 is returned.
 * If there is no intersection, or the lambda value is
 * negative, a negative value is returned.
 */
static double intersect(const struct vector_t* p,
                        const struct vector_t* d, double r)
{
  double a = d->x*d->x + d->y*d->y;
  double b = 2*(p->x*d->x + p->y*d->y);
  double c = p->x*p->x + p->y*p->y - r*r;
			
  double delta = b*b - 4*a*c;
			
  if(delta <= 0) // no intersection
    {
      if (delta == 0)
        return -b;
      else
        return -1;
    }
  else 
    {
      //only the further point's of interest
      return (-b + sqrt(delta))/(2*a);
    }
}

static __inline void MUL_ADD_PIX(uint_32* r,
                                 uint_32 p1, int_32 f1,
                                 uint_32 p2, int_32 f2)
{
  uint_8* pp1 = (uint_8*) &p1;
  uint_8* pp2 = (uint_8*) &p2;

  r[0] = pp1[0] * f1 + pp2[0] * f2;
  r[1] = pp1[1] * f1 + pp2[1] * f2;
  r[2] = pp1[2] * f1 + pp2[2] * f2;
}

static __inline uint_32 MUL_ADD_ROUND(const uint_32* p1, int_32 f1,
                                      const uint_32* p2, int_32 f2)
{
  uint_32 result;
  uint_8* rrr = (uint_8*) &result;

  rrr[0] = ((p1[0] >> 16) * f1 + (p2[0] >> 16) * f2) >> 16;
  rrr[1] = ((p1[1] >> 16) * f1 + (p2[1] >> 16) * f2) >> 16;
  rrr[2] = ((p1[2] >> 16) * f1 + (p2[2] >> 16) * f2) >> 16;

  return result;
}

static __inline uint_32 PIX_AVG(const uint_32* texture,
                                int_32 fu, int_32 fv,
                                int i_tl, int i_tr,
                                int i_br, int i_bl)
{
  int_32 fun = (1<<16) - fu;
  int_32 fvn = (1<<16) - fv;
  
  uint_32 t_tl = texture[i_tl];
  uint_32 t_tr = texture[i_tr];
  uint_32 t_br = texture[i_br];
  uint_32 t_bl = texture[i_bl];

  uint_32 tmp1[4], tmp2[4];

  MUL_ADD_PIX(tmp1, t_tl, fun, t_tr, fu);
  MUL_ADD_PIX(tmp2, t_bl, fun, t_br, fu);

  return MUL_ADD_ROUND(tmp1, fvn, tmp2, fv);
}

static int power_of_2(int a)
{
  int i;
  for (i = 0; i < 16; ++i)
    if (a == (1 << i))
      return i;

  return 0;
}

static int square_and_power_of_2(int width, int height)
{
  return (width == height) && power_of_2(width);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  double rot_angle;

  int x,y;
  struct vector_t p;

  TexturePoint* gridpointer;	
	
  int xres = trim_int(inst->in_xres->number, 0, 1024);
  int yres = trim_int(inst->in_yres->number, 0, 1024);

  double radius = trim_double(inst->in_radius->number, 1, 100);
  double shade  = trim_double(inst->in_shading->number, 0, 1)* 10;

  int do_shade = shade >= 0.05;
  const double txt_len = 2*M_PI*radius*3;
  double move  = trim_double(inst->in_t->number, 0, 10000) * txt_len;
  double zdist = trim_double(inst->in_zdist->number, 0.1, 10);

  double rot   = trim_double(inst->in_rot->number, -180, 180);

  int tex_xsize = inst->in_b->xsize;
  int tex_ysize = inst->in_b->ysize;
  const uint_32* texture = inst->in_b->framebuffer;
  uint_32* dst = 0;

  const double f_u = (tex_xsize-1) / (2*M_PI);
  const double f_v = (tex_ysize-1) / txt_len;

  double tex_ysize_edge = tex_ysize - 0.501;
  if (tex_xsize < 1 || tex_ysize < 1)
    return;

  if (do_shade)
    my->libgrid_flags |= LIBGRID_USE_Z;
  else
    my->libgrid_flags &= (~LIBGRID_USE_Z);

  if (square_and_power_of_2(tex_xsize, tex_ysize))
    {
      my->libgrid_flags |= LIBGRID_POWER_OF_2;
      grid_change_texture(&my->grid, power_of_2(tex_xsize),
                          texture, my->libgrid_flags);
    }
  else
    {
      my->libgrid_flags &= (~LIBGRID_POWER_OF_2);
      grid_change_texture(&my->grid, tex_xsize,
                          texture, my->libgrid_flags);
    }


  if (my->xres_old !=  xres || my->yres_old != yres)
    {
      FrameBufferAttributes attribs;

      attribs.xsize = xres;
      attribs.ysize = yres;
      framebuffer_changeAttributes(inst->out_r, &attribs);

      if (grid_change_dst(&my->grid,xres,yres,inst->out_r->framebuffer) == 0)
        {
          s_log(0, "Could not change grid");
          return;
        }

      my->xres_old = xres;
      my->yres_old = yres;				
    }

  dst = inst->out_r->framebuffer;

  //set up viewpoint
  p.x = radius*(inst->in_pos->x*1.5 - 0.75);
  p.y = radius*(inst->in_pos->y*1.5 - 0.75);
  p.z = -zdist;

  rot_angle = rot/180 * M_PI;
  if (rot_angle < 0)
    rot_angle = 2*M_PI + rot_angle;

  if (strcmp(inst->in_mode->text, "krass") == 0)
    {
      const double f_uu = f_u * 65536.;
      const double f_vv = f_v * 65536.;

      for(y=0; y < yres; ++y)
        {
          for(x=0; x < xres; ++x)
            {
              struct vector_t dir;
              int_32 u, v;
              double t;
              int idx, uu, vv;

              //intersection = t*direction
              dir.x = ((double) x) / xres - 0.5; //TODO
              dir.y = ((double) y) / yres - 0.5; //TODO
              dir.z = zdist;

              t = intersect(&p, &dir, radius);
			
              if(t < 1)
                {
                  u = 0;//TEX_SIZE/2;
                  v = 0;//TEX_SIZE/2;
                } 
              else 
                {
                  double alpha;
                  struct vector_t is;
				
                  is.x = p.x + t*dir.x; 
                  is.y = p.y + t*dir.y;
                  is.z = p.z + t*dir.z + move;

                  alpha = angle(is.x, is.y) + rot_angle;

                  //apply cylindric texture-mapping
                  u = (int_32) lrint(f_uu * alpha);
                  v = (int_32) lrint(fmod(f_vv * is.z, 65536. * tex_ysize));
                }

              uu = (u >> 16);
              vv = (v >> 16);
              while (uu >= tex_xsize)
                uu -= tex_xsize;

              while (vv >= tex_ysize)
                vv -= tex_ysize;

              idx = uu + vv*tex_xsize;

              if (uu == tex_xsize-1 || vv == tex_ysize-1)
                {
                  *dst = texture[idx];
                }
              else
                {
                  assert(0 <= uu <= tex_xsize - 2);
                  assert(0 <= vv <= tex_ysize - 2);

                  *dst = PIX_AVG(texture, u & 0x0000ffff, v & 0x0000ffff,
                                 idx, idx + 1,
                                 idx + tex_xsize + 1,
                                 idx + tex_xsize);
                }
              ++dst;
            }
        }
    }
  else
    {
      gridpointer = my->grid.points;
      
      //compute a grid of GRID_SIZExGRID_SIZE blocks
      for(y=0; y <= yres; y += GRIDSIZE)
        {
          for(x=0; x <= xres; x += GRIDSIZE)
            {
              struct vector_t dir;
              double u, v;
              int z, v_mod;
              double t;

              //intersection = t*direction
              dir.x = ((double) x) / xres - 0.5;// - p.x;
              dir.y = ((double) y) / yres - 0.5;// - p.y;
              dir.z = zdist;

              t = intersect(&p, &dir, radius);
			
              if(t < 1)
                {
                  u = 0;//TEX_SIZE/2;
                  v = 0;//TEX_SIZE/2;
                  z = 255;
                } 
              else
                {
                  double alpha;
                  struct vector_t is;
				
                  is.x = p.x + t*dir.x; 
                  is.y = p.y + t*dir.y;
                  is.z = p.z + t*dir.z + move;

                  alpha = angle(is.x, is.y) + rot_angle;
                  if (alpha >= 2*M_PI)
                    alpha -= 2*M_PI;

                  //apply cylindric texture-mapping
                  u = alpha * f_u;
                  v = is.z * f_v;

                  if (do_shade)
                    z = (int) (shade * (t - 1));
                  else
                    z = 0;
                }

              v_mod = 0;
              while (v >= tex_ysize_edge)
                {
                  v -= tex_ysize_edge;
                  ++v_mod;
                }

              if (v_mod & 1) v = tex_ysize_edge - v;

              gridpointer->u = (int_32) (65536 * u);
              gridpointer->v = (int_32) (65536 * v);
              gridpointer->z = minimum(z, 255) << 16;

              assert(gridpointer->u >> 16 >= 0);
              assert(gridpointer->v >> 16 >= 0);
              assert(gridpointer->u >> 16 <= tex_xsize-1);
              assert(gridpointer->v >> 16 <= tex_ysize-1);

              if (u >= tex_xsize - (1+ GRIDSIZE/ 2) 
                  || u < (1+GRIDSIZE / 2))
                gridpointer->is_border = 1;
              else
                gridpointer->is_border = 0;

              ++gridpointer;
            }
        }
      
      grid_interpolate(&my->grid);
    }
}
