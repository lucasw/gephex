#ifndef INCLUDED_LIBGRID_H
#define INCLUDED_LIBGRID_H

/************************************************************************/
/*  Library to provide functionality for modules to interpolate over	*/
/*  a given grid on a texture (or whatever).          			*/
/************************************************************************/


#define LIBGRID_GRIDSIZE 8

#define LIBGRID_POWER_OF_2 0x01
#define LIBGRID_USE_Z	   0x02

#include "basic_types.h"

typedef struct TexturePoint_
{
	int u;
	int v;
	int z;
} TexturePoint;

typedef struct Grid_
{
	int x_size;
	int y_size;
	TexturePoint* points;

	uint_32* texture;
	uint_32* dst;

	int xsize_texture;	
	unsigned int flags;	
	
	int xsize_dst;
	int ysize_dst;
        void (*int_func)(struct Grid_*, int, int);
} Grid;


/**
 * Initializes a grid structure. grid must point to an existing struct.
 * If flags has LIBGRID_USE_POWER_OF_2 set, xsize_texture is assumed to be
 * the log_2 of the true texture size.
 * For example, a value of 8 would mean that the texture is 256x256
 * The parameter use_z_value controls, wether interpolate shades
 * according to the z -values of the texture-points.
 */
void grid_init(Grid* grid, int xsize_texture, int xsize_dst, int ysize_dst,
			  uint_32* texture, uint_32* dst, unsigned int flags);

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
						 uint_32* texture, unsigned int flags);

/**
 * Call if the dst framebuffer has changed.
 */
void grid_change_dst(Grid* grid, int xsize_dst, int ysize_dst, uint_32* dst);


/**
 * Interpolates the block at (x,y) in the grid coordinate system.
 */
void grid_interpolate_block(Grid* grid, int x, int y);

/**
 * Interpolates the whole grid.
 */
void grid_interpolate(Grid* grid);

#endif
