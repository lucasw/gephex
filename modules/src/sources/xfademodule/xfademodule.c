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

#include "xfademodule.h"

#include <math.h>
#include <limits.h>
#include <assert.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
#include "cpuinfo.h"
static int s_mmx_supported = 0;
static int s_e3dnow_supported = 0;
#endif

static const double EPS = 0.00001;

static logT s_log;

typedef void (*fadeT)(uint_32 size, uint_8* framebuf1,
		      uint_8* framebuf2, uint_8* result,
		      int fadeValue);

static void fade(uint_32 size, uint_8* framebuf1,
		 uint_8* framebuf2, uint_8* result,
		 int fadeValue);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
extern void fade_mmx(uint_32 size, uint_8* framebuf1,
		     uint_8* framebuf2, uint_8* result,
		     int fadeValue);

extern void fade_e3dnow(uint_32 size, uint_8* framebuf1,
                        uint_8* framebuf2, uint_8* result,
                        int fadeValue);
#endif

typedef struct _MyInstance {

  // scaledFb is allocated lazily only when scaling is needed.
  // As soon as scaling is not performed anymore, it is freed.
  // So if scaling is constantly needed, there is no overhead
  // with allocating memory for scaledFb, and if no scaling is needed
  // there is no memory overhead.
  FrameBufferType* scaledFb;

  fadeT fade;

  StringType oldRoutine;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    {
      s_mmx_supported    = cpuinfo_has_mmx();
      s_e3dnow_supported = cpuinfo_has_e3dnow();
    }
  else
    {
      s_mmx_supported    = 0;
      s_e3dnow_supported = 0;
    }

  if (s_mmx_supported)
    s_log(2, "found mmx support");
  else
    s_log(2, "no mmx support");

  if (s_e3dnow_supported)
    s_log(2, "found e3dnow support");
  else
    s_log(2, "no e3dnow support");
#endif

  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->scaledFb = 0;
  my->fade = 0;

  string_initInstance(&my->oldRoutine);

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFb != 0)
    framebuffer_deleteInstance(my->scaledFb);

  string_destroyInstance(&my->oldRoutine);
  free(my);
}

static void fade(uint_32 size, uint_8* framebuf1,
		 uint_8* framebuf2, uint_8* result,
		 int fadeValue)
{	
  uint_8* end = result + size*4;
  int negfadeValue = 255 - fadeValue;
		
  while (result != end)
    {
      *result = (*framebuf2*fadeValue + *framebuf1*negfadeValue)>>8;
		  
      ++framebuf1;
      ++framebuf2;
      ++result;
      *result = (*framebuf2*fadeValue + *framebuf1*negfadeValue)>>8;
		  
      ++framebuf1;
      ++framebuf2;
      ++result;
      *result = (*framebuf2*fadeValue + *framebuf1*negfadeValue)>>8;
		  
      framebuf1 += 2;
      framebuf2 += 2;
      result += 2;
    }
}


/**
 * Takes two framebuffertypes and scales them if they differ in size.
 * postcondition:
 *   *fb1 and *fb2 are arrays of the same size
 */
