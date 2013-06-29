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
}

#include <stdlib.h>
#include <string.h>

#include "split.xpm"

static const char* SPEC = 
"mod_spec { name=mod_splitModule; number_of_inputs=1; number_of_outputs=3; "
"deterministic=true; }";
static const char* INPUT_SPECS[] = 
{ 
	"input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }" 
};
static const char* OUTPUT_SPECS[] = 
{ 
	"output_spec { type=typ_framebuffer; }", 
	"output_spec { type=typ_framebuffer; }", 
	"output_spec { type=typ_framebuffer; }" 
};

typedef struct instance_
{
  FrameBufferType result_r;
  FrameBufferType result_g;
  FrameBufferType result_b;
  FrameBufferType* input;
} Instance, *InstancePtr;

int init(logT)
{
  return 1;
}

void*  newInstance(void)
{
  InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));

  inst->result_r.xsize = 640; inst->result_r.ysize = 480;
  inst->result_g.xsize = 640; inst->result_g.ysize = 480;
  inst->result_b.xsize = 640; inst->result_b.ysize = 480;
  inst->result_r.framebuffer = (int*) malloc(sizeof(int) * 640*480);
  inst->result_g.framebuffer = (int*) malloc(sizeof(int) * 640*480);
  inst->result_b.framebuffer = (int*) malloc(sizeof(int) * 640*480);

  return inst;
}

void deleteInstance(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  free(inst->result_r.framebuffer);
  free(inst->result_g.framebuffer);
  free(inst->result_b.framebuffer);
  free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{	
  InstancePtr inst = (InstancePtr) instance;	

  inst->input = (FrameBufferType*) typePointer;

  return 0;
}

void * getOutput (void* instance,int index)
{
  InstancePtr inst = (InstancePtr) instance;
	switch(index)
	{
		case 0:
		  return &(inst->result_r);
		break;
		case 1:
		  return &(inst->result_g);
		break;
		case 2:
		  return &(inst->result_b);
		break;
		default:
			return 0;
		break;
	}
}

// ---------------------------------------------------------------------------
// Main Part
// ---------------------------------------------------------------------------


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  int xsize, ysize; 
	int *src, *dstr, *dstg, *dstb;

  src = (int*)inst->input->framebuffer;
  xsize = 640;
  ysize = 480;

  dstr = inst->result_r.framebuffer;
  dstg = inst->result_g.framebuffer;
  dstb = inst->result_b.framebuffer;

	int xysize = xsize * ysize;

	for(int i=xysize; i--;)
	{
		char* tmpc = (char*)src;
		*dstr = (tmpc[2] << 16) | (tmpc[2] << 8) | tmpc[2];
		*dstg = (tmpc[1] << 16) | (tmpc[1] << 8) | tmpc[1];
		*dstb = (tmpc[0] << 16) | (tmpc[0] << 8) | tmpc[0];
		dstr++; 
		dstg++; 
		dstb++; 
		src++;
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
  static const char* INFO = "info { name=RGBSplit group=Filter inputs=[1 Bild] outputs=[3 Bild Bild Bild] type=xpm }";
  char* tmpBuf;
  int reqLen = strlen(INFO) + 1 + getSizeOfXPM(split_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(split_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO)+1;
      for (i = 0; i < lines; ++i)
	  {
		  char* source = split_xpm[i];
		  memcpy(offset,source,strlen(source)+1);
		  offset += strlen(source) + 1;
	  }			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
  }
  return reqLen;
}
