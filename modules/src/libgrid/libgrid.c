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

/**
 * TODO: linear filtering
 */

#include "libgrid.h"

#include <stdlib.h>

//--------------------------------------------------------------------------

static void MUL_ADD_PIX(uint_32* r,
                        uint_32 p1, int_32 f1,
                        uint_32 p2, int_32 f2);

static uint_32 MUL_ADD_ROUND(const uint_32* p1, int_32 f1,
                             const uint_32* p2, int_32 f2);

static uint_32 PIX_AVG(const uint_32* texture,
                       int i_tl, int i_tr,
                       int i_br, int i_bl);

static uint_32 PIX_AVG_LIN(const uint_32* texture,
                           int_32 fu, int_32 fv,
                           int i_tl, int i_tr,
                           int i_br, int i_bl);


static void grid_ip_block_reg(const Grid* grid, int x, int y);
static void grid_ip_block_fast(const Grid* grid, int x, int y);

static void grid_ip_block_reg_z(const Grid* grid, int x, int y);
static void grid_ip_block_fast_z(const Grid* grid, int x, int y);

//--------------------------------------------------------------------------

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

static __inline uint_32 PIX_AVG_LIN(const uint_32* texture,
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

static __inline uint_32 PIX_AVG(const uint_32* texture,
                                int i_tl, int i_tr,
                                int i_br, int i_bl)
{
  int_32 f = (int_32) (0.5 * 65536);
  return PIX_AVG_LIN(texture, f, f,
                     i_tl, i_tr,
                     i_br, i_bl);

}

//--------------------------------------------------------------------------

int grid_init(Grid* grid, int grid_size_log,
              int xsize_texture, int xsize_dst,
              int ysize_dst, const uint_32* texture, uint_32* dst,
              unsigned int flags)
{
  TexturePoint* tp;
  int i;
  int x_size, y_size;
  int grid_size;

  grid_size = 1 << grid_size_log;

  x_size = xsize_dst / grid_size + 1;
  y_size = ysize_dst / grid_size + 1;

  tp = (TexturePoint*) malloc(x_size * y_size * sizeof(TexturePoint));

  if (tp == 0)
    return 0;

  grid->grid_size_log = grid_size_log;
  grid->grid_size     = grid_size;

  grid->x_size = x_size;
  grid->y_size = y_size;

  grid->points = tp;

  grid->texture = texture;

  grid->xsize_texture = xsize_texture;
  grid->flags = flags;

  if (flags & LIBGRID_USE_Z)
    {
      if (flags & LIBGRID_POWER_OF_2)
	grid->int_func = grid_ip_block_fast_z;
      else
	grid->int_func = grid_ip_block_reg_z;
    }
  else
    {
      if (flags & LIBGRID_POWER_OF_2)
	grid->int_func = grid_ip_block_fast;
      else
	grid->int_func = grid_ip_block_reg;
    }

  grid->dst = dst;
  grid->xsize_dst = xsize_dst;
  grid->ysize_dst = ysize_dst;

  tp = grid->points;
  for (i = grid->y_size*grid->x_size - 1; i >= 0; --i, ++tp)
    {
      tp->u = 0;
      tp->v = 0;
      tp->z = 0;
      tp->is_border = 0;
    }

  return 1;
}

void grid_flush(Grid* grid)
{
  if (grid->points)
    {
      free(grid->points);
      grid->points = 0;
    }
}

void grid_change_texture(Grid* grid, int xsize_texture,
			 const uint_32* texture, unsigned int flags)
{
  grid->xsize_texture = xsize_texture;
  grid->texture       = texture;
  grid->flags         = flags;	

  if (flags & LIBGRID_USE_Z)
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_ip_block_fast_z;
      else	
	grid->int_func = grid_ip_block_reg_z;
    }
  else
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_ip_block_fast;
      else	
	grid->int_func = grid_ip_block_reg;
    }

}

int grid_change_dst(Grid* grid, int xsize_dst, int ysize_dst, uint_32* dst)
{
  int xsize_texture = grid->xsize_texture;
  const uint_32* texture = grid->texture;
  unsigned int flags = grid->flags;	

  // store the array (is freed only if init succeeds)
  TexturePoint* p = grid->points;

  if (grid_init(grid, grid->grid_size_log, xsize_texture, xsize_dst, ysize_dst,
                texture, dst, flags) == 0)
    {
      grid->points = p;
      return 0;
    }
  else
    {
      free(p);
      return 1;
    }
}