void scale_framebuffers(const FrameBufferType* f1,const FrameBufferType* f2,
			FrameBufferType** scaled, uint_32** fb1, uint_32** fb2,
			int* xsize, int* ysize, int* did_scale)
{
	if (f1->xsize != f2->xsize
	  || f1->ysize != f2->ysize)
	{
	  if (*scaled == 0)
	    *scaled = framebuffer_newInstance();

	  // indicate that we did scale this time
	  *did_scale = 1;

	  // scale the smaller input to the size of the other one
	  if (f1->xsize * f1->ysize >
	      f2->xsize * f2->ysize)
	    {
	      *fb1   = f1->framebuffer;		  
	      *xsize = f1->xsize;
	      *ysize = f1->ysize;

	      framebuffer_scale(*scaled, f2, *xsize, *ysize);
	      *fb2 = (*scaled)->framebuffer;
	    }
	  else
	    {
	      *fb2  = f2->framebuffer;
	      *xsize = f2->xsize;
	      *ysize = f2->ysize;

	      framebuffer_scale(*scaled,f1, *xsize, *ysize);
	      *fb1 = (*scaled)->framebuffer;
	    }
	}
      else
	{
	  // both inputs have the same size
	  *did_scale = 0;
	  *fb1 = f1->framebuffer;
	  *fb2 = f2->framebuffer;
	  *xsize = f1->xsize;
	  *ysize = f1->ysize;		  
	}
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  double number = trim_double(inst->in_x->number, 0, 1);

  if (strcmp(my->oldRoutine.text, inst->in_routine->text) != 0)
    {
      string_assign(&my->oldRoutine, inst->in_routine);

      if (strcmp(my->oldRoutine.text, "regular") == 0)
	{
	  s_log(2, "Using regular fading");
	  my->fade = fade;
	}
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
      else if (strcmp(my->oldRoutine.text, "mmx") == 0)
    {
      if (s_e3dnow_supported)
	{
	  s_log(2, "Using e3dnow fading");
	  my->fade = fade_e3dnow;
	}
      else if (s_mmx_supported)
        {
	  s_log(2, "Using mmx fading");
	  my->fade = fade_mmx;
        }
      else
        {
	  s_log(2, "Using regular fading");
	  my->fade = fade;
        }
    }
#endif
      else
	{
	  char buffer[128];
	  snprintf(buffer, sizeof(buffer),
		   "Unsupported fade routine: '%s', using 'regular' instead",
		   my->oldRoutine.text);

	  s_log(0, buffer);
	  my->fade = fade;
	}
    }

  if (fabs(number) < EPS ||
      fabs(number-1.0) < EPS)
    {
      // no need to do anything here, because the inputs are patched directly
      // to the output.
      return;
    }
  else
    {
      uint_32* fb1 = 0;
      uint_32* fb2 = 0;
      int didScale = 0;

      int xsize = 0, ysize = 0;
      int fadeValue = (int) (number * 255 + .5);

      scale_framebuffers(inst->in_1, inst->in_2,
			 &my->scaledFb, &fb1, &fb2,
			 &xsize, &ysize, &didScale);
      
      // scale output framebuffer to the size of the inputs
      {
	FrameBufferAttributes attribs;
		
	attribs.xsize = xsize;
	attribs.ysize = ysize;
	framebuffer_changeAttributes(inst->out_r, &attribs);
      }

      assert(didScale == 0 || (my->scaledFb->xsize == xsize &&
			       my->scaledFb->ysize == ysize));

      assert(inst->out_r->xsize == xsize && inst->out_r->ysize == ysize);

      my->fade(xsize*ysize, (uint_8*) fb1, (uint_8*) fb2,
	       (uint_8*) inst->out_r->framebuffer,
	       fadeValue);
      
      // delete scaled framebuffer if we didn't need it this time
      if (didScale == 0)
	{
	  if (my->scaledFb != 0)
	    {
	      framebuffer_deleteInstance(my->scaledFb);
	      my->scaledFb = 0;
	    }
	}
    }
  
}

void strongDependencies(Instance* inst, int neededInputs[])
{	
  double number = trim_double(inst->in_x->number, 0, 1);  
  if (fabs(number) < EPS) {
    neededInputs[in_2] = 0;
	//neededInputs[in_routine] = 0;
  }
  else if (fabs(1.0 - number) < EPS){
    neededInputs[in_1] = 0;
	//neededInputs[in_routine] = 0;
  }
}

void patchLayout(Instance* inst, int out2in[])
{
  double number = trim_double(inst->in_x->number, 0, 1);
  if (fabs(number) < EPS)
    out2in[out_r] = in_1;
  else if (fabs(number - 1.0) < EPS)
    out2in[out_r] = in_2;
}
