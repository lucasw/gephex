#include "libgrid.h"

#include <stdlib.h>

static void grid_interpolate_block_reg(Grid* grid, int x, int y);
static void grid_interpolate_block_fast(Grid* grid, int x, int y);

static void grid_interpolate_block_reg_z(Grid* grid, int x, int y);
static void grid_interpolate_block_fast_z(Grid* grid, int x, int y);


void grid_init(Grid* grid, int xsize_texture, int xsize_dst,
	       int ysize_dst, uint_32* texture, uint_32* dst,
	       unsigned int flags)
{
  grid->x_size = xsize_dst / LIBGRID_GRIDSIZE + 1;
  grid->y_size = ysize_dst / LIBGRID_GRIDSIZE + 1;

  grid->points = (TexturePoint*) malloc(grid->x_size * grid->y_size
					* sizeof(TexturePoint));

  grid->texture = texture;

  grid->xsize_texture = xsize_texture;
  grid->flags = flags;

  if (flags & LIBGRID_USE_Z)
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_interpolate_block_fast_z;
      else	
	grid->int_func = grid_interpolate_block_reg_z;
    }
  else
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_interpolate_block_fast;
      else	
	grid->int_func = grid_interpolate_block_reg;
    }

  grid->dst = dst;
  grid->xsize_dst = xsize_dst;
  grid->ysize_dst = ysize_dst;
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
			 uint_32* texture, unsigned int flags)
{
  grid->xsize_texture = xsize_texture;
  grid->texture = texture;
  grid->flags = flags;	

  if (flags & LIBGRID_USE_Z)
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_interpolate_block_fast_z;
      else	
	grid->int_func = grid_interpolate_block_reg_z;
    }
  else
    {
      if (flags & LIBGRID_POWER_OF_2)	
	grid->int_func = grid_interpolate_block_fast;
      else	
	grid->int_func = grid_interpolate_block_reg;
    }

}

void grid_change_dst(Grid* grid, int xsize_dst, int ysize_dst, uint_32* dst)
{
  int xsize_texture = grid->xsize_texture;
  uint_32* texture = grid->texture;
  unsigned int flags = grid->flags;	

  grid_flush(grid);

  grid_init(grid,xsize_texture,xsize_dst,ysize_dst,texture,dst,
	    flags);
}

typedef void (*interpolate_block_t) (Grid*, int, int);

void grid_interpolate_block(Grid* grid, int x, int y)
{
  ((interpolate_block_t) (grid->int_func)) (grid,x,y);
}

