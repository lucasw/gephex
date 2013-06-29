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

#ifndef INCLUDED_LIBGRID_H
#define INCLUDED_LIBGRID_H

/************************************************************************/
/*  Library to provide functionality for modules to interpolate over	*/
/*  a given grid on a texture (or whatever).          			*/
/************************************************************************/


#define LIBGRID_POWER_OF_2 0x01
#define LIBGRID_USE_Z	   0x02

#include "basic_types.h"

typedef struct TexturePoint_
{
  int_32 u;
  int_32 v;
  int_32 z;

  int is_border;
} TexturePoint;

typedef struct Grid_
{
  int grid_size_log;
  int grid_size;

  int x_size;
  int y_size;
  TexturePoint* points;

  const uint_32* texture;
  uint_32* dst;

  int xsize_texture;	
  unsigned int flags;	
	
  int xsize_dst;
  int ysize_dst;
  void (*int_func)(const struct Grid_*, int, int);

} Grid;


/**
 * Initializes a grid structure. grid must point to an existing struct.
 * If flags has LIBGRID_USE_POWER_OF_2 set, xsize_texture is assumed to be
 * the log_2 of the true texture size.
 * For example, a value of 8 would mean that the texture is 256x256
 * The parameter use_z_value controls, wether interpolate shades
 * according to the z -values of the texture-points.
 */
int grid_init(Grid* grid, int grid_size_log,
              int xsize_texture, int xsize_dst, int ysize_dst,
              const uint_32* texture, uint_32* dst, unsigned int flags);

/**
 * Frees all memory the grid has allocated.
 */
void grid_flush(Grid* grid);

/**
 * Call if the texture has changed.
 * If flags has LIBGRID_USE_POWER_OF_2 set, xsize_texture is assumed to be
 * the log_2 of the true texture size.
 */
void grid_change_texture(Grid* grid, int xsize_texture,
                         const uint_32* texture, unsigned int flags);

/**
 * Call if the dst framebuffer has changed.
 */
int grid_change_dst(Grid* grid, int xsize_dst, int ysize_dst, uint_32* dst);


/**
 * Interpolates the block at (x,y) in the grid coordinate system.
 */
void grid_interpolate_block(const Grid* grid, int x, int y);

/**
 * Interpolates the whole grid.
 */
void grid_interpolate(const Grid* grid);

#endif
