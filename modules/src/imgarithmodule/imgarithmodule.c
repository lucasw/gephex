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
static void add_mmx(uint_32 size, const unsigned char* framebuf1,
		            const unsigned char* framebuf2,
                    unsigned char* result, int amount);
static void sub_mmx(uint_32 size, const unsigned char* framebuf1,
		            const unsigned char* framebuf2,
                    unsigned char* result, int amount);
static void mul_mmx(uint_32 size, const unsigned char* framebuf1,
		            const unsigned char* framebuf2,
                    unsigned char* result, int amount);
static void addc_mmx(uint_32 size, const unsigned char* framebuf1,
		            const unsigned char* framebuf2,
                    unsigned char* result, int amount);
static void subc_mmx(uint_32 size, const unsigned char* framebuf1,
		             const unsigned char* framebuf2,
                     unsigned char* result, int amount);
static void mulc_mmx(uint_32 size, const unsigned char* framebuf1,
		            const unsigned char* framebuf2,
                    unsigned char* result, int amount);
static void invert_mmx(uint_32 size, const unsigned char* framebuf1,
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

} MyInstance, *MyInstancePtr;

//-----------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    {
      s_mmx_supported = cpuinfo_has_mmx();
      s_log(2, "found mmx support");
    }
  else
    {
      s_mmx_supported = 0;
      s_log(2, "no mmx support");
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

	my->op = 0;

	my->binary = 1;

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


void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	
	int amount = (int) (255 * trim_double(inst->in_amount->number, 0, 1));
	
	uint_32* fb1 = 0;
	uint_32* fb2 = 0;	  
	int didScale = 0;
	
	int xsize = 0, ysize = 0;
	int mmx = strcmp(inst->in_mmx->text, "yes") == 0;

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
				s_log(2, "Using regular add routine");
				my->op = add;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx add routine");
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
				s_log(2, "Using regular sub routine");
				my->op = sub;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx sub routine");
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
				s_log(2, "Using regular mul routine");
				my->op = mul;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx mul routine");
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
				s_log(2, "Using regular addc routine");
				my->op = addc;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx addc routine");
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
				s_log(2, "Using regular subc routine");
				my->op = subc;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx subc routine");
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
				s_log(2, "Using regular addc routine");
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
				s_log(2, "Using regular invert routine");
				my->op = invert;
			} else
			{
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
				if (s_mmx_supported)		       
				{
					s_log(2, "Using mmx invert routine");
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
				"Unknown Operation: '%s' - using 'x - c*y'instead", inst->in_op->text);
			s_log(0, buffer);

			my->binary = 1;
			my->op = sub;
		}
	}

	assert(my->op);

	if (my->binary) {
		scale_framebuffers(inst->in_input1, inst->in_input2,
			&my->scaledFb, &fb1, &fb2,
			&xsize, &ysize, &didScale);
	}
	else {
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
	
	my->op(xsize*ysize*4,
           (const unsigned char*) fb1,
		   (const unsigned char*) fb2,
		   (unsigned char*) inst->out_result->framebuffer,
		   amount);

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
	if (my->binary == 0)
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

  for(i=size-1; i >= 0; --i)
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

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void sub_mmx(uint_32 size, const unsigned char* framebuf1,
		    const unsigned char* framebuf2, unsigned char* result, int amount)
{
	uint_32 size_ = size;
	unsigned char masq[8];
	unsigned int i;
	int rest = size_ & 0x0f;

	for(i=0; i<8; i+=4)
	{
		masq[i]   = 255-amount;
		masq[i+1] = 255-amount;
		masq[i+2] = 255-amount;
		masq[i+3] = 0; //TODO: alpha?
	}

#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1
		mov ebx, framebuf2
		mov edi, result
		mov eax, size_
		movq mm4, masq
		shr eax, 4
		cmp eax, 0
	    jz sub_mmx_end

		inst_loop:
			movq mm0, [esi]
			movq mm1, [esi+8]
			movq mm2, [ebx]
			movq mm3, [ebx+8]
			psubusb mm2, mm4
			psubusb mm3, mm4 
			psubusb mm0, mm2 
			psubusb mm1, mm3
			movq [edi], mm0
			movq [edi+8], mm1
			add esi, 16
			add ebx, 16
			add edi, 16
			dec eax
		jnz inst_loop
sub_mmx_end:
		emms
	}
	
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
          int d0, d1, d2, d3;
          //TODO: if I use the register ebx here,
          // the whole thing crashes (even though ebx is in the globlist!!!)
          // If ebx is safed manually (push/pop), everything is ok.
          // If I use eax instead, everything is ok, too!
          // Bug in the compiler???
          // (occurred with gcc-3.2 when using -O1 or more
          //  and with gcc-2.95.4 when using -O3)
          // When running with valgrind, everythong works.
          // With gdb, gdb hangs inside the asm block.
	  __asm__ __volatile__ (
	      "movq (%5),%%mm4                   \n\t"
	      "shrl $4, %0                       \n\t"
	      "cmpl $0, %0                       \n\t"
	      "jz 2f                             \n\t"
	      "1:                                \n\t"
	      "    movq  (%1), %%mm0             \n\t"
	      "    movq 8(%1), %%mm1             \n\t"
	      "    movq  (%2), %%mm2             \n\t"
	      "    movq 8(%2), %%mm3             \n\t"
	      "    psubusb %%mm4, %%mm2          \n\t"
	      "    psubusb %%mm4, %%mm3          \n\t"
	      "    psubusb %%mm2, %%mm0          \n\t"
	      "    psubusb %%mm3, %%mm1          \n\t"
	      "    movq %%mm0,  (%3)             \n\t"
	      "    movq %%mm1, 8(%3)             \n\t"	      
	      "    addl $16, %1                  \n\t"
	      "    addl $16, %2                  \n\t"
	      "    addl $16, %3                  \n\t"
	      "    decl %0                       \n\t"
	      "jnz 1b                            \n\t"
	      "2:                                \n\t"
	      "emms                              \n\t"
              : "=&r"(d0), "=&r"(d1), "=&r"(d2), "=&r"(d3)
	      : "0" (size_), "r"(masqPtr), "1" (framebuf1), "2"(framebuf2),
	       "3"(result)
	      : "memory"
	      );
	}