void grid_interpolate_block_reg(Grid* grid, int x, int y)
{
  int offset = x + y*grid->x_size;

  TexturePoint* upper_left = grid->points + offset;
  TexturePoint* lower_left = grid->points + offset + grid->x_size;
  TexturePoint* upper_right = grid->points + offset + 1;
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size;

  int_32 u_left, u_right, v_left, v_right;
	
  int_32 step_start_row_u = (int_32) (65536. * (lower_left->u - upper_left->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_start_row_v = (int_32) (65536. * (lower_left->v - upper_left->v)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_u = (int_32) (65536. * (lower_right->u - upper_right->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_v = (int_32) (65536. * (lower_right->v - upper_right->v)/((double) LIBGRID_GRIDSIZE));
	
  uint_32 start_row_uu = upper_left->u << 16;
  uint_32 start_row_vv = upper_left->v << 16;
  uint_32 end_row_uu = upper_right->u << 16;
  uint_32 end_row_vv = upper_right->v << 16;
  uint_32 u_line_index, v_line_index;
  int_32 step_line_u, step_line_v;

  uint_32* dst = grid->dst + y * LIBGRID_GRIDSIZE * grid->xsize_dst 
    + x *  LIBGRID_GRIDSIZE;
  uint_32* src = grid->texture;
	
  for(y=0; y < LIBGRID_GRIDSIZE; ++y)
    {
      u_left  = start_row_uu >> 16;
      u_right = end_row_uu >> 16;
      v_left = start_row_vv >> 16;
      v_right = end_row_vv >> 16;
		
      u_line_index = start_row_uu;
      v_line_index = start_row_vv;
		
      step_line_u = (int_32) (65536. * (u_right-u_left)/((double) LIBGRID_GRIDSIZE));
      step_line_v = (int_32) (65536. * (v_right-v_left)/((double) LIBGRID_GRIDSIZE));
		
      //neuer step
      for(x=0; x<LIBGRID_GRIDSIZE; ++x)
	{
	  u_left = u_line_index >> 16;
	  v_left = v_line_index >> 16;
	  *dst = src[u_left+ v_left*grid->xsize_texture];
	  u_line_index += step_line_u;
	  v_line_index += step_line_v;
	  ++dst;
	}
		
      start_row_uu += step_start_row_u;
      end_row_uu += step_end_row_u;
      start_row_vv += step_start_row_v;
      end_row_vv += step_end_row_v;
		
      dst += (grid->xsize_dst - LIBGRID_GRIDSIZE);
    }
}

void grid_interpolate_block_fast(Grid* grid, int x, int y)
{
  int offset = x + y*grid->x_size;

  TexturePoint* upper_left = grid->points + offset;
  TexturePoint* lower_left = grid->points + offset + grid->x_size;
  TexturePoint* upper_right = grid->points + offset + 1;
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size;

  int_32 u_left, u_right, v_left, v_right;
	
  int_32 step_start_row_u = (int_32) (65536. * (lower_left->u - upper_left->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_start_row_v = (int_32) (65536. * (lower_left->v - upper_left->v)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_u = (int_32) (65536. * (lower_right->u - upper_right->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_v = (int_32) (65536. * (lower_right->v - upper_right->v)/((double) LIBGRID_GRIDSIZE));
	
  uint_32 start_row_uu = upper_left->u << 16;
  uint_32 start_row_vv = upper_left->v << 16;
  uint_32 end_row_uu = upper_right->u << 16;
  uint_32 end_row_vv = upper_right->v << 16;
  uint_32 u_line_index, v_line_index;
  int_32 step_line_u, step_line_v;

  uint_32* dst = grid->dst + y * LIBGRID_GRIDSIZE * grid->xsize_dst 
    + x *  LIBGRID_GRIDSIZE;
  uint_32* src = grid->texture;
	
  for(y=0; y < LIBGRID_GRIDSIZE; ++y)
    {
      u_left  = start_row_uu >> 16;
      u_right = end_row_uu >> 16;
      v_left = start_row_vv >> 16;
      v_right = end_row_vv >> 16;
		
      u_line_index = start_row_uu;
      v_line_index = start_row_vv;
		
      step_line_u = (int_32) (65536. * (u_right-u_left)/((double) LIBGRID_GRIDSIZE));
      step_line_v = (int_32) (65536. * (v_right-v_left)/((double) LIBGRID_GRIDSIZE));
		
      //neuer step
      for(x=0; x<LIBGRID_GRIDSIZE; ++x)
	{
	  u_left = u_line_index >> 16;
	  v_left = v_line_index >> 16;
	  *dst = src[u_left+ (v_left << grid->xsize_texture)];
	  u_line_index += step_line_u;
	  v_line_index += step_line_v;
	  ++dst;
	}
		
      start_row_uu += step_start_row_u;
      end_row_uu += step_end_row_u;
      start_row_vv += step_start_row_v;
      end_row_vv += step_end_row_v;
		
      dst += (grid->xsize_dst - LIBGRID_GRIDSIZE);
    }
}

void grid_interpolate_block_reg_z(Grid* grid, int x, int y)
{
  int offset = x + y*grid->x_size;

  TexturePoint* upper_left = grid->points + offset;
  TexturePoint* lower_left = grid->points + offset + grid->x_size;
  TexturePoint* upper_right = grid->points + offset + 1;
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size;

  int_32 u_left, u_right, v_left, v_right;
	
  int_32 step_start_row_u = (int_32) (65536. * (lower_left->u - upper_left->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_start_row_v = (int_32) (65536. * (lower_left->v - upper_left->v)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_u = (int_32) (65536. * (lower_right->u - upper_right->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_v = (int_32) (65536. * (lower_right->v - upper_right->v)/((double) LIBGRID_GRIDSIZE));
	
  uint_32 start_row_uu = upper_left->u << 16;
  uint_32 start_row_vv = upper_left->v << 16;
  uint_32 end_row_uu = upper_right->u << 16;
  uint_32 end_row_vv = upper_right->v << 16;
  uint_32 u_line_index, v_line_index;
  int_32 step_line_u, step_line_v;

  uint_32* dst = grid->dst + y * LIBGRID_GRIDSIZE * grid->xsize_dst 
    + x *  LIBGRID_GRIDSIZE;
  uint_32* src = grid->texture;
	
  for(y=0; y < LIBGRID_GRIDSIZE; ++y)
    {
      u_left  = start_row_uu >> 16;
      u_right = end_row_uu >> 16;
      v_left = start_row_vv >> 16;
      v_right = end_row_vv >> 16;
		
      u_line_index = start_row_uu;
      v_line_index = start_row_vv;
		
      step_line_u = (int_32) (65536. * (u_right-u_left)/((double) LIBGRID_GRIDSIZE));
      step_line_v = (int_32) (65536. * (v_right-v_left)/((double) LIBGRID_GRIDSIZE));
		
      //neuer step
      for(x=0; x<LIBGRID_GRIDSIZE; ++x)
	{
	  u_left = u_line_index >> 16;
	  v_left = v_line_index >> 16;
	  *dst = src[u_left+ v_left*grid->xsize_texture];
	  u_line_index += step_line_u;
	  v_line_index += step_line_v;
	  ++dst;
	}
		
      start_row_uu += step_start_row_u;
      end_row_uu += step_end_row_u;
      start_row_vv += step_start_row_v;
      end_row_vv += step_end_row_v;
		
      dst += (grid->xsize_dst - LIBGRID_GRIDSIZE);
    }
}

void grid_interpolate_block_fast_z(Grid* grid, int x, int y)
{
  int offset = x + y*grid->x_size;

  TexturePoint* upper_left = grid->points + offset;
  TexturePoint* lower_left = grid->points + offset + grid->x_size;
  TexturePoint* upper_right = grid->points + offset + 1;
  TexturePoint* lower_right = grid->points + offset + 1 + grid->x_size;

  int_32 u_left, u_right, v_left, v_right, z_right, z_left;
	
  int_32 step_start_row_u = (int_32) (65536. * (lower_left->u - upper_left->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_start_row_v = (int_32) (65536. * (lower_left->v - upper_left->v)/((double) LIBGRID_GRIDSIZE));
  int_32 step_start_row_z = (int_32) (65536. * (lower_left->z - upper_left->z)/((double) LIBGRID_GRIDSIZE));

  int_32 step_end_row_u = (int_32) (65536. * (lower_right->u - upper_right->u)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_v = (int_32) (65536. * (lower_right->v - upper_right->v)/((double) LIBGRID_GRIDSIZE));
  int_32 step_end_row_z = (int_32) (65536. * (lower_right->z - upper_right->z)/((double) LIBGRID_GRIDSIZE));
	
  uint_32 start_row_uu = upper_left->u << 16;
  uint_32 start_row_vv = upper_left->v << 16;
  uint_32 start_row_zz = upper_left->z << 16;
  uint_32 end_row_uu = upper_right->u << 16;
  uint_32 end_row_vv = upper_right->v << 16;
  uint_32 end_row_zz = upper_right->z << 16;
  uint_32 u_line_index, v_line_index, z_line_index;
  int_32 step_line_u, step_line_v, step_line_z;

  uint_32* dst = grid->dst + y * LIBGRID_GRIDSIZE * grid->xsize_dst 
    + x *  LIBGRID_GRIDSIZE;
  uint_32* src = grid->texture;
	
  for(y=0; y < LIBGRID_GRIDSIZE; ++y)
    {
      u_left  = start_row_uu >> 16;
      u_right = end_row_uu >> 16;
      v_left = start_row_vv >> 16;
      v_right = end_row_vv >> 16;
      z_left  = start_row_zz >> 16;
      z_right = end_row_zz >> 16;
		
      u_line_index = start_row_uu;
      v_line_index = start_row_vv;
      z_line_index  = start_row_zz;
		
      step_line_u = (int_32) (65536. * (u_right-u_left)/((double) LIBGRID_GRIDSIZE));
      step_line_v = (int_32) (65536. * (v_right-v_left)/((double) LIBGRID_GRIDSIZE));
      step_line_z = (int_32) (65536. * (z_right-z_left)/((double) LIBGRID_GRIDSIZE));
		
      //neuer step
      for(x=0; x<LIBGRID_GRIDSIZE; ++x)
	{
	  int index;
	  unsigned char* texel;
	  unsigned char* pixel = (unsigned char*) dst;

	  u_left = u_line_index >> 16;
	  v_left = v_line_index >> 16;
	  z_left = z_line_index >> 16;

	  index = u_left+ (v_left << grid->xsize_texture);

	  texel = (unsigned char*) (src + index);

	  *pixel = ((255 - z_left) * *texel) >> 8;
	  ++pixel;
	  ++texel;

	  *pixel = ((255 - z_left) * *texel) >> 8;
	  ++pixel;
	  ++texel;

	  *pixel = ((255 - z_left) * *texel) >> 8;						

	  u_line_index += step_line_u;
	  v_line_index += step_line_v;
	  z_line_index += step_line_z;
	  ++dst;
	}
		
      start_row_uu += step_start_row_u;
      end_row_uu   += step_end_row_u;

      start_row_vv += step_start_row_v;
      end_row_vv   += step_end_row_v;

      start_row_zz += step_start_row_z;
      end_row_zz   += step_end_row_z;
		
      dst += (grid->xsize_dst - LIBGRID_GRIDSIZE);
    }
}

void grid_interpolate(Grid* grid)
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
