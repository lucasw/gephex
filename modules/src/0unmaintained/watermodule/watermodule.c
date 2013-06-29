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

#include "watermodule.h"
#include <math.h>
#include <limits.h>

#define DISPLACEMENT_LOOKUP_SIZE 2000
#define DISPLACEMENT_LOOKUP_SIZE_HALF 1000

#define TEX_SIZE 256

const double _double2fixmagic = 68719476736.0*1.5;     //2^36 * 1.5,  (52-_shiftamt=36) uses limited precisicion to floor
const int _shiftamt        = 16;                    //16.16 fixed point representation,


//#define GRID_SIZE 4
//slower with fucking grid
/*typedef struct TexturePoint_
{
  int u;
  int v;
} TexturePoint;
*/
typedef struct _MyInstance {
	char* waterDisplacement;
	int* water1;
	int* water2;
	//pointer to water-table
	int* activeWater;
	int* tmpWater;
	/*int grid_x;
	int grid_y;
	TexturePoint* grid;*/
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

//Create a lookup table
void setupDisplacementTable(char* table, int arraySize, float refractionIndex, float depth)
{
	int i;
	float angle, beamAngle, heightDiff;
	for(i=-arraySize/2; i<arraySize/2; ++i)
	{
		heightDiff = i*depth;
		angle = (float)atan(heightDiff);
		beamAngle = (float)asin(sin(angle)/refractionIndex);
		table[i+arraySize/2]= (int)(tan(beamAngle)*heightDiff);
	}

}

MyInstance* construct()
{
	int xres=TEX_SIZE, yres=TEX_SIZE;
	MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	my->waterDisplacement = (char*) malloc(DISPLACEMENT_LOOKUP_SIZE);
	setupDisplacementTable(my->waterDisplacement, DISPLACEMENT_LOOKUP_SIZE, 1.333f, 2.5f);
	my->water1 = (int*)malloc(xres*yres*sizeof(int));
	my->water2 = (int*)malloc(xres*yres*sizeof(int));
	memset((my->water1), 0, xres*yres*sizeof(int));
	memset((my->water2), 0, xres*yres*sizeof(int));
  // TODO: Add init-code for different kinds of fluids
	my->activeWater = my->water1;
	my->tmpWater = my->water2;

	/*my->grid_x = xres / GRID_SIZE + 1;
	my->grid_y = yres / GRID_SIZE + 1;
	my->grid = malloc(sizeof(TexturePoint) * my->grid_x * my->grid_y);*/

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
	free(my->waterDisplacement);
	free(my->water1);
	free(my->water2);
  free(my);
}

/*__inline*/ int double2int(double val)
{
	val		= val + _double2fixmagic;
	return ((int*)&val)[0] >> _shiftamt; 
}


void createWaterDrop(int x, int y, int size, int splashStrength, int *where, int xsize, int ysize)
{
	int i,j, square_x, square_y, square_size;
	//where += (x-size)+xsize*(y-size);
	
	for (j=y-size; j<= y+size; ++j) {
		for (i=x-size; i <= x+size; ++i) {
		// make sure we're in bounds
		if (i < 0 || i >= xsize || j < 0 || j >= ysize) continue;
      
		// see if the point at (x,y) is within the circle of radius size
		square_x    = (x-i)*(x-i);
		square_y    = (y-j)*(y-j);
		square_size = size*size;

		if (square_x+square_y <= square_size) {
			where[(j*xsize)+i] += double2int((double)splashStrength*sqrt(square_x+square_y));
			//*where += double2int(((double)splashStrength*sqrt(square_x+square_y)));
		}
		//++where;
		}
		//where+=xsize;
	}
}

void proceedWater(int size, const int xsize, int ysize, int* oldWater, int* newWater)

{

	int x,*xminus1, *yminus1, *xplus1, *yplus1;//, *xminus2, *yminus2, *xplus2, *yplus2;

	int value;
	int* oldIndex = oldWater;
	int* newIndex = newWater;
	int _size = size;
	const int _xsize = xsize;
	
	int floatMult = (int) (1.05f*65536.);

	for(x=0; x<xsize; ++x)
	{
		xminus1 = oldIndex-1; if(xminus1 < oldWater) xminus1 = oldWater;
		//xminus2 = oldIndex-2; if(xminus2 < oldWater) xminus2 = oldWater;
		xplus1 = oldIndex+1; 
		//xplus2 = oldIndex+2;
		yminus1 = oldWater;
		//yminus2 = oldIndex; //ahh...not quite right but faster :)
		yplus1 = oldIndex+xsize;
		//yplus2 = yplus1+xsize;

		value = ((*xminus1)+(*xplus1)+(*yminus1)+(*yplus1))/2;//+(*xminus2)+(*xplus2)+(*yminus2)+(*yplus2))/2;
		value -= (*newIndex);
		value = double2int((double)value/1.05f);
		*(newIndex) = value;
		++oldIndex;
		++newIndex;
	}

	//size-= 2*xsize;
		//mov ecx, 293120
	/*_asm
	{
		mov ecx, _size
		mov esi, oldIndex
		mov edi, newIndex
		
		loop_main:
			mov eax, [esi+1]
			mov ebx, [esi+_xsize]
			add eax, ebx
			mov ebx, [esi-640]
			add eax, ebx
			mov ebx, [esi-1]
			add eax, ebx
			shr eax, 1
			sub eax, [esi]
			shl eax, 16
			xor edx, edx
			idiv floatMult
			shr eax, 16

			mov [edi], eax
			inc esi
			inc edi
			dec ecx
		jnz loop_main
		emms

	}*/


		/*xminus1 = oldIndex-1;
	xplus1 = oldIndex+1;
	yminus1 = oldIndex-xsize;
	yplus1 = oldIndex+xsize;*/

	
	for(x = xsize; x<size -xsize; ++x)
	{
		//xminus1 = oldIndex-1;
		//xplus1 = oldIndex+1;
		//yminus1 = oldIndex-xsize;
		//yplus1 = oldIndex+xsize;
		//xminus2 = xminus1-1;
		//xplus2 = xplus1+1;
		//yminus2 = yminus1-xsize;
		//yplus2 = yplus1 +xsize;
			xminus1 = oldIndex-1;
	xplus1 = oldIndex+1;
	yminus1 = oldIndex-xsize;
	yplus1 = oldIndex+xsize;

	
		value = ((*xminus1++)+(*xplus1++)+(*yminus1++)+(*yplus1++))/2;//+(*xminus2)+(*xplus2)+(*yminus2)+(*yplus2))/4;
		value -= (*newIndex);
		value = double2int((double)value/1.05f);
		*(newIndex) = value;
		++oldIndex;
		++newIndex;

	}

	for(x= size-xsize; x<size; ++x)
	{
		xminus1 = oldIndex-1;
		xplus1 = oldIndex+1; if(xplus1 > oldWater+size-1) xplus1 = oldWater+size-1;
		yminus1 = oldIndex-xsize;
		yplus1 = /*oldIndex+xsize; if(yplus1> oldWater+size-1) yplus1 = */oldWater+size-1;
		/*xminus2 = xminus1-1; //uncomment for slower but better looking water
		xplus2 = xplus1+1; if(xplus2 > oldWater+size-1) xplus2 = oldWater+size-1;
		yminus2 = yminus1-xsize; 
		yplus2 = oldIndex;*/ 


		value = ((*xminus1)+(*xplus1)+(*yminus1)+(*yplus1))>>1;/*+(*xminus2)+(*xplus2)+(*yminus2)+(*yplus2)*/
		value -= (*newIndex);
		value = double2int((double)value/1.05f);
		
		*(newIndex) = value;
		++oldIndex;
		++newIndex;

	
	}
}

/*void interpolateBlock(TexturePoint* upper_left, 
			       TexturePoint* lower_left, 
			       TexturePoint* upper_right, 
			       TexturePoint* lower_right,
			       int* src, int* dst, int X_SIZE)
{
  int x, y, u_left, u_right, v_left, v_right;

  int step_start_row_u = 65536. * (lower_left->u - upper_left->u)/((double) GRID_SIZE);
  int step_start_row_v = 65536. * (lower_left->v - upper_left->v)/((double) GRID_SIZE);
  int step_end_row_u = 65536. * (lower_right->u - upper_right->u)/((double) GRID_SIZE);
  int step_end_row_v = 65536. * (lower_right->v - upper_right->v)/((double) GRID_SIZE);
 
  unsigned int start_row_uu = upper_left->u << 16;
  unsigned int start_row_vv = upper_left->v << 16;
  unsigned int end_row_uu = upper_right->u << 16;
  unsigned int end_row_vv = upper_right->v << 16;
  unsigned int u_line_index, v_line_index;
  int step_line_u, step_line_v;

  for(y=0; y < GRID_SIZE; ++y)
    {
      u_left  = start_row_uu >> 16;
      u_right = end_row_uu >> 16;
      v_left = start_row_vv >> 16;
      v_right = end_row_vv >> 16;

      u_line_index = start_row_uu;
      v_line_index = start_row_vv;

      step_line_u = 65536. * (u_right-u_left)/((double) GRID_SIZE);
      step_line_v = 65536. * (v_right-v_left)/((double) GRID_SIZE);

      //neuer step
      for(x=0; x<GRID_SIZE; ++x)
	{
	  u_left = u_line_index >> 16;
	  v_left = v_line_index >> 16;
	  *dst = src[u_left+ v_left*X_SIZE];
	  u_line_index += step_line_u;
	  v_line_index += step_line_v;
	  ++dst;
	}

      start_row_uu += step_start_row_u;
      end_row_uu += step_end_row_u;
      start_row_vv += step_start_row_v;
      end_row_vv += step_end_row_v;

      dst+= (X_SIZE-GRID_SIZE);
    }
}*/

int RandomNumber(int iMin, int iMax)
{
  if (iMin == iMax) return(iMin);
  return((rand() % (abs(iMax-iMin)+1))+iMin);
}

static int count = 0;
static int counter = -1;
void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	int* src;
	int* dst;
	//int* waterbuf = my->activeWater;
	int xsize; 
	int ysize; 
	int	size; 
	int x,y,gridx=0, gridy=0;
	//int dest_index=0;
	int* srcPtr;
	int* waterPtr;
	int* tmp;
	int xdiff, ydiff, xdisp, ydisp;
	int freq = 200-(int)(inst->in_frequency->number/(double)UINT_MAX * 200.)+110 ;
	int splashStrength = (int)(inst->in_splashStrength->number/(double)UINT_MAX * 20.)+5;
	int dropSize = (int)(inst->in_dropSize->number/(double)UINT_MAX * 10.)+5;
	int numDrops = (int)(inst->in_numDrops->number/(double)UINT_MAX * 30.);
	FrameBufferAttributes attribs;
	

	framebuffer_getAttributes(inst->in_src, &attribs);
	if(attribs.xsize!=TEX_SIZE||attribs.ysize!=TEX_SIZE)
	{	
		attribs.xsize = TEX_SIZE;
		attribs.ysize = TEX_SIZE;
		framebuffer_changeAttributes(inst->in_src, &attribs);
	}

	framebuffer_getAttributes(inst->out_result, &attribs);
	if(attribs.xsize!=TEX_SIZE||attribs.ysize!=TEX_SIZE)
	{	
		attribs.xsize = TEX_SIZE;
		attribs.ysize = TEX_SIZE;
		framebuffer_changeAttributes(inst->out_result, &attribs);
	}

	xsize = inst->in_src->xsize;
	ysize = inst->in_src->ysize;
	size = xsize*ysize;
	waterPtr = my->activeWater;
	src = inst->in_src-> framebuffer;
	dst = inst->out_result->framebuffer;

	//TexturePoint* gridptr;
	//gridptr = my->grid;
	

	if(count >= freq || count <= 0)
	{
		for(y=0; y<numDrops; ++y)
			createWaterDrop(RandomNumber(0, xsize-1), RandomNumber(0, ysize-1), dropSize, splashStrength, my->activeWater, xsize, ysize);
		counter = counter*(-1);
	}

	count+=counter;
	
	proceedWater(xsize*ysize, xsize,ysize, my->tmpWater, my->activeWater); 
	
	for (y=0; y < ysize-1; y++) {
		
		for (x=0; x < xsize-1; x++) {
			xdiff = *(waterPtr+1) - *(waterPtr);
			ydiff = *(waterPtr+xsize/2) - *(waterPtr);
			/*if(x%2==0)*/ ++waterPtr;

			xdisp = my->waterDisplacement[(xdiff+DISPLACEMENT_LOOKUP_SIZE_HALF) %DISPLACEMENT_LOOKUP_SIZE];
			ydisp = my->waterDisplacement[(ydiff+DISPLACEMENT_LOOKUP_SIZE_HALF) %DISPLACEMENT_LOOKUP_SIZE];
			
			
			if (xdiff < 0) {
				if (ydiff < 0) {
					srcPtr= src+(y-ydisp)*xsize+x-xdisp;
					if(srcPtr<src||srcPtr>=src+size)
						*dst++ = *src;
					else
						*dst++ = *srcPtr;
				}
				else {
					srcPtr = src+((y+ydisp)*xsize)+x-xdisp;
					if(srcPtr<src||srcPtr>=src+size)
						*dst++ = *src;
					else
						*dst++ = *srcPtr;
				}
			}
			else {
				if (ydiff < 0) {
					srcPtr = src+((y-ydisp)*xsize)+x+xdisp;
					if(srcPtr<src||srcPtr>=src+size)
						*dst++ = *src;
					else
						*dst++ = *srcPtr;
				}
				else {
					srcPtr = src+((y+ydisp)*xsize)+x+xdisp;
					if(srcPtr<src||srcPtr>=src+size)
						*dst++ = *src;
					else
						*dst++ = *srcPtr;
				}
			}
		}//for1
		x++;
		xdiff = 0;
		ydiff = 0;

		xdisp = my->waterDisplacement[DISPLACEMENT_LOOKUP_SIZE_HALF];
		ydisp = my->waterDisplacement[DISPLACEMENT_LOOKUP_SIZE_HALF];
			
		if (y+ydisp < 0 || y+ydisp >= ysize|| x+xdisp < 0 || x+xdisp >= xsize)
			*dst++= src[0];    
		else
			*dst++ = src[((y+ydisp)*xsize)+x+xdisp];  
				
			
		// next line
		//dest_index++ ;
		/*if(y%2==0) waterPtr += xsize/2;//*/++waterPtr;
		//else waterPtr -= xsize/2;
	}
	++y;
	++waterPtr;
	for (x=0; x < xsize-1; x++) {
		
		//int xdiff = (x == xsize-1)  ? 0 : my->activeWater[(y*xsize)+x+1]   - my->activeWater[(y*xsize)+x];
		//int ydiff = (y == ysize-1) ? 0 : my->activeWater[((y+1)*xsize)+x] - my->activeWater[(y*xsize)+x];
		xdiff= *(waterPtr+1)  - *(waterPtr);
		ydiff= 0;
		
		
		xdisp = my->waterDisplacement[(xdiff+DISPLACEMENT_LOOKUP_SIZE_HALF) %DISPLACEMENT_LOOKUP_SIZE];
		ydisp = my->waterDisplacement[(ydiff+DISPLACEMENT_LOOKUP_SIZE_HALF) %DISPLACEMENT_LOOKUP_SIZE];
		
		if (xdiff < 0) {
			
			if (y+ydisp < 0 || y+ydisp >= ysize || x-xdisp < 0 || x-xdisp >= xsize)
				*dst++ = src[0];    
			else
				*dst++ = src[((y+ydisp)*xsize)+x-xdisp];  
			
		}
		else {
			if (y+ydisp < 0 || y+ydisp >= ysize|| x+xdisp < 0 || x+xdisp >= xsize)
				*dst++ = src[0];    
			else
				*dst++ = src[((y+ydisp)*xsize)+x+xdisp];  
			
		}
	}
	x++;
	xdiff = 0;
	ydiff = 0;
	
	xdisp = my->waterDisplacement[(xdiff+DISPLACEMENT_LOOKUP_SIZE_HALF ) ];
	ydisp = my->waterDisplacement[(ydiff+DISPLACEMENT_LOOKUP_SIZE_HALF ) ];
	
	if (y+ydisp < 0 || y+ydisp >= ysize|| x+xdisp < 0 || x+xdisp >= xsize)
		*dst++ = src[0];    
	else
		*dst++ = src[((y+ydisp)*xsize)+x+xdisp];  
	
	
	//swap the waterbuffers so we can work with the new one
	tmp = my->tmpWater;
	my->tmpWater = my->activeWater;
	my->activeWater = tmp;
	
	/*for (y=0; y <= ysize; y+=GRID_SIZE) {
		
		for (x=0; x <= xsize; x+=GRID_SIZE) {
			int u,v;
			int offset = (y*xsize)+x;
			int xdiff = (x == xsize-1||x==xsize)  ? 0 : waterPtr[offset+1]   - waterPtr[offset];
			int ydiff = (y == ysize-1||y==ysize) ? 0 : waterPtr[offset+xsize] - waterPtr[offset];
      
			int xdisp = my->waterDisplacement[(xdiff+DISPLACEMENT_LOOKUP_SIZE_HALF ) % DISPLACEMENT_LOOKUP_SIZE];
			int ydisp = my->waterDisplacement[(ydiff+DISPLACEMENT_LOOKUP_SIZE_HALF ) % DISPLACEMENT_LOOKUP_SIZE];
			if(xdiff<0) 
			{
				if (ydiff < 0) {
					if (y-ydisp < 0 || y-ydisp >= ysize|| x-xdisp < 0 || x-xdisp >= xsize)
					{
						u=x;
						v=y;
					}
					else
					{
						u = x-xdisp;
						v = y-ydisp;
					}
				}
				else {
					if (y+ydisp < 0 || y+ydisp >= ysize|| x-xdisp < 0 || x-xdisp >= xsize)
					{
						u=x;
						v=y;
					}
					else
					{
						v=y+ydisp;
						u=x-xdisp;  
					}
				}
			}
			else {
				if (ydiff < 0) {
					if (y-ydisp < 0 || y-ydisp >= ysize|| x+xdisp < 0 || x+xdisp >= xsize)
					{
						u=x;
						v=y;
					}
					else
					{
						v=y-ydisp;
						u=x+xdisp;
					}
				}
				else {
					if (y+ydisp < 0 || y+ydisp >= ysize|| x+xdisp < 0 || x+xdisp >= xsize)
					{
						u=x;
						v=y;
					}
					else
					{
						v=y+ydisp;
						u=x+xdisp;
					}
				}
			}
			gridptr->u = u;
			gridptr->v = v;
			gridptr++;
			
		}
	}
	gridptr = my->grid;
	for(y=0; y<my->grid_y-1; ++y)
    {
      for(x=0; x<my->grid_x-1; ++x)
	{
	  interpolateBlock(gridptr,
			   gridptr+my->grid_x,
			   gridptr+1,
			   gridptr+1+my->grid_x,
			   src, dst,xsize);
	  dst += GRID_SIZE;
	  ++gridptr;
	}
      ++gridptr;
      dst+=((GRID_SIZE-1)*xsize);
    }*/

}

