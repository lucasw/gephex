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
#endif

static const double EPS = 0.00001;

static logT s_log;

typedef void (*fadeT)(uint_32 size, unsigned char* framebuf1,
		      unsigned char* framebuf2, unsigned char* result,
		      int fadeValue);

static void fade(uint_32 size, unsigned char* framebuf1,
		 unsigned char* framebuf2, unsigned char* result,
		 int fadeValue);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void fade_mmx(uint_32 size, unsigned char* framebuf1,
		     unsigned char* framebuf2, unsigned char* result,
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
      s_log(2, "found mmx support");
      s_mmx_supported = cpuinfo_has_mmx();
    }
  else
    {
      s_log(2, "no mmx support");
      s_mmx_supported = 0;
    }
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

static void fade(uint_32 size, unsigned char* framebuf1,
		 unsigned char* framebuf2, unsigned char* result,
		 int fadeValue)
{	
  unsigned char* end = result + size;
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

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void fade_mmx(uint_32 size,
		     unsigned char* framebuf1,
		     unsigned char* framebuf2,
		     unsigned char* result,
		     int fadeValue)
{
  unsigned char* end = result + size;      
  int negfadeValue = 255 - fadeValue;

  char masq[8];
  char masq_neg[8];
  int i;
	
  int rest = size & 0x07;

  for(i=0; i<8; i+=4)
    {
      masq[i] = fadeValue;
      masq[i+1] = fadeValue;
      masq[i+2] = fadeValue;
      masq[i+3] = fadeValue; 

      masq_neg[i] = negfadeValue;
      masq_neg[i+1] = negfadeValue;
      masq_neg[i+2] = negfadeValue;
      masq_neg[i+3] = negfadeValue; 
    }

#if defined(COMP_VC)
  {
  int s = size;
  _asm{
	  mov edi, result
	  mov esi, framebuf1
	  mov ebx, framebuf2
	  mov eax, s
	  shr eax, 3
	  cmp eax, 0
	  jz fade_mmx_end

	  movq mm5, [masq]
	  movq mm4, [masq_neg]
	  pxor mm6, mm6
	  punpcklbw mm4, mm6
	  punpcklbw mm5, mm6

loop_main:
	  
          movq mm0, [esi]
		  movq mm1, [esi]
		  
		  punpcklbw mm0, mm6
		  punpckhbw mm1, mm6
		  
		  movq mm2, [ebx]
		  movq mm3, [ebx]
		  
		  punpcklbw mm2, mm6
		  punpckhbw mm3, mm6
		  
		  pmullw mm0, mm4
		  pmullw mm1, mm4
		  
		  pmullw mm2, mm5
		  pmullw mm3, mm5
		  
		  paddw mm0, mm2
		  paddw mm1, mm3
		  
		  psrlw mm0, 8
		  psrlw mm1, 8
		  
		  packuswb mm0, mm1
		  
		  movq [edi], mm0
		  
		  add esi, 8
		  add ebx, 8
		  add edi, 8
		  dec eax
	jnz loop_main

fade_mmx_end:
	  emms
		  
  }
  }
#elif defined(COMP_GCC)
  __asm__ __volatile__ (
      "movq (%0), %%mm4                     \n\t"
      "movq (%1), %%mm5                     \n\t"
      "movl %2, %%esi                       \n\t"
      "movl %3, %%ebx                       \n\t"
      "movl %4, %%edi                       \n\t"
      "movl %5, %%eax                       \n\t"
      "shrl $3, %%eax                       \n\t"
      "cmpl $0, %%eax                       \n\t"
      "jz   2f                              \n\t"

      "pxor %%mm6, %%mm6                    \n\t"
      "punpcklbw %%mm6, %%mm4               \n\t"
      "punpcklbw %%mm6, %%mm5               \n\t"
      "1:                                   \n\t" 	  
      "    movq (%%esi), %%mm0              \n\t"
      "    movq (%%esi), %%mm1              \n\t"
			
      "	   punpcklbw %%mm6, %%mm0           \n\t"
      "	   punpckhbw %%mm6, %%mm1           \n\t"
			
      "	   movq (%%ebx), %%mm2              \n\t"
      "	   movq (%%ebx), %%mm3              \n\t"
			
      "	   punpcklbw %%mm6, %%mm2           \n\t"
      "	   punpckhbw %%mm6, %%mm3           \n\t"

      "    pmullw %%mm4, %%mm0              \n\t"
      "    pmullw %%mm4, %%mm1              \n\t"

      "    pmullw %%mm5, %%mm2              \n\t"
      "    pmullw %%mm5, %%mm3              \n\t"
			
      "    paddw %%mm2, %%mm0               \n\t"
      "    paddw %%mm3, %%mm1               \n\t"

      "    psrlw $8, %%mm0                  \n\t"
      "    psrlw $8, %%mm1                  \n\t"

      "    packuswb %%mm1, %%mm0            \n\t"
      "    movq %%mm0, (%%edi)              \n\t"
	    
      "    addl $8, %%esi                   \n\t"
      "    addl $8, %%ebx                   \n\t"
      "    addl $8, %%edi                   \n\t"
      "    decl %%eax                       \n\t"
      "jnz 1b                               \n\t"
      "2:                                   \n\t"
      "emms                                 \n\t"
      :
      : "r"(masq_neg), "r"(masq), "m" (framebuf1), "m"(framebuf2),
      "m"(result), "m" (size)
      : "eax", "ebx", "esi", "edi", "memory"
      );
#endif

  if (rest != 0) {
    uint_32 s = size & (~0x07);
    assert (s == size - rest);
    fade(rest, framebuf1+s, framebuf2+s, result+s, fadeValue);
  }
}
#endif


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
	  // inputs have different sizes

	  /*{
	    char buffer[64];
	    snprintf(buffer, sizeof(buffer),
		     "In1 = %ix%i, In2 = %ix%i\n",
		     f1->xsize, f1->ysize,
		     f2->xsize, f2->ysize);

	    s_log(2, buffer);
	    }*/

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
      else if (s_mmx_supported &&
	       strcmp(my->oldRoutine.text, "mmx") == 0)
	{
	  s_log(2, "Using mmx fading");
	  my->fade = fade_mmx;
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
      int fadeValue = (int) (number * 255);

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

      my->fade(xsize*ysize*4, (unsigned char*) fb1, (unsigned char*) fb2,
	       (unsigned char*) inst->out_r->framebuffer,
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
