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

#include "mirrormodule.h"

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

	// Add your initialization here

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
  
	int xsize, ysize, xysize, i, j, k;
	unsigned char *src, *dst;
	int lrrl, tbbt, both;
	int omode;

  	FrameBufferAttributes attribs;
	framebuffer_getAttributes(inst->in_1, &attribs);
	framebuffer_changeAttributes(inst->out_r, &attribs);

	xsize = inst->in_1->xsize;
	ysize = inst->in_1->ysize;
	xysize = xsize * ysize;

	src = (unsigned char*)(inst->in_1->framebuffer + xysize-1);
	dst = (unsigned char*)(inst->out_r->framebuffer + xysize-1);

	omode = trim_int(inst->in_mode->number, 0, 3);

	if( omode == 0 )
	{

		for( i=xysize-1; i>=0; --i )
		{

			*dst=*src;
			*(dst+1)=*(src+1);
			*(dst+2)=*(src+2);
	
			dst-=4;
			src-=4;
	
		}

	}
	else
	{

		both = lrrl = tbbt = 0;
	
	
		if( omode == 1 || omode == 3 )
		{
	
			lrrl = trim_int(inst->in_lrrl->number, 1, 2);
	
		}
	
		if( omode == 2 || omode == 3 )
		{
	
			tbbt = trim_int(inst->in_tbbt->number, 1, 2);
	
		}
	
		if( omode == 3 )
		{
	
			both = 1;
	
		}
	
	
		if( lrrl == 1 )
		{
	
			k=0;
			j=xsize-1;
	
			for( i=xysize-1; i>=0; --i )
			{
				
		
				if( (j+1) > (0.5*xsize) )
				{
	
					k=0;
	
				}
				else
				{
	
					*dst=*src;
					*(dst+1)=*(src+1);
					*(dst+2)=*(src+2);
					*(dst+(k*8))=*src;
					*(dst+(k*8)+1)=*(src+1);
					*(dst+(k*8)+2)=*(src+2);
					k++;
	
				}
		
				--j;
		
				if( j < 0 )
				{
	
					j = xsize-1;
	
				}
		
				dst-=4;
				src-=4;
		
			}
	
	
		}
		
		if( lrrl == 2 )
		{
	
			k=xsize-1;
			j=xsize-1;
	
			for( i=xysize-1; i>=0; --i )
			{
				
		
				if( (j+1) > (0.5*xsize) )
				{
	
					*dst=*src;
					*(dst+1)=*(src+1);
					*(dst+2)=*(src+2);
					*(dst-(k*4))=*src;
					*(dst-(k*4)+1)=*(src+1);
					*(dst-(k*4)+2)=*(src+2);
					k-=2;
	
		
				}
				else
				{
	
					k=xsize-1;
				
				}
		
				--j;
		
				if( j < 0 )
				{
					j = xsize-1;
				}
		
				dst-=4;
				src-=4;
		
			}
	
		}
	
		if( tbbt == 1 )
		{
	
			j=xsize-1;
	
			if( both )
			{
	
				dst += (xysize-1)*4;
	
				k=0;
		
				for(i=xysize-1; i>=0; --i)
				{
		
		
					if( i > ( xysize / 2 ) - 1 )
					{
		
		
					}
					else
					{
		
						*dst = *dst;
						*(dst+1)=*(dst+1);
						*(dst+2)=*(dst+2);
						*(dst+(k*xsize*8))=*dst;
						*(dst+(k*xsize*8)+1)=*(dst+1);
						*(dst+(k*xsize*8)+2)=*(dst+2);
		
						j--;
		
						if( j < 0 )
						{
							j = xsize-1;
							k++;
						}
		
					}
		
					dst-=4;
		
				}
	
			}
			else
			{
	
				k=0;
		
				for(i=xysize-1; i>=0; --i)
				{
		
		
					if( i > ( xysize / 2 ) - 1 )
					{
		
		
					}
					else
					{
		
						*dst = *src;
						*(dst+1)=*(src+1);
						*(dst+2)=*(src+2);
						*(dst+(k*xsize*8))=*src;
						*(dst+(k*xsize*8)+1)=*(src+1);
						*(dst+(k*xsize*8)+2)=*(src+2);
		
						j--;
		
						if( j < 0 )
						{
							j = xsize-1;
							k++;
						}
		
					}
		
					dst-=4;
					src-=4;
		
				}
	
			}
	
		}
	
		if( tbbt == 2 )
		{
	
			j=xsize-1;
	
			if( both )
			{
	
				dst += (xysize-1)*4;
	
				k=ysize-1;
		
				for(i=xysize-1; i>=0; --i)
				{
		
		
					if( i > ( xysize / 2 ) - 1 )
					{
		
						*dst = *dst;
						*(dst+1)=*(dst+1);
						*(dst+2)=*(dst+2);
						*(dst-(k*xsize*4))=*dst;
						*(dst-(k*xsize*4)+1)=*(dst+1);
						*(dst-(k*xsize*4)+2)=*(dst+2);
		
						j--;
		
						if( j < 0 )
						{
							j = xsize-1;
							k-=2;
						}
		
					}
					else
					{
		
					}
		
					dst-=4;
		
				}
	
			}
			else
			{
	
				k=ysize-1;
		
				for(i=xysize-1; i>=0; --i)
				{
		
		
					if( i > ( xysize / 2 ) - 1 )
					{
		
						*dst = *src;
						*(dst+1)=*(src+1);
						*(dst+2)=*(src+2);
						*(dst-(k*xsize*4))=*src;
						*(dst-(k*xsize*4)+1)=*(src+1);
						*(dst-(k*xsize*4)+2)=*(src+2);
		
						j--;
		
						if( j < 0 )
						{
							j = xsize-1;
							k-=2;
						}
		
					}
					else
					{
		
					}
		
					dst-=4;
					src-=4;
		
				}
	
			}
	
		}

	}

}