typedef void (*ip_block_t) (const Grid*, int, int);

void grid_interpolate_block(const Grid* grid, int x, int y)
{
  ((ip_block_t) (grid->int_func)) (grid,x,y);
}


void grid_interpolate(const Grid* grid)
{
  int x,y;

  for(y=0; y < grid->y_size-1; ++y)
    {
      for(x=0; x < grid->x_size-1; ++x)
	{
	  grid_interpolate_block(grid,x,y);			
	}		
    }
}

//---------------------------------------------------------------------------

static void block_fill(uint_32* dst, uint_32 col, int bsize, int dst_xsize)
{
  int x, y;
  for (y = 0; y < bsize; ++y)
    {
      for (x = 0; x < bsize; ++x)
        {
          *dst = col;
          ++dst;
        }
      dst += dst_xsize - bsize;
    }
}

//---------------------------------------------------------------------------

#define GRID_IP_REG_TEMPLATE(grid, x, y, INNER_LOOP) \
{ \
  int offset = x + y*grid->x_size; \
  int tex_xsize = grid->xsize_texture;  \
\
  TexturePoint* upper_left  = grid->points + offset; \
  TexturePoint* lower_left  = grid->points + offset + grid->x_size; \
  TexturePoint* upper_right = grid->points + offset + 1; \
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size; \
\
  int_32 u_left, u_right, v_left, v_right; \
\
  int_32 start_col_uu = upper_left->u; \
  int_32 start_col_vv = upper_left->v; \
  int_32 end_col_uu   = upper_right->u; \
  int_32 end_col_vv   = upper_right->v; \
\
  int_32 step_start_col_u = (lower_left->u - upper_left->u) \
    >> grid->grid_size_log; \
  int_32 step_start_col_v = (lower_left->v - upper_left->v) \
    >> grid->grid_size_log; \
  int_32 step_end_col_u   = (lower_right->u - upper_right->u) \
    >> grid->grid_size_log; \
  int_32 step_end_col_v   = (lower_right->v - upper_right->v) \
    >> grid->grid_size_log; \
\
  int_32 u_line_index, v_line_index; \
  int_32 step_line_u, step_line_v; \
\
  uint_32* dst = grid->dst + (y << grid->grid_size_log) * grid->xsize_dst \
    + (x << grid->grid_size_log); \
  const uint_32* src = grid->texture; \
\
  if (lower_left->is_border || upper_left->is_border) \
  { \
      int u_lr = lower_right->u >> 16; \
      int v_lr = lower_right->v >> 16; \
      int u_ll = lower_left->u  >> 16; \
      int v_ll = lower_left->v  >> 16; \
      int u_ul = upper_left->u  >> 16; \
      int v_ul = upper_left->v  >> 16; \
      int u_ur = upper_right->u >> 16; \
      int v_ur = upper_right->v >> 16; \
      uint_32 col; \
      if (grid->flags & LIBGRID_POWER_OF_2) \
         col = PIX_AVG(src,     \
                       u_lr + (v_lr<<tex_xsize),  \
                       u_ll + (v_ll<<tex_xsize),  \
                       u_ul + (v_ul<<tex_xsize),  \
                       u_ur + (v_ur<<tex_xsize)); \
      else \
         col = PIX_AVG(src,     \
                       u_lr + v_lr*tex_xsize,  \
                       u_ll + v_ll*tex_xsize,  \
                       u_ul + v_ul*tex_xsize,  \
                       u_ur + v_ur*tex_xsize); \
      block_fill(dst, col, \
                 grid->grid_size, grid->xsize_dst); \
   return; \
  } \
\
  for(y = 0; y < grid->grid_size; ++y) \
    { \
      u_left  = start_col_uu; \
      u_right = end_col_uu; \
      v_left  = start_col_vv; \
      v_right = end_col_vv; \
\
      u_line_index = start_col_uu; \
      v_line_index = start_col_vv; \
\
      step_line_u = (int_32) ((u_right-u_left) >> grid->grid_size_log); \
      step_line_v = (int_32) ((v_right-v_left) >> grid->grid_size_log); \
\
      for(x=0; x < grid->grid_size; ++x) \
	{ \
          INNER_LOOP(dst, src, u_line_index, v_line_index, tex_xsize); \
	  u_line_index += step_line_u; \
	  v_line_index += step_line_v; \
	  ++dst; \
	} \
\
      start_col_uu += step_start_col_u; \
      end_col_uu   += step_end_col_u; \
      start_col_vv += step_start_col_v; \
      end_col_vv   += step_end_col_v; \
\
      dst += (grid->xsize_dst - grid->grid_size); \
    } \
} \

