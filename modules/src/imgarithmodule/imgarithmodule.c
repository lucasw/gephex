/* Simple Image Arithmetics
  Copyright (C) 2003 Martin Bayer, Georg Seidel, Philipp Promesberger
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/

#include "imgarithmodule.h"

#include <limits.h>
#include <assert.h>
#include <math.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

//-----------------------------------------------------------------------

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
#include "cpuinfo.h"
static int s_mmx_supported = 0;
#endif

static logT s_log;

//-----------------------------------------------------------------------

typedef void (*opT)(uint_32 size,const unsigned char* framebuf1,
                    const unsigned char* framebuf2,
                    unsigned char* result, int amount);

//-----------------------------------------------------------------------

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
extern void add_mmx(uint_32 size, const unsigned char* framebuf1,
                    const unsigned char* framebuf2,
                    unsigned char* result, int amount);
extern void sub_mmx(uint_32 size, const unsigned char* framebuf1,
                    const unsigned char* framebuf2,
                    unsigned char* result, int amount);
extern void mul_mmx(uint_32 size, const unsigned char* framebuf1,
                    const unsigned char* framebuf2,
                    unsigned char* result, int amount);
extern void addc_mmx(uint_32 size, const unsigned char* framebuf1,
                     const unsigned char* framebuf2,
                     unsigned char* result, int amount);
extern void subc_mmx(uint_32 size, const unsigned char* framebuf1,
                     const unsigned char* framebuf2,
                     unsigned char* result, int amount);
extern void mulc_mmx(uint_32 size, const unsigned char* framebuf1,
                     const unsigned char* framebuf2,
                     unsigned char* result, int amount);
extern void invert_mmx(uint_32 size, const unsigned char* framebuf1,
                       const unsigned char* framebuf2,
                       unsigned char* result, int amount);
#endif

static void add(uint_32 size, const unsigned char* framebuf1,
                const unsigned char* framebuf2,
                unsigned char* result, int amount);
static void sub(uint_32 size, const unsigned char* framebuf1,
                const unsigned char* framebuf2,
                unsigned char* result, int amount);
static void mul(uint_32 size, const unsigned char* framebuf1,
                const unsigned char* framebuf2,
                unsigned char* result, int amount);
static void addc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* framebuf2,
                 unsigned char* result, int amount);
static void subc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* framebuf2,
                 unsigned char* result, int amount);
static void mulc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* framebuf2,
                 unsigned char* result, int amount);
static void invert(uint_32 size, const unsigned char* framebuf1,
                   const unsigned char* framebuf2,
                   unsigned char* result, int amount);

//-----------------------------------------------------------------------

typedef struct _MyInstance {
  FrameBufferType* scaledFb;

  opT op;

  StringType operation;
  StringType mmx;

  int binary;
  int amount;
} MyInstance, *MyInstancePtr;

//-----------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    s_mmx_supported = cpuinfo_has_mmx();
  else
    s_mmx_supported = 0;

  if (s_mmx_supported)
    s_log(2, "found mmx support");
  else
    s_log(2, "no mmx support");
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

  my->op = 0;

  my->binary = 1;
  my->amount = 0;

  string_initInstance(&my->operation);
  string_initInstance(&my->mmx);

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFb != 0)
    framebuffer_deleteInstance(my->scaledFb);

  string_destroyInstance(&my->operation);
  string_destroyInstance(&my->mmx);
  free(my);
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
      // inputs have different sizes

      /*{
        char buffer[64];
        snprintf(buffer, sizeof(buffer),
        "In1 = %ix%i, In2 = %ix%i\n",
        f1->xsize, f1->ysize,
        f2->xsize, f2->ysize);

        s_log(3, buffer);
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


static void handle_params(InstancePtr inst)
{
  MyInstancePtr my = inst->my;

  int mmx = strcmp(inst->in_mmx->text, "yes") == 0;

  my->amount = (int) floor(.5 + 255*trim_double(inst->in_amount->number,0,1));

  if (strcmp(my->operation.text, inst->in_op->text) != 0 ||
      strcmp(my->mmx.text, inst->in_mmx->text) != 0 ||
      my->op == 0)
    {
      string_assign(&my->operation, inst->in_op);
      string_assign(&my->mmx, inst->in_mmx);
		
      // add
      if (strcmp(my->operation.text, "x + c*y") == 0)
        {
          my->binary = 1;
          if (!mmx)
            {
              //              s_log(2, "Using regular add routine");
              my->op = add;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    //                    s_log(2, "Using mmx add routine");
                    my->op = add_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = add;
                  }
              }
        }

      // sub
      else if (strcmp(my->operation.text, "x - c*y") == 0)
        {
          my->binary = 1;
          if (!mmx)
            {
              //              s_log(2, "Using regular sub routine");
              my->op = sub;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    //                    s_log(2, "Using mmx sub routine");
                    my->op = sub_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = sub;
                  }
              }
        }

      // mul
      else if (strcmp(my->operation.text, "(1-c)*x + c*(x*y)") == 0)
        {
          my->binary = 1;
          if (!mmx)
            {
              //              s_log(2, "Using regular mul routine");
              my->op = mul;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    //                    s_log(2, "Using mmx mul routine");
                    my->op = mul_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = mul;
                  }
              }
        }

      // addc
      else if (strcmp(my->operation.text, "x + c") == 0)
        {
          my->binary = 0;
          if (!mmx)
            {
              //              s_log(2, "Using regular addc routine");
              my->op = addc;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    //                    s_log(2, "Using mmx addc routine");
                    my->op = addc_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = addc;
                  }
              }
        }

      // addc
      else if (strcmp(my->operation.text, "x - c") == 0)
        {
          my->binary = 0;
          if (!mmx)
            {
              //              s_log(2, "Using regular subc routine");
              my->op = subc;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    //                   s_log(2, "Using mmx subc routine");
                    my->op = subc_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = subc;
                  }
              }
        }

      // mulc
      else if (strcmp(my->operation.text, "x * 4*c") == 0)
        {
          my->binary = 0;
          if (!mmx)
            {
              //              s_log(2, "Using regular addc routine");
              my->op = mulc;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
                    s_log(2, "Using mmx addc routine");
                    my->op = mulc_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = mulc;
                  }
              }
        }

      // invert
      else if (strcmp(my->operation.text, "1 - x") == 0)
        {
          my->binary = 0;
          if (!mmx)
            {
              //              s_log(2, "Using regular invert routine");
              my->op = invert;
            } else
              {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
                if (s_mmx_supported)		       
                  {
//                    s_log(2, "Using mmx invert routine");
                    my->op = invert_mmx;
                  }
                else
#endif
                  {					
                    s_log(0, "No mmx support found, using 'regular' instead");
                    my->op = invert;
                  }
              }
        }
      else
        {
          char buffer[128];
          snprintf(buffer, sizeof(buffer),
                   "Unknown Operation: '%s' - using 'x - c*y'instead",
                   inst->in_op->text);
          s_log(0, buffer);

          my->binary = 1;
          my->op = sub;
        }
    }

}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  uint_32* fb1 = 0;
  uint_32* fb2 = 0;	  
  int didScale = 0;
	
  int xsize = 0, ysize = 0;

  // params have been handled in strongDependencies

  assert(my->op);

  if (my->binary && my->amount != 0)
    {
      scale_framebuffers(inst->in_input1, inst->in_input2,
                         &my->scaledFb, &fb1, &fb2,
                         &xsize, &ysize, &didScale);
    }
  else
    {
      fb1 = inst->in_input1->framebuffer;
      didScale = 0;
      xsize = inst->in_input1->xsize;
      ysize = inst->in_input1->ysize;
    }
	
  // scale output framebuffer to the size of the inputs
  {
    FrameBufferAttributes attribs;
		
    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_result, &attribs);
  }
	
  assert(didScale == 0 || (my->scaledFb->xsize == xsize &&
                           my->scaledFb->ysize == ysize));
	
  assert(inst->out_result->xsize == xsize
         && inst->out_result->ysize == ysize);	
	
  if (my->amount == 0 && my->binary == 1)
    {
      memcpy(inst->out_result->framebuffer,
             fb1, xsize*ysize*4);
    }
  else
    my->op(xsize*ysize,
           (const unsigned char*) fb1,
           (const unsigned char*) fb2,
           (unsigned char*) inst->out_result->framebuffer,
           my->amount);

  // delete scaled framebuffer if we didn't need it this time
  if (didScale == 0 && my->scaledFb != 0)
    {		
      framebuffer_deleteInstance(my->scaledFb);
      my->scaledFb = 0;	
    }
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  MyInstancePtr my = inst->my;

  handle_params(inst);

  if (my->binary == 0)
    neededInputs[in_input2] = 0;
  else if (my->amount == 0)
    neededInputs[in_input2] = 0;
}

//------------------------------------------------------------------------
// SUB

static void sub(uint_32 size, const unsigned char* framebuf1,
                const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;
  int a = 255-amount;

  for(i=size*4-1; i >= 0; --i)
    {
      int r = (*framebuf2++ - a);

      if (r < 0)
	r = 0;

      r = *framebuf1++ - r;

      if (r < 0)
	r = 0;

      *result++ = r;
    }
}

//------------------------------------------------------------------------
// MUL

static void mul(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;  

  for(i=size*4-1; i >= 0; --i)
    {
      int f1 = *framebuf1++;
      int r = f1 * ((int) *framebuf2++);
	  
      r >>= 8;

      r = (255-amount) * f1 + amount * r;

      r >>= 8;	  
	  
      *result++ = (unsigned char) r;
    }
}

//------------------------------------------------------------------------
// ADD

static void add(uint_32 size, const unsigned char* framebuf1,
                const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;
  int a = 255-amount;

  for(i=size*4-1; i >= 0; --i)
    {
      int r = (*framebuf2++ - a);

      if (r < 0)
        r = 0;

      r = *framebuf1++ + r;

      if (r > 255)
        r = 255;

      *result++ = r;
    }
}

//------------------------------------------------------------------------
// ADDC

static void addc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* forget_this_warning,
                 unsigned char* result, int amount)
{
  int i;

  for(i=size*4-1; i >= 0; --i)
    {
      int r = *framebuf1++ + amount;

      if (r > 255)
        r = 255;

      *result++ = r;
    }
}

//------------------------------------------------------------------------
// SUBC

static void subc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* mind_your_own_business,
                 unsigned char* result, int amount)
{
  int i;

  for(i=size*4-1; i >= 0; --i)
    {
      int r = *framebuf1++ - amount;

      if (r < 0)
        r = 0;

      *result++ = r;
    }
}

//------------------------------------------------------------------------
// MULC

static void mulc(uint_32 size, const unsigned char* framebuf1,
                 const unsigned char* not_a_warning,
                 unsigned char* result, int amount)
{
  int i;

  for(i=size*4-1; i >= 0; --i)
    {
      int r = *framebuf1++ * amount;

      r >>= 6;
      if (r > 255)
        r = 255;

      *result++ = r;
    }
}


//------------------------------------------------------------------------
// invert

static void invert(uint_32 size,
                   const unsigned char* src,
                   const unsigned char* is_not_important,
                   unsigned char* dst, int is_of_no_interest )
{
  int i;

  for (i = size*4-1; i >= 0; --i)
    {
      *(dst++) = 255 - *(src++);
    }
}

//------------------------------------------------------------------------