#else
	printf("not implemented yet!");
	return;
#endif

	if (rest != 0)
	  {
	    int s = size - rest;
            sub(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif

//------------------------------------------------------------------------
// MUL

static void mul(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;  

  for(i=size-1; i >= 0; --i)
    {
	  int f1 = *framebuf1++;
      int r = f1 * ((int) *framebuf2++);
	  
      r >>= 8;

	  r = (255-amount) * f1 + amount * r;

	  r >>= 8;	  
	  
      *result++ = (unsigned char) r;
  }
}

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void mul_mmx(uint_32 size,
                    const unsigned char* framebuf1,
          		    const unsigned char* framebuf2,
                    unsigned char* result,
		            int amount)
{
    unsigned char masq[8];
	unsigned char masq_neg[8];
	unsigned char zero[8];
	int i;
	int size_ = size;
	int rest = size_ & 0x0f; //TODO?

	for(i=0; i<8; i+=4)
	{
		masq[i] = amount;
		masq[i+1] = amount;
		masq[i+2] = amount;
		masq[i+3] = 0; //TODO: alpha?
		//masq[i+3] = amount;

		zero[i] = 0;
		zero[i+1] = 0;
		zero[i+2] = 0;
		zero[i+3] = 0;

		masq_neg[i] = 255-amount;
		masq_neg[i+1] = 255-amount;
		masq_neg[i+2] = 255- amount;
		masq_neg[i+3] = 0;
		//masq_neg[i+3] = 255-amount;
	}

#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1
		mov ebx, framebuf2
		mov edi, result
		mov eax, size_
		movq mm5, zero
		shr eax, 3
		cmp eax, 0
		jz mul_mmx_end

		inst_loop:
			movq mm4, masq
			movq mm6, masq_neg
			movq mm0, [esi]
			punpcklbw mm0, mm5
		
			movq mm1, [ebx]	
			punpcklbw mm1, mm5
			
			pmullw mm0, mm1
			psrlw mm0, 8
			
			movq mm2, [esi]
			punpckhbw mm2, mm5

			movq mm3, [ebx]
			punpckhbw mm3, mm5
	
			pmullw mm2, mm3
			psrlw mm2, 8
			
			packuswb mm0, mm2
			
			movq mm1, [esi]
			movq mm2, mm1
			punpcklbw mm1, mm5
			punpckhbw mm2, mm5
			punpcklbw mm6, mm5

			movq mm3, mm0
			punpcklbw mm0, mm5
			punpckhbw mm3, mm5
			punpcklbw mm4, mm5

			pmullw mm1, mm6
			pmullw mm2, mm6
			pmullw mm0, mm4
			pmullw mm3, mm4
			
			paddw mm1, mm0
			paddw mm2, mm3

			psrlw mm1, 8
			psrlw mm2, 8

			packuswb mm1, mm2

			movq [edi], mm1			

			add esi, 8
			add ebx, 8
			add edi, 8
			dec eax
		jnz inst_loop
mul_mmx_end:
		emms
	}
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
	  unsigned char* negmasqPtr = masq_neg;
	  unsigned char* zeroPtr = zero;
      int d0, d1, d2, d3;          
      __asm__ __volatile__ 
        (
         "movq (%10), %%mm5                 \n\t"
         "shrl $3, %0                       \n\t"
         "cmpl $0, %0                       \n\t"
         "jz 2f                             \n\t"
         "1:                                \n\t"
         "    movl  %5, %10                 \n\t"
         "    movq  (%10), %%mm4            \n\t"
         "    movl  %9, %10                 \n\t"
         "    movq  (%10), %%mm6            \n\t"
           
         "    movq  (%1), %%mm0             \n\t"
         "    punpcklbw %%mm5, %%mm0        \n\t"
           
         "    movq  (%2), %%mm1             \n\t"
         "    punpcklbw %%mm5, %%mm1        \n\t"
           
         "    pmullw %%mm1, %%mm0           \n\t"
         "    psrlw     $8, %%mm0           \n\t"
           
         "    movq  (%1), %%mm2             \n\t"
         "    punpckhbw %%mm5, %%mm2        \n\t"

         "    movq  (%2), %%mm3             \n\t"
         "    punpckhbw %%mm5, %%mm3        \n\t"

         "    pmullw %%mm3, %%mm2           \n\t"
         "    psrlw     $8, %%mm2           \n\t"
           
         "    packuswb  %%mm2, %%mm0        \n\t"

         "    movq  (%1),  %%mm1            \n\t"
         "    movq  %%mm1, %%mm2            \n\t"
         "    punpcklbw %%mm5, %%mm1        \n\t"
         "    punpckhbw %%mm5, %%mm2        \n\t"
         "    punpcklbw %%mm5, %%mm6        \n\t"
	      
         "    movq %%mm0, %%mm3             \n\t"
         "    punpcklbw %%mm5, %%mm0        \n\t"
         "    punpckhbw %%mm5, %%mm3        \n\t"
         "    punpcklbw %%mm5, %%mm4        \n\t"

         "    pmullw   %%mm6, %%mm1         \n\t"
         "    pmullw   %%mm6, %%mm2         \n\t"
         "    pmullw   %%mm4, %%mm0         \n\t"
         "    pmullw   %%mm4, %%mm3         \n\t"

         "    paddw    %%mm0, %%mm1         \n\t"
         "    paddw    %%mm3, %%mm2         \n\t"

         "    psrlw       $8, %%mm1         \n\t"
         "    psrlw       $8, %%mm2         \n\t"
           
         "    packuswb  %%mm2, %%mm1        \n\t"

         "    movq %%mm1,  (%3)             \n\t"
	      
         "    addl $8, %1                   \n\t"
         "    addl $8, %2                   \n\t"
         "    addl $8, %3                   \n\t"
         "    decl %0                       \n\t"
         "jnz 1b                            \n\t"
         "2:                                \n\t"
         "emms                              \n\t"
         : "=&r"(d0), "=&r"(d1), "=&r"(d2), "=&r"(d3)
         : "0" (size_), "m"(masqPtr), "1" (framebuf1), "2"(framebuf2),
         "3"(result), "m"(negmasqPtr), "r"(zeroPtr)
         : "memory"
         );
	}

#else
	printf("Not impl.\n");
#endif
	if (rest != 0)
	  {
	    int s = size - rest;
            sub(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif

//------------------------------------------------------------------------
// ADD

static void add(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;
  int a = 255-amount;

  for(i=size-1; i >= 0; --i)
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

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void add_mmx(uint_32 size,
                    const unsigned char* framebuf1,
          		    const unsigned char* framebuf2,
                    unsigned char* result,
		            int amount)
{
	int size_ = size;
    int i;
	unsigned char masq[8];
	int rest = size_ & 0x0f;

	for(i=0; i<8; i+=4)
	{
		masq[i]   = 255-amount;
		masq[i+1] = 255-amount;
		masq[i+2] = 255-amount;
		masq[i+3] = 0; //TODO: alpha?
	}

#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1
		mov ebx, framebuf2
		mov edi, result
		mov eax, size_
		movq mm4, masq
		shr eax, 4
  	    cmp eax, 0
	    jz add_mmx_end

		inst_loop:
			movq mm0, [esi]
			movq mm1, [esi+8]
			movq mm2, [ebx]
			movq mm3, [ebx+8]
			psubusb mm2, mm4
			psubusb mm3, mm4 
			paddusb mm0, mm2 
			paddusb mm1, mm3
			movq [edi], mm0
			movq [edi+8], mm1
			add esi, 16
			add ebx, 16
			add edi, 16
			dec eax
		jnz inst_loop
add_mmx_end:
		emms
	}
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
      int d0, d1, d2, d3;          
	  __asm__ __volatile__ (
	      "movq (%5),%%mm4                   \n\t"
	      "shrl $4, %0                       \n\t"
	      "cmpl $0, %0                       \n\t"
	      "jz 2f                             \n\t"
	      "1:                                \n\t"
	      "    movq  (%1), %%mm0             \n\t"
	      "    movq 8(%1), %%mm1             \n\t"
	      "    movq  (%2), %%mm2             \n\t"
	      "    movq 8(%2), %%mm3             \n\t"
	      "    psubusb %%mm4, %%mm2          \n\t"
	      "    psubusb %%mm4, %%mm3          \n\t"
	      "    paddusb %%mm2, %%mm0          \n\t"
	      "    paddusb %%mm3, %%mm1          \n\t"
	      "    movq %%mm0,  (%3)             \n\t"
	      "    movq %%mm1, 8(%3)             \n\t"	      
	      "    addl $16, %1                  \n\t"
	      "    addl $16, %2                  \n\t"
	      "    addl $16, %3                  \n\t"
	      "    decl %0                       \n\t"
	      "jnz 1b                            \n\t"
	      "2:                                \n\t"
	      "emms                              \n\t"
              : "=&r"(d0), "=&r"(d1), "=&r"(d2), "=&r"(d3)
	      : "0" (size_), "r"(masqPtr), "1" (framebuf1), "2"(framebuf2),
	       "3"(result)
	      : "memory"
	      );
	}
#else
	printf("not implemented yet!");
	return;
#endif
    if (rest != 0)
	  {
	    int s = size - rest;
            add(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif

//------------------------------------------------------------------------
// ADDC

static void addc(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;

  for(i=size-1; i >= 0; --i)
    {
      int r = *framebuf1++ + amount;

	  if (r > 255)
	    r = 255;

      *result++ = r;
    }
}

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void addc_mmx(uint_32 size,
                    const unsigned char* framebuf1,
          		    const unsigned char* framebuf2,
                    unsigned char* result,
		            int amount)
{
	int size_ = size;
    int i;
	unsigned char masq[8];
	int rest = size_ & 0x0f;

	for(i=0; i<8; i+=4)
	{
		masq[i]   = amount;
		masq[i+1] = amount;
		masq[i+2] = amount;
		masq[i+3] = 0; //TODO: alpha?
	}

#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1		
		mov edi, result
		mov eax, size_
		movq mm4, masq
		shr eax, 4
  	    cmp eax, 0
	    jz add_mmx_end

		inst_loop:
			movq mm0, [esi]
			movq mm1, [esi+8]			
			paddusb mm0, mm4 
			paddusb mm1, mm4
			movq [edi],   mm0
			movq [edi+8], mm1
			add esi, 16			
			add edi, 16
			dec eax
		jnz inst_loop
add_mmx_end:
		emms
	}
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
      int d0, d1, d2;          
	  __asm__ __volatile__ (
	      "movq (%4),%%mm4                   \n\t"
	      "shrl $4, %0                       \n\t"
	      "cmpl $0, %0                       \n\t"
	      "jz 2f                             \n\t"
	      "1:                                \n\t"
	      "    movq  (%1), %%mm0             \n\t"
	      "    movq 8(%1), %%mm1             \n\t"	      	      
	      "    paddusb %%mm4, %%mm0          \n\t"
	      "    paddusb %%mm4, %%mm1          \n\t"
	      "    movq %%mm0,  (%2)             \n\t"
	      "    movq %%mm1, 8(%2)             \n\t"	      
	      "    addl $16, %1                  \n\t"	      
	      "    addl $16, %2                  \n\t"
	      "    decl %0                       \n\t"
	      "jnz 1b                            \n\t"
	      "2:                                \n\t"
	      "emms                              \n\t"
              : "=&r"(d0), "=&r"(d1), "=&r"(d2)
	      : "0" (size_), "r"(masqPtr), "1" (framebuf1), 
	       "2"(result)
	      : "memory"
	      );
	}
#else
	printf("not implemented yet!");
	return;
#endif
    if (rest != 0)
	  {
	    int s = size - rest;
            addc(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif

//------------------------------------------------------------------------
// SUBC

static void subc(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;

  for(i=size-1; i >= 0; --i)
    {
      int r = *framebuf1++ - amount;

	  if (r < 0)
	    r = 0;

      *result++ = r;
    }
}

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void subc_mmx(uint_32 size,
                    const unsigned char* framebuf1,
          		    const unsigned char* framebuf2,
                    unsigned char* result,
		            int amount)
{
	int size_ = size;
    int i;
	unsigned char masq[8];
	int rest = size_ & 0x0f;

	for(i=0; i<8; i+=4)
	{
		masq[i]   = amount;
		masq[i+1] = amount;
		masq[i+2] = amount;
		masq[i+3] = 0; //TODO: alpha?
	}

#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1		
		mov edi, result
		mov eax, size_
		movq mm4, masq
		shr eax, 4
  	    cmp eax, 0
	    jz add_mmx_end

		inst_loop:
			movq mm0, [esi]
			movq mm1, [esi+8]			
			psubusb mm0, mm4 
			psubusb mm1, mm4
			movq [edi],   mm0
			movq [edi+8], mm1
			add esi, 16			
			add edi, 16
			dec eax
		jnz inst_loop
add_mmx_end:
		emms
	}
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
      int d0, d1, d2;          
	  __asm__ __volatile__ (
	      "movq (%4),%%mm4                   \n\t"
	      "shrl $4, %0                       \n\t"
	      "cmpl $0, %0                       \n\t"
	      "jz 2f                             \n\t"
	      "1:                                \n\t"
	      "    movq  (%1), %%mm0             \n\t"
	      "    movq 8(%1), %%mm1             \n\t"	      	      
	      "    psubusb %%mm4, %%mm0          \n\t"
	      "    psubusb %%mm4, %%mm1          \n\t"
	      "    movq %%mm0,  (%2)             \n\t"
	      "    movq %%mm1, 8(%2)             \n\t"	      
	      "    addl $16, %1                  \n\t"	      
	      "    addl $16, %2                  \n\t"
	      "    decl %0                       \n\t"
	      "jnz 1b                            \n\t"
	      "2:                                \n\t"
	      "emms                              \n\t"
              : "=&r"(d0), "=&r"(d1), "=&r"(d2)
	      : "0" (size_), "r"(masqPtr), "1" (framebuf1), 
	       "2"(result)
	      : "memory"
	      );
	}
#else
	printf("not implemented yet!");
	return;
#endif
    if (rest != 0)
	  {
	    int s = size - rest;
            subc(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif

//------------------------------------------------------------------------
// MULC

static void mulc(uint_32 size, const unsigned char* framebuf1,
          	    const unsigned char* framebuf2,
                unsigned char* result, int amount)
{
  int i;

  for(i=size-1; i >= 0; --i)
    {
      int r = *framebuf1++ * amount;

	  r >>= 6;
	  if (r > 255)
		  r = 255;

      *result++ = r;
    }
}

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void mulc_mmx(uint_32 size,
                    const unsigned char* framebuf1,
          		    const unsigned char* framebuf2,
                    unsigned char* result,
		            int amount)
{
	int size_ = size;
	uint_16 masq[4];
	unsigned char zero[8];
	int rest = size_ & 0x0f; //TODO

	memset(zero, 0, 8);
	
	masq[0] = amount;
	masq[1] = amount;
	masq[2] = amount;
	masq[3] = 0; //TODO: alpha?


#if defined(COMP_VC)
	_asm{
		mov esi, framebuf1		
		mov edi, result
		mov eax, size_
		movq mm4, masq
		movq mm5, zero
		shr eax, 3
  	    cmp eax, 0
	    jz add_mmx_end

		inst_loop:
			movq      mm0, [esi]
		    movq      mm1, mm0
			punpcklbw mm0, mm5
			punpckhbw mm1, mm5

			pmullw    mm0, mm4
			psrlw     mm0, 6

			pmullw    mm1, mm4
			psrlw     mm1, 6

			//psllw   mm0, 2
			//psllw   mm1, 2

			packuswb mm0, mm1

			movq    [edi], mm0
			
			add esi, 8
			add edi, 8
			dec eax
		jnz inst_loop
add_mmx_end:
		emms
	}
#elif defined(COMP_GCC)
	{
	  unsigned char* masqPtr = masq;
	  unsigned char* zeroPtr = zero;
      int d0, d1, d2;          
	  __asm__ __volatile__ 
            (
             "movq (%4), %%mm4                  \n\t"
             "movq (%7), %%mm5                  \n\t"
             "shrl $3, %0                       \n\t"
             "cmpl $0, %0                       \n\t"
             "jz 2f                             \n\t"
             "1:                                \n\t"
             "    movq        (%1), %%mm0       \n\t"
             "    movq       %%mm0, %%mm1       \n\t"	      	      
	      
             "    punpcklbw  %%mm5, %%mm0       \n\t"
             "    punpckhbw  %%mm5, %%mm1       \n\t"

             "    pmullw     %%mm4, %%mm0       \n\t"
             "    pmullw     %%mm4, %%mm1       \n\t"

             "    psrlw         $6, %%mm0       \n\t"
             "    psrlw         $6, %%mm1       \n\t"

             "    packuswb   %%mm1, %%mm0       \n\t"

             "    movq %%mm0,  (%2)             \n\t"

             "    addl $8, %1                   \n\t"	      
             "    addl $8, %2                   \n\t"
             "    decl %0                       \n\t"
             "jnz 1b                            \n\t"
             "2:                                \n\t"
             "emms                              \n\t"
             : "=&r"(d0), "=&r"(d1), "=&r"(d2)
             : "0" (size_), "r"(masqPtr), "1" (framebuf1), 
             "2"(result), "r"(zeroPtr)
             : "memory"
             );
	}
#else
	printf("not implemented yet!");
	return;
#endif
    if (rest != 0)
	  {
	    int s = size - rest;
            mulc(rest, framebuf1+s, framebuf2+s, result+s, amount);
	  }
}
#endif


//------------------------------------------------------------------------
// MULC

static void invert( uint_32 size,
				    const unsigned char* src,
					const unsigned char* dummy,
				    unsigned char* dst, int amount )
{
	int i;

    for (i = size-1; i >= 0; --i)
	{
	  *(dst++) = 255 - *(src++);
	}
}


#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void invert_mmx( uint_32 size, 
				    const unsigned char* src,
				    const unsigned char* dummy,
				    unsigned char* dst, int amount )
{
	unsigned char masq[8];
	int _size = size;
	int i;
	int rest;
		  
    for (i = 0; i < 8; i+=4)
      {
		masq[i]   = 255;
		masq[i+1] = 255;
		masq[i+2] = 255;
		masq[i+3] = 0;
      }
    rest = size & 0x07;
		  
#if defined(COMP_VC)
    _asm {
    mov esi, src
	mov edi, dst
	mov eax, _size
	shr eax, 5
	cmp eax, 0
	jz inv_mmx_end
	movq mm4, [masq]
	my_loop:
        movq mm0, [esi]
        movq mm1, [esi+8]
	    movq mm2, [esi+16]
	    movq mm3, [esi+24]
	    pxor mm0, mm4
	    pxor mm1, mm4
	    pxor mm2, mm4
	    pxor mm3, mm4
	    movq [edi], mm0
	    movq [edi+8], mm1
	    movq [edi+16], mm2
	    movq [edi+24], mm3
	    add esi, 32
	    add edi, 32
	    dec eax
	jnz my_loop
	emms
inv_mmx_end:
	}
	  
#elif defined(COMP_GCC)
    {
      unsigned char* masqPtr = masq;
      int d0, d1, d2;
      __asm__ __volatile__ (
	  "shr  $5, %%eax                       \n\t"
	  "cmpl $0, %%eax                       \n\t"
	  "jz 2f                                \n\t"
	  "movq (%3),%%mm4                      \n\t"
	  "1:                                   \n\t"
	  "    movq (%%esi), %%mm0              \n\t"
	  "    movq 8(%%esi), %%mm1             \n\t"
	  "    movq 16(%%esi),%%mm2             \n\t"
	  "    movq 24(%%esi), %%mm3            \n\t"
	  "    pxor %%mm4, %%mm0                \n\t"
	  "    pxor %%mm4, %%mm1                \n\t"
	  "    pxor %%mm4, %%mm2                \n\t"
	  "    pxor %%mm4, %%mm3                \n\t"
	  "    movq %%mm0, (%%edi)              \n\t"
	  "    movq %%mm1, 8(%%edi)             \n\t"
	  "    movq %%mm2, 16(%%edi)            \n\t"
	  "    movq %%mm3, 24(%%edi)            \n\t"
	  "    addl $32, %%esi                  \n\t"
	  "    addl $32, %%edi                  \n\t"
	  "    decl %%eax                       \n\t"
	  "jnz 1b                               \n\t"
	  "emms                                 \n\t"
	  "2:                                   \n\t"
	  : "=&a"(d0), "=&S"(d1), "=&D"(d2)
	  : "r"(masqPtr), "0" (_size), "1" (src), "2"(dst)
          : "memory"
	  );
    }
#else
#error "Not implemented for this compiler!"
#endif

	if (rest != 0)
	{
          int pos = size - rest;
          invert(rest, src+pos, 0, dst + pos, 1);
	}
}
#endif
