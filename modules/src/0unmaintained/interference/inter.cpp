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

extern "C" 
{
	#include "dllmodule.h"
	#include "framebuffertype.h"
	#include "numbertype.h"
}

#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <limits.h>

#include "inter.xpm"

static const char* SPEC = 
"mod_spec { name=mod_interModule; number_of_inputs=2; number_of_outputs=1; "
"deterministic=true; }";
static const char* INPUT_SPECS[] = 
{ "input_spec { type=typ_number; const=true; strong_dependency=true; }",  
  "input_spec { type=typ_number; const=true; strong_dependency=true; }" };
static const char* OUTPUT_SPECS[] = { "output_spec { type=typ_framebuffer; }" };

typedef struct instance_
{
  FrameBufferType result;
  NumberType* input_x;
  NumberType* input_y;
} Instance, *InstancePtr;

int init(logT)
{
  return 1;
}

char *bm1;
char *bm2;
char *far1[256];
char *far2[256];
char warp[256];

void*  newInstance(void)
{
  InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));
  inst->result.xsize = 640;
  inst->result.ysize = 480;
  inst->result.framebuffer = (int*) malloc(sizeof(int) * 640*480);

	int s = 15, i, j;

	bm1 = new char[0x1280*960];
	bm2 = new char[0x1280*960];

	char *tmp1 = bm1; char *tmp2 = bm2;

	for(j=-479; j<481; j++)
	{
		for(i=-639; i<641; i++)
		{
			long dist=i*i+j*j;
			float sqr=sqrt(dist);
			*(tmp1++)=*(tmp2++)=((int)(sqr/(float)s)%2)?0x0:0x1;
		}
	}

  return inst;
}

void deleteInstance(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

	free(bm1); free(bm2);

  free(inst->result.framebuffer);
  free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{	
  InstancePtr inst = (InstancePtr) instance;	
	
	switch(index)
	{
		case 0:
		  inst->input_x = (NumberType*) typePointer;
			break;
		case 1:
		  inst->input_y = (NumberType*) typePointer;
			break;
	}

  // inst->input = (FrameBufferType*) typePointer;

  return 0;
}

void * getOutput (void* instance,int index)
{
  InstancePtr inst = (InstancePtr) instance;
  return &(inst->result);
}

// ---------------------------------------------------------------------------
// Main Part
// ---------------------------------------------------------------------------


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  int* dst = inst->result.framebuffer;

	char *tmp1 = bm1; char *tmp2 = bm2;

	int x = (inst->input_x->number / (double)UINT_MAX) * 640 - 320;
	int y = (inst->input_y->number / (double)UINT_MAX) * 480 - 240;
	
	for(int j=240;j<720;j++)
		for(int i=320;i<960;i++)
		{
			char a = tmp1[j*1280+i];
			char b = tmp2[(j+y)*1280+(i+x)];
			*dst++ = (a&&b)?0xFF:0x00; //(a&&b)?0xFF:0x00;
		} 
}

const char* getInputSpec (int index)
{
  return INPUT_SPECS[index];
}
	
const char* getOutputSpec (int index)
{
  return OUTPUT_SPECS[index];
}

const char* getSpec(void)
{
  return SPEC;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Interference group=Grafikeffekte inputs=[2 Number] outputs=[1 Bild] type=xpm }";
  char* tmpBuf;
  int reqLen = strlen(INFO) + 1 + getSizeOfXPM(inter_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(inter_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO)+1;
      for (i = 0; i < lines; ++i)
	  {
		  char* source = inter_xpm[i];
		  memcpy(offset,source,strlen(source)+1);
		  offset += strlen(source) + 1;
	  }			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
  }
  return reqLen;
}
