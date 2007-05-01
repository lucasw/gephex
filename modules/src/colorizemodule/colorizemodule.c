/* This source file is a part of the GePhex Project.

 Copyright (C) 2005

 Lars Siebold <khandha5@gmx.net>
 
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

#include <stdio.h>
#include <math.h>

#include "colorizemodule.h"

static logT s_log;

typedef struct _MyInstance {

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
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
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  return my;
}

void destruct(MyInstance* my)
{

  free(my);
}

void update(void* instance)
{

	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;

	// Add your effect here!
  
	int xsize, ysize; 
	uint_32 *src, *dst;
	int xysize, i;
	uint8_t color_a[4];
	uint8_t color_b[4];
	uint8_t color_c[4];
	uint_32 color;
	double ta, tb, taa, tbb, to, mode;

	src = (int*)inst->in_1->framebuffer;
	xsize = inst->in_1->xsize;
	ysize = inst->in_1->ysize;


	{
	FrameBufferAttributes attr;
	attr.xsize = xsize;
	attr.ysize = ysize;

	framebuffer_changeAttributes(inst->out_r, &attr);
	}

	dst = inst->out_r->framebuffer;

	xysize = xsize * ysize;

	mode = trim_double(inst->in_mode->number, 1, 7);

	to = trim_double(inst->in_tolerance->number, 0, 1);
	ta = to;
	taa = 0.5 * to;
	tb = 1 - to;
	tbb = 1 - 0.5 * to;


	color_a[0] = color_comp_to_byte(inst->in_color->b);
	color_a[1] = color_comp_to_byte(inst->in_color->g);
	color_a[2] = color_comp_to_byte(inst->in_color->r);
	color_a[3] = 0;


	if(mode == 1)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Average
			color_c[0] = ta * ((color_b[0] + color_a[0]) / 2 );
			color_c[1] = ta * ((color_b[1] + color_a[1]) / 2 );
			color_c[2] = ta * ((color_b[2] + color_a[2]) / 2 );
			color_c[3] = ta * ((color_b[3] + color_a[3]) / 2 );
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 2)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Additive
			color_c[0] = (tbb * color_b[0] + taa * color_a[0]);
			color_c[1] = (tbb * color_b[1] + taa * color_a[1]);
			color_c[2] = (tbb * color_b[2] + taa * color_a[2]);
			color_c[3] = (tbb * color_b[3] + taa * color_a[3]);
	
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 3)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Subtractive
			color_c[0] = (taa * color_a[0] - tbb * color_b[0]);
			color_c[1] = (taa * color_a[1] - tbb * color_b[1]);
			color_c[2] = (taa * color_a[2] - tbb * color_b[2]);
			color_c[3] = (taa * color_a[3] - tbb * color_b[3]);
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 4)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Subtractive 2
			color_c[0] = (tbb * color_b[0] - taa * color_a[0]);
			color_c[1] = (tbb * color_b[1] - taa * color_a[1]);
			color_c[2] = (tbb * color_b[2] - taa * color_a[2]);
			color_c[3] = (tbb * color_b[3] - taa * color_a[3]);
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 5)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Multiplication
			if( taa < 0.1 )
			{
				taa = 0.1;
			}
			
			color_c[0] = 0.125 * (((taa * color_a[0]) * (tbb * color_b[0])) / 2);
			color_c[1] = 0.125 * (((taa * color_a[1]) * (tbb * color_b[1])) / 2);
			color_c[2] = 0.125 * (((taa * color_a[2]) * (tbb * color_b[2])) / 2);
			color_c[3] = 0.125 * (((taa * color_a[3]) * (tbb * color_b[3])) / 2);
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 6)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Division
			if( color_b[0] != 0 && tbb != 0 )
			{
				color_c[0] = ((taa * color_a[0]) / (tbb * color_b[0]));
			}
			else
			{
				color_c[0] = 0;
			}

			if( color_b[1] != 0 && tbb != 0 )
			{
				color_c[1] = ((taa * color_a[1]) / (tbb * color_b[1]));
			}
			else
			{
				color_c[1] = 0;
			}

			if( color_b[2] != 0 && tbb != 0 )
			{
				color_c[2] = ((taa * color_a[2]) / (tbb * color_b[2]));
			}
			else
			{
				color_c[2] = 0;
			}

			if( color_b[3] != 0 && tbb != 0 )
			{
				color_c[3] = ((taa * color_a[3]) / (tbb * color_b[3]));
			}
			else
			{
				color_c[3] = 0;
			}
	
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else if(mode == 7)
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			// Division 2
			if( taa < 0.1 )
			{
				taa = 0.1;
			}

			if( color_b[0] != 0 && taa != 0 )
			{
				color_c[0] = ((tbb * color_a[0]) / (taa * color_b[0]));
			}
			else
			{
				color_c[0] = 0;
			}

			if( color_b[1] != 0 && taa != 0 )
			{
				color_c[1] = ((tbb * color_a[1]) / (taa * color_b[1]));
			}
			else
			{
				color_c[1] = 0;
			}

			if( color_b[2] != 0 && taa != 0 )
			{
				color_c[2] = ((tbb * color_a[2]) / (taa * color_b[2]));
			}
			else
			{
				color_c[2] = 0;
			}

			if( color_b[3] != 0 && taa != 0 )
			{
				color_c[3] = ((tbb * color_a[3]) / (taa * color_b[3]));
			}
			else
			{
				color_c[3] = 0;
			}
	
	
			color = *((uint_32*) color_c);

			*dst = color;
			++dst;
			++src;

		}

	}
	else
	{

		for(i=xysize; --i;)
		{

			uint8_t* tmpsrc = (uint8_t*)src;

			color_b[0] = tmpsrc[0];
			color_b[1] = tmpsrc[1];
			color_b[2] = tmpsrc[2];
			color_b[3] = tmpsrc[3];

			color = *((uint_32*) color_b);

			*dst = color;
			++dst;
			++src;

		}

	}

}

