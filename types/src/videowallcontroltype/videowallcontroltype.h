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

#ifndef __INCLUDED_VIDEO_WALL_CONTROL_TYPE_H__
#define __INCLUDED_VIDEO_WALL_CONTROL_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_MONITORS 6

//Monitor
typedef struct monitor_
{
	unsigned char r,g,b;
	int showsPic; //true, if this monitor is supposed to just display the input signal
} Monitor;

// Zahl von 0 bis (2^32)-1
typedef struct VideoWallControlType_
{
	Monitor monitors[NUM_MONITORS][NUM_MONITORS]; //6x6 Monitors
} VideoWallControlType;

static __inline void videowallcontrol_initInstance(VideoWallControlType* newType)
{
	int i, j;
	for(i=0;i<NUM_MONITORS;++i)
	{
		for(j=0;j<NUM_MONITORS;++j)
		{
			newType->monitors[i][j].r = 0;
			newType->monitors[i][j].b = 0;
			newType->monitors[i][j].g = 0;
			newType->monitors[i][j].showsPic = 0; //show input signal at start..TODO
		}
	}
}

static __inline VideoWallControlType* videowallcontrol_newInstance(void)
{
	VideoWallControlType* newType = (VideoWallControlType*) malloc(sizeof(VideoWallControlType));
	videowallcontrol_initInstance(newType);
	return newType;
}
static __inline void videowallcontrol_assign(VideoWallControlType* dst,const VideoWallControlType* src)
{
	memcpy(&dst->monitors, &src->monitors, sizeof(Monitor)*NUM_MONITORS);
}

static __inline void videowallcontrol_deleteInstance(VideoWallControlType* vwc)
{
	free(vwc);
}

static __inline int videowallcontrol_serialize(VideoWallControlType* videowallcontrol, char* buffer, int bufferLen)
{
/*	if (bufferLen<14||buffer==0)
	{
		return 14;
	}
	else
	{
		sprintf(buffer,"%u",videowallcontrol->videowallcontrol);
		return strlen(buffer)+1;
	}*/
	// Let's say for now we juist print the vals from left to right and top to bottom
	// that makes uhm... 36*(2*3+4)+1(showpic should only be 0 or 1, r,g,b>=0<=63) +1 for 0   TODO
	int x, y, base=0;
	//this is bullshit, has to be computed again
	if(bufferLen>=361 || buffer != 0)
	{
		for(x=0; x<NUM_MONITORS; ++x)
		{
			for(y=0; y<NUM_MONITORS; ++y)
			{
				if(videowallcontrol->monitors[x][y].showsPic == 1)
				{
					sprintf(buffer+base, "src %d %d ", x, y);
					base+=8;
				}
				else
				{
					sprintf(buffer+base, "color %d %d %u %u %u ", x, y, videowallcontrol->monitors[x][y].r, videowallcontrol->monitors[x][y].b, videowallcontrol->monitors[x][y].g);
					
					base+=16;
					if(videowallcontrol->monitors[x][y].r>=10) ++base;
					if(videowallcontrol->monitors[x][y].g>=10) ++base;
					if(videowallcontrol->monitors[x][y].b>=10) ++base;

				}
			}
		}
		return strlen(buffer)+1;
	}
	return 361;

}

static __inline void videowallcontrol_deSerialize(const char* buffer,int len, VideoWallControlType* videowallcontrol)
{
	int x = 0,y = 0,  base = 0;
	unsigned char r = 0, g = 0, b = 0;
	if (buffer[0] == 0)
	{
		videowallcontrol_initInstance(videowallcontrol);
	}
	else
	{
		char* command = (char*)malloc(7);
		sscanf(buffer, "%s", command);
		if(strcmp(command, "color")==0)
		{
			base+=6;
			sscanf(buffer+base,"%u %u %u ", r,g,b);
			base+=6;
			if(r>=10) ++base;
			if(g>=10) ++base;
			if(b>=10) ++base;

			for(;base<len; base+=4)
			{
				sscanf(buffer+base, "%d %d ", x, y);
				videowallcontrol->monitors[x][y].r = r;
				videowallcontrol->monitors[x][y].g = g;
				videowallcontrol->monitors[x][y].b = b;
			}
		
		}
		else if(strcmp(command, "src")==0)
		{
			base+=4;
			for(;base<len; base+=4)
			{
				sscanf(buffer+base, "%d %d ", x, y);
				videowallcontrol->monitors[x][y].showsPic = 1;
			}

		}
				
		
		/*for(x=0; x<NUM_MONITORS; ++x)
		{
			for(y=0; y<NUM_MONITORS; ++y)
			{
		
				sscanf(buffer+base, "%s", command);
				if(strcmp(command, "color")==0)
				{

				}
				else if(strcmp(command, "src")==0)
				{

				}
				sscanf(buffer+base, "%u %u %u %u ", &videowallcontrol->monitors[i].r, &videowallcontrol->monitors[i].g,
					&videowallcontrol->monitors[i].b, &videowallcontrol->monitors[i].showsPic);
				base+=10;
			}
		}*/
		free(command);
	}
}

#endif
