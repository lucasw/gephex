#include "imgsubmodule.h"

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

static logT s_log;



typedef void (*subT)(uint_32 size,const unsigned char* framebuf1,
		     const unsigned char* framebuf2,
                     unsigned char* result, int amount);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void sub_mmx(uint_32 size, const unsigned char* framebuf1,
		    const unsigned char* framebuf2,
                    unsigned char* result, int amount);
#endif

static void sub(uint_32 size, const unsigned char* framebuf1,
		const unsigned char* framebuf2,
                unsigned char* result, int amount);

typedef struct _MyInstance {
  FrameBufferType* scaledFb;

  subT sub;

  StringType oldRoutine;
} MyInstance, *MyInstancePtr;

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

	my->sub = 0;

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

	if (strcmp(my->oldRoutine.text, inst->in_routine->text) != 0)
	  {
	    string_assign(&my->oldRoutine, inst->in_routine);

	    if (strcmp(my->oldRoutine.text, "regular") == 0)
	      {
		s_log(2, "Using regular sub routine");
		my->sub = sub;
	      }
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
	    else if (s_mmx_supported &&
		     strcmp(my->oldRoutine.text, "mmx") == 0)
	      {
		s_log(2, "Using mmx sub routine");
		my->sub = sub_mmx;
	      }
#endif
	    else
	      {
		char buffer[128];
		snprintf(buffer, sizeof(buffer),
			 "Unsupported sub routine: '%s', using 'regular' "
			 "instead",
			 my->oldRoutine.text);
		s_log(0, buffer);
		my->sub = sub;
	      }
	  }
	
	
	scale_framebuffers(inst->in_input1, inst->in_input2,
			   &my->scaledFb, &fb1, &fb2,
			   &xsize, &ysize, &didScale);
	
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
	
	my->sub(xsize*ysize*4,
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


/*****************************************************************************/

static void sub(uint_32 size,
                const unsigned char* framebuf1,
		const unsigned char* framebuf2,
                unsigned char* result,
		int amount)
{
  int i;

  for(i=size-1; i >= 0; --i)
    {
      int r = (*framebuf2++ - amount);

      if (r < 0)
	r = 0;

      r = *framebuf1++ - r;

      if (r < 0)
	r = 0;

      *result++ = r;
    }
}

#if defined(CPU_I386) && defined (OPT_INCLUDE_MMX)
static void sub_mmx(uint_32 size,
                    const unsigned char* framebuf1,
		    const unsigned char* framebuf2,
                    unsigned char* result,
		    int amount)
{
	uint_32 size_ = size;
	unsigned char masq[8];
	unsigned int i;
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
