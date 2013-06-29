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
#include <limits.h>

#include "hsv.xpm"

#define UNDEFINED 0x7E7E7E7E

static const char* SPEC = 
"mod_spec { name=mod_hsvModule; number_of_inputs=4; number_of_outputs=1; "
"deterministic=true; }";
static const char* INPUT_SPECS[] = 
{ 
	"input_spec { type=typ_number; const=true; strong_dependency=true; }", 
	"input_spec { type=typ_number; const=true; strong_dependency=true; }", 
	"input_spec { type=typ_number; const=true; strong_dependency=true; }", 
	"input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }" 
};
static const char* OUTPUT_SPECS[] = { "output_spec { type=typ_framebuffer; }" };

void RGB_to_HSV(unsigned char  r, unsigned char  g, unsigned char  b, double &h, double &s, double &v) {
  /* Given: r, g, b in (byte)
	 * Desired: h in [0;360], s and v in [0;1]
   */
  double rd, gd, bd;
  rd = r * (1.0 / 255.0); 
	gd = g * (1.0 / 255.0); 
	bd = b * (1.0 / 255.0);
	double marg = (rd>gd)?rd:gd; 
	double mirg = (rd<gd)?rd:gd;
	double max = (marg>bd)?marg:bd; 
	double min = (mirg<bd)?mirg:bd;

	v = max; 
	s = (max!=0.0)?((max-min)/max):0.0;

	if(s==0.0) 
		h = 0.0; // UNDEFINED;
	else 
	{ 
		double delta = max - min;

		if(rd==max)
			h = (gd-bd) / delta;
		else if(gd==max)
			h = 2.0 + (bd-rd) / delta;
		else if(bd==max)
			h = 4.0 + (rd-gd) / delta;
			
		h *= 60.0;

		if(h<0.0)
			h+=360.0;
	}
}

void HSV_to_RGB(unsigned char &r, unsigned char  &g, unsigned char  &b, double h, double s, double v)
{
	/* Given: h in [0;360], s, v in [0;1]
	 * Desired: r, g, b in [0;1]
	 */

	if(s==0.0) 
	{
		if(h==UNDEFINED) 
		{
			r= (unsigned char) (v*256.0);
			g= (unsigned char) (v*256.0);
			b= (unsigned char) (v*256.0);
		}
	}
	else 
	{
		double f, p, q, t;
		int i;

		while(h>=360.0)
			h-=360.0;

		h/=60.0;
		i = (int)(h);
		f = h - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch(i) 
		{
			case 0:
				r = (unsigned char)(v*255.0); g = (unsigned char)(t*255.0); b = (unsigned char)(p*255.0);
			break;
			case 1:
				r = (unsigned char)(q*255.0); g = (unsigned char)(v*255.0); b = (unsigned char)(p*255.0);
			break;
			case 2:
				r = (unsigned char)(p*255.0); g = (unsigned char)(v*255.0); b = (unsigned char)(t*255.0);
			break;
			case 3:
				r = (unsigned char)(p*255.0); g = (unsigned char)(q*255.0); b = (unsigned char)(v*255.0);
			break;
			case 4:
				r = (unsigned char)(t*255.0); g = (unsigned char)(p*255.0); b = (unsigned char)(v*255.0);
			break;
			case 5:
				r = (unsigned char)(v*255.0); g = (unsigned char)(p*255.0); b = (unsigned char)(q*255.0);
			break;
		}
	}
}

typedef struct instance_
{
  FrameBufferType result;
  FrameBufferType* input;
  NumberType* h_value;
	NumberType* s_value;
	NumberType* v_value;
} Instance, *InstancePtr;

int init(logT)
{
  return 1;
}

void*  newInstance(void)
{
  InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));
  inst->result.xsize = 640;
  inst->result.ysize = 480;
  inst->result.framebuffer = (int*) malloc(sizeof(int) * 640*480);

  return inst;
}

void deleteInstance(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  free(inst->result.framebuffer);
  free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{	
  InstancePtr inst = (InstancePtr) instance;	

	switch(index)
	{
	case 0:
  	inst->h_value = (NumberType*) typePointer;
		break;
	case 1:
  	inst->s_value = (NumberType*) typePointer;
		break;
	case 2:
  	inst->v_value = (NumberType*) typePointer;
		break;
	case 3:
  	inst->input = (FrameBufferType*) typePointer;
		break;
	}

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

  int xsize, ysize; 
	int *src, *dst;

  src = (int*)inst->input->framebuffer;
  xsize = inst->result.xsize;
  ysize = inst->result.ysize;
  dst = inst->result.framebuffer;

	int xysize = xsize * ysize;

  double h_, s_, v_;
	unsigned char r, g, b;
	for(int i=xysize; i--;)
	{
		unsigned char *tmpc = (unsigned char*)src;
		r = tmpc[2]; g = tmpc[1]; b = tmpc[0];
		RGB_to_HSV(r, g, b, h_, s_, v_);
	
		float hv = ((inst->h_value->number)/((float)(UINT_MAX)))*360;
		float sv = (inst->s_value->number)/((float)(UINT_MAX));
		float vv = (inst->v_value->number)/((float)(UINT_MAX));

		h_+=hv;
		s_+=sv;
		v_+=vv;

		// printf("hsv: %f, %f, %f\n", h_, s_, v_);
		// printf("slider hsv: %f, %f, %f\n", hv, sv, vv);

		HSV_to_RGB(r, g, b, h_, s_, v_);
		*dst = (r << 16) | (g << 8) | b;
		dst++; src++;
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
  static const char* INFO = "info { name=HSV group=Grafikeffekte inputs=[4 Zahl Zahl Zahl Bild] outputs=[1 Bild] type=xpm}";
  char* tmpBuf;
  int reqLen = strlen(INFO) + 1 + getSizeOfXPM(hsv_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(hsv_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO)+1;
      for (i = 0; i < lines; ++i)
	  {
		  char* source = hsv_xpm[i];
		  memcpy(offset,source,strlen(source)+1);
		  offset += strlen(source) + 1;
	  }			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
  }
  return reqLen;
}