//---------------------------------------------------------------------------

static __inline void inner_loop_reg(uint_32* dst, const uint_32* txt,
                                    int_32 u, int_32 v,
                                    int tex_xsize)
{
  int uu = u >> 16;
  int vv = v >> 16;
  *dst = txt[uu + vv * tex_xsize];
}

static __inline void inner_loop_fast(uint_32* dst, const uint_32* txt,
                                     int_32 u, int_32 v,
                                     int tex_xsize)
{
  int uu = u >> 16;
  int vv = v >> 16;
  *dst = txt[uu + (vv << tex_xsize)];
}

//---------------------------------------------------------------------------

static void grid_ip_block_reg(const Grid* grid, int x, int y)
{
  GRID_IP_REG_TEMPLATE(grid, x, y, inner_loop_reg);
}

static void grid_ip_block_fast(const Grid* grid, int x, int y)
{
  GRID_IP_REG_TEMPLATE(grid, x, y, inner_loop_fast);
}

//---------------------------------------------------------------------------

#define GRID_IP_Z_TEMPLATE(grid, x, y, INNER_LOOP) \
{ \
  int offset = x + y*grid->x_size; \
  int tex_xsize = grid->xsize_texture;  \
\
  TexturePoint* upper_left  = grid->points + offset; \
  TexturePoint* lower_left  = grid->points + offset + grid->x_size; \
  TexturePoint* upper_right = grid->points + offset + 1; \
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size; \
\
  int_32 u_left, u_right, v_left, v_right, z_left, z_right; \
\
  int_32 start_col_uu = upper_left->u; \
  int_32 start_col_vv = upper_left->v; \
  int_32 start_col_zz = upper_left->z; \
  int_32 end_col_uu   = upper_right->u; \
  int_32 end_col_vv   = upper_right->v; \
  int_32 end_col_zz   = upper_right->z; \
\
  int_32 step_start_col_u = (lower_left->u - upper_left->u) \
    >> grid->grid_size_log; \
  int_32 step_start_col_v = (lower_left->v - upper_left->v) \
    >> grid->grid_size_log; \
  int_32 step_start_col_z = (lower_left->z - upper_left->z) \
    >> grid->grid_size_log; \
  int_32 step_end_col_u   = (lower_right->u - upper_right->u) \
    >> grid->grid_size_log; \
  int_32 step_end_col_v   = (lower_right->v - upper_right->v) \
    >> grid->grid_size_log; \
  int_32 step_end_col_z   = (lower_right->z - upper_right->z) \
    >> grid->grid_size_log; \
\
  int_32 u_line_index, v_line_index, z_line_index; \
  int_32 step_line_u, step_line_v, step_line_z; \
\
  uint_32* dst = grid->dst + (y << grid->grid_size_log) * grid->xsize_dst \
    + (x << grid->grid_size_log); \
  const uint_32* src = grid->texture; \
\
  if (lower_left->is_border || upper_left->is_border) \
  { \
   uint_32 col_shaded; \
   uint_8* pixel = (uint_8*) &col_shaded; \
 \
   int u_lr = lower_right->u >> 16; \
   int v_lr = lower_right->v >> 16; \
   int u_ll = lower_left->u  >> 16;  \
   int v_ll = lower_left->v  >> 16;  \
   int u_ul = upper_left->u  >> 16;  \
   int v_ul = upper_left->v  >> 16;  \
   int u_ur = upper_right->u >> 16; \
   int v_ur = upper_right->v >> 16; \
   uint_32 col; \
   int zz = lower_right->z >> 16; \
 \
   uint_8* texel = (uint_8*) &col; \
   if (grid->flags & LIBGRID_POWER_OF_2) \
      col = PIX_AVG(src,     \
                    u_lr + (v_lr<<tex_xsize),  \
                    u_ll + (v_ll<<tex_xsize),  \
                    u_ul + (v_ul<<tex_xsize),  \
                    u_ur + (v_ur<<tex_xsize)); \
   else \
      col = PIX_AVG(src,     \
                    u_lr + v_lr*tex_xsize,  \
                    u_ll + v_ll*tex_xsize,  \
                    u_ul + v_ul*tex_xsize,  \
                    u_ur + v_ur*tex_xsize); \
 \
   pixel[0] = ((255 - zz) * texel[0]) >> 8; \
   pixel[1] = ((255 - zz) * texel[1]) >> 8; \
   pixel[2] = ((255 - zz) * texel[2]) >> 8; \
   block_fill(dst, col_shaded, grid->grid_size, grid->xsize_dst); \
   return; \
  } \
  \
  for(y = 0; y < grid->grid_size; ++y) \
    { \
      u_left  = start_col_uu; \
      u_right = end_col_uu; \
      v_left  = start_col_vv; \
      v_right = end_col_vv; \
      z_left  = start_col_zz; \
      z_right = end_col_zz; \
\
      u_line_index = start_col_uu; \
      v_line_index = start_col_vv; \
      z_line_index = start_col_zz; \
\
      step_line_u = (int_32) ((u_right-u_left) >> grid->grid_size_log); \
      step_line_v = (int_32) ((v_right-v_left) >> grid->grid_size_log); \
      step_line_z = (int_32) ((z_right-z_left) >> grid->grid_size_log); \
\
      for(x=0; x < grid->grid_size; ++x) \
	{ \
          INNER_LOOP(dst, src, u_line_index, v_line_index,  \
                     z_line_index, tex_xsize); \
	  u_line_index += step_line_u; \
	  v_line_index += step_line_v; \
	  z_line_index += step_line_z; \
	  ++dst; \
	} \
\
      start_col_uu += step_start_col_u; \
      end_col_uu   += step_end_col_u; \
      start_col_vv += step_start_col_v; \
      end_col_vv   += step_end_col_v; \
      start_col_zz += step_start_col_z; \
      end_col_zz   += step_end_col_z; \
\
      dst += (grid->xsize_dst - grid->grid_size); \
    } \
} \


