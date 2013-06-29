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

#include "starfield.h"
#include <limits.h>

#include "config.h"

#define MAX_STARS 1280

int screenDist = 256;
int numStars = 0;
int zPos = 500;
int randArray[MAX_STARS];

typedef struct Star_
{
	int xPos;
	int yPos;
	int zPos;
	char alive;
}Star;

typedef struct _MyInstance {
	Star stars[MAX_STARS];	
} MyInstance, *MyInstancePtr;

void setUpRandomNumbers(int randArray[MAX_STARS])
{
	int index, i, j, swnum1, tmp;	
     
	i=10;
    for(index=0; index<MAX_STARS/2; index++)
	{	
        randArray[index]=i;
        ++i;
	}
 
    i=-10;
    for(index=MAX_STARS/2; index<MAX_STARS; index++)
	{	
        randArray[index]=i;
        --i;
	}

	//swap the thing a little
    for(j = 1; j<MAX_STARS/5; ++j)
	{
        for(i = 0; i<MAX_STARS; ++i)
		{
            swnum1 = (int)(rand()%MAX_STARS);
            tmp = randArray[swnum1];
			randArray[swnum1] = randArray[i];
			randArray[i] = tmp;
        }
    }
}

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
	MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	int i;
	
	for(i= 0; i<MAX_STARS; ++i) my->stars[i].alive = 0;
	setUpRandomNumbers(randArray);
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
	int i, screenX, screenY, speed, colorModifier;
	unsigned int mainStarColor, colorStar;
	unsigned char r, g, b, currNumStars;
	unsigned char colorBG[8];
	unsigned char* dst = (unsigned char*)inst->out_result->framebuffer;
	int size_ = inst->out_result->xsize*inst->out_result->ysize*4;
	
	
	r = (unsigned char)(inst->in_colorStars->r * 255);
	g = (unsigned char)(inst->in_colorStars->g * 255);
	b = (unsigned char)(inst->in_colorStars->b * 255);
	mainStarColor = (b<<16)|(g<<8)|r;
	speed = (int)((double)inst->in_speed->number/ (double)UINT_MAX * 25.);
	currNumStars = (int)((double)inst->in_currentNumStars->number/(double)UINT_MAX * MAX_STARS);
	
	for(i=0; i<8; i+=4)
	{
		colorBG[i] = (unsigned char)(inst->in_colorBG->r*255);
		colorBG[i+1] = (unsigned char)(inst->in_colorBG->g*255);
		colorBG[i+2] = (unsigned char)(inst->in_colorBG->b*255);
		colorBG[i+3] = 0; //TODO: alpha?
	}
	
#if defined(COMP_VC) && defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
	_asm
	{
		mov edi, dst
			mov eax, size_
			shr eax, 5
			movq mm1, [colorBG]
loop_1:
		movq [edi], mm1
			movq [edi+8], mm1
			movq [edi+16], mm1
			movq [edi+24], mm1
			add edi, 32
			dec eax
			jnz loop_1
			emms
	}	

#else
	{
		int* end = (int*)dst + (size_ >> 2) - 1;
		for (; end >= (int*)dst; --end)
		{
			*end = *((int*)colorBG);
		}
		
	}
#endif
	//done delete bg
	
	if(numStars < currNumStars)
	{
		for(i=0; i< currNumStars; ++i)
		{
			if(my->stars[i].alive == 0)
			{
				my->stars[i].xPos = randArray[(i+MAX_STARS/2)%MAX_STARS]%640;
				my->stars[i].yPos = randArray[i]%480;
				my->stars[i].zPos = 500;
				my->stars[i].alive = 1;
				++numStars;
			}
		}
	}
	
	for(i=0; i< currNumStars; ++i)
	{
		screenX = 320+screenDist * my->stars[i].xPos / my->stars[i].zPos;
		screenY = 240+screenDist * my->stars[i].yPos / my->stars[i].zPos;
		my->stars[i].zPos -= speed;
		if(screenX<0||screenY<0||screenX>=inst->out_result->xsize||screenY>= inst->out_result->ysize|| my->stars[i].zPos <= 0)
		{
			my->stars[i].alive = 0;
			--numStars;
		}
		else
		{
			colorModifier = my->stars[i].zPos/100;	
			if(colorModifier<1) 
				colorModifier = 1;
			colorStar = ((b/colorModifier)<<16)|(g/colorModifier)<<8|(r/colorModifier);
			inst->out_result->framebuffer[screenX+screenY*inst->out_result->xsize] = colorStar;	
			
		}
		
	}
	// Add your effect here!
}

