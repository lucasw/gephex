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

#include "planemodule.h"

#include <limits.h>
#include <math.h>
#include "../libgrid/libgrid.h"

#define GRIDSIZE_LOG 4
#define GRIDSIZE (1 << GRIDSIZE_LOG)

#define GRID_OPTIONS 0

#if defined (_MSC_VER)
#define lrint(a) ((int_32) (a))
#endif

#ifdef M_PI
#undef M_PI
#endif

static logT s_log = 0;

static const double M_PI = 3.1415926535897932384;

typedef struct _MyInstance 
{
  int xres_old;
  int yres_old;

  int libgrid_flags;
  Grid grid;
	
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  log_function = s_log;
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
    {
      s_log(0, "Could not allocate MyInstance");
      return 0;
    }

  my->libgrid_flags = GRID_OPTIONS;

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


struct vector_t
{
  double v[3];
};

struct matrix_t
{
  double m[3][3];
};

static void matr_mult(struct matrix_t* dst,
                      const struct matrix_t* lhs,
                      const struct matrix_t* rhs)
{
  int col, row, i;
  for (col = 0; col < 3; ++col)
    {
      for (row = 0; row < 3; ++row)
        {
          double sc = 0;

          for (i = 0; i < 3; ++i)
            sc += rhs->m[i][col] * lhs->m[row][i];

          dst->m[row][col] = sc;
        }
    }
}

static void matr_mult_vec(struct vector_t* dst,
                          const struct matrix_t* A,
                          const struct vector_t* v)
{
  int col, row;
  for (row = 0; row < 3; ++row)
    {
      double sc = 0;
      for (col = 0; col < 3; ++col)
        {
          sc += A->m[row][col] * v->v[col];
        }
      dst->v[row] = sc;
    }
}

static double scalar_product(const struct vector_t* lhs,
                             const struct vector_t* rhs)
{
  return lhs->v[0]*rhs->v[0] + lhs->v[1]*rhs->v[1] + lhs->v[2]*rhs->v[2];
}
                           

static void rot_x(struct matrix_t* dst, double alpha)
{
  double ca = cos(alpha);
  double sa = sin(alpha);

  dst->m[0][0] = 1; dst->m[0][1] = 0;  dst->m[0][2] =   0;
  dst->m[1][0] = 0; dst->m[1][1] = ca; dst->m[1][2] = -sa;
  dst->m[2][0] = 0; dst->m[2][1] = sa; dst->m[2][2] =  ca;
}

static void rot_y(struct matrix_t* dst, double alpha)
{
  double ca = cos(alpha);
  double sa = sin(alpha);

  dst->m[0][0] = ca; dst->m[0][1] =  0; dst->m[0][2] = -sa;
  dst->m[1][0] =  0; dst->m[1][1] =  1; dst->m[1][2] =   0;
  dst->m[2][0] = sa; dst->m[2][1] =  0; dst->m[2][2] =  ca;
}

static void rot_z(struct matrix_t* dst, double alpha)
{
  double ca = cos(alpha);
  double sa = sin(alpha);

  dst->m[0][0] = ca; dst->m[0][1] = -sa; dst->m[0][2] = 0;
  dst->m[1][0] = sa; dst->m[1][1] =  ca; dst->m[1][2] = 0;
  dst->m[2][0] =  0; dst->m[2][1] =   0; dst->m[2][2] = 1;
}

static __inline double minimum(double a, double b){
  return (a<b) ? a : b;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int x,y;

  struct vector_t p, h_r, h;

  double dd = trim_double(inst->in_d->number, 0.1, 1)+0.5;
  //  double alpha_x =  trim_double(inst->in_alpha_x->number, -90, 90)*M_PI / 180;
  //  double alpha_y =  trim_double(inst->in_alpha_y->number, -90, 90)*M_PI / 180;
  double alpha_z = -trim_double(inst->in_rot->number, 0, 90)*M_PI / 180;

  //  struct matrix_t rotx, roty, rotz, tmp, rot;
  struct matrix_t rot;

  double dist = 1;

  TexturePoint* gridpointer;	
	
  int xres = trim_int(inst->in_xres->number, 0, 1024);
  int yres = trim_int(inst->in_yres->number, 0, 1024);

  double shade = 0.5*(1 - dd) * trim_double(inst->in_shading->number, 0, 1);

  int tex_xsize = inst->in_b->xsize;
  int tex_ysize = inst->in_b->ysize;
  const uint_32* texture = inst->in_b->framebuffer;

  double tex_xsize_edge = tex_xsize - 0.501;
  double tex_ysize_edge = tex_ysize - 0.501;

  int do_shade = shade > 0.001;

  double f_u = 0.33*tex_xsize / dd;
  double f_v = 0.33*tex_ysize / dd;
  double hr_times_p;

  if (tex_xsize < 1 || tex_ysize < 1)
    return;

  if (do_shade)
    my->libgrid_flags |= LIBGRID_USE_Z;
  else
    my->libgrid_flags &= (~LIBGRID_USE_Z);
		
  grid_change_texture(&my->grid, tex_xsize,
                      texture, my->libgrid_flags);

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

  //set up viewpoint
  p.v[0] = 4*(trim_double(inst->in_pos->x,0,1) - 0.5);
  p.v[1] = trim_double(inst->in_pos->y,0,1) * dist;
  p.v[2] = inst->in_t->number * 10;

  // calculate the rotated normal vector
  // (the original normal vector h = (0, 1, 0)
  h.v[0] = 0;
  h.v[1] = 1;
  h.v[2] = 0;

  //  rot_x(&rotx, alpha_x);
  //  rot_y(&roty, alpha_y);
  //  rot_z(&rotz, alpha_z);

  //  matr_mult(&tmp, &rotx, &rotz);
  //  matr_mult(&rot, &roty, &tmp);
  
  rot_z(&rot, alpha_z);
  matr_mult_vec(&h_r, &rot, &h);

  assert(fabs(scalar_product(&h_r, &h_r) - 1.0) < 0.01);

  // calculate the scalarproduct h_r * p
  hr_times_p = scalar_product(&h_r, &p);

  gridpointer = my->grid.points;

  for(y=0; y <= yres; y += GRIDSIZE)
    {
      for(x=0; x <=xres; x += GRIDSIZE)
        {
          int u_mod, v_mod, z;
          double u, v, hr_times_d, lambda;
          struct vector_t dir;

          dir.v[0] = fabs(((double) x)/xres - 0.5); //TODO
          dir.v[1] = fabs(((double) y)/yres - 0.5); //TODO
          dir.v[2] = 1;

          // calculate the scalarproduct h_r * d
          hr_times_d = scalar_product(&h_r, &dir);
          
          if(fabs(hr_times_d) <= 0.01)
            {
              u = 0;
              v = 0;
              z = 255;
            }
          else
            {
              struct vector_t is, is_pr;

              lambda = (dist - hr_times_p) / hr_times_d;
              is.v[0] = p.v[0] + lambda * dir.v[0];
              //              is.v[1] = p.v[1] + lambda * dir.v[1];
              is.v[2] = p.v[2] + lambda * dir.v[2];

              is_pr.v[0] = is.v[0] - dist * h_r.v[0];
              //              is_pr.v[1] = is.v[1] - dist * h_r.v[1];
              is_pr.v[2] = is.v[2] - dist * h_r.v[2];
	
              u = fabs(is_pr.v[0] * f_u);
              v = fabs(is_pr.v[2] * f_v);

              if (do_shade && lambda > 1)
                z = (int) (minimum(255, shade*(lambda-1)));
              else
                z = 0;
            }

          u_mod = 0;
          while (u > tex_xsize_edge)
            {
              u -= tex_xsize_edge;
              u_mod++;
            }

          v_mod = 0;
          while (v > tex_ysize_edge)
            {
              v -= tex_ysize_edge;
              v_mod++;
            }

          if (u_mod & 1)
            u = tex_xsize_edge - u;

          if (v_mod & 1)
            v = tex_ysize_edge - v;

          assert( 0 <= u && u <= tex_xsize_edge );
          assert( 0 <= v && v <= tex_ysize_edge );

          gridpointer->u = (int_32) lrint(u * 65536);
          gridpointer->v = (int_32) lrint(v * 65536);
          gridpointer->z = (int_32) (z << 16);
          ++gridpointer;
        }
    }
	
  grid_interpolate(&my->grid);
}