//---------------------------------------------------------------------------

static __inline void inner_loop_reg_z(uint_32* dst, const uint_32* txt,
                                      int_32 u, int_32 v, int_32 z,
                                      int tex_xsize)
{
  uint_8* pixel = (uint_8*) dst;

  const int uu = u >> 16;
  const int vv = v >> 16;
  const int zz = 255 - (z >> 16);

  const int index = uu + (vv * tex_xsize);

  const uint_8* texel = (const uint_8*) (txt + index);

  pixel[0] = (zz * texel[0]) >> 8;
  pixel[1] = (zz * texel[1]) >> 8;
  pixel[2] = (zz * texel[2]) >> 8;
}

static __inline void inner_loop_fast_z(uint_32* dst, const uint_32* txt,
                                       int_32 u, int_32 v, int_32 z,
                                       int tex_xsize)
{
  uint_8* pixel = (uint_8*) dst;

  const int uu = u >> 16;
  const int vv = v >> 16;
  const int zz = 255 - (z >> 16);

  const int index = uu + (vv << tex_xsize);

  const uint_8* texel = (const uint_8*) (txt + index);

  texel = (uint_8*) (txt + index);

  pixel[0] = (zz * texel[0]) >> 8;
  pixel[1] = (zz * texel[1]) >> 8;
  pixel[2] = (zz * texel[2]) >> 8;
}

//---------------------------------------------------------------------------

static void grid_ip_block_reg_z(const Grid* grid, int x, int y)
{
  GRID_IP_Z_TEMPLATE(grid, x, y, inner_loop_reg_z);
}

static void grid_ip_block_fast_z(const Grid* grid, int x, int y)
{
  GRID_IP_Z_TEMPLATE(grid, x, y, inner_loop_fast_z);
}

//--------------------------------------------------------------------------
