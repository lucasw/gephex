#include "invertmodule.h"

#include <stdio.h>

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


typedef void (*invertT)(uint_32* dst, const uint_32* src, int size);

static void invert(uint_32* dst, const uint_32* src, int size);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void invert_mmx(uint_32* dst, const uint_32* src, int size);
#endif


typedef struct _MyInstance {

  invertT invert;

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

  my->invert = 0;

  string_initInstance(&my->oldRoutine);

  return my;
}

void destruct(MyInstance* my)
{
  string_destroyInstance(&my->oldRoutine);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  FrameBufferAttributes attribs;
	  
  framebuffer_getAttributes(inst->in_b, &attribs);
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (strcmp(my->oldRoutine.text, inst->in_routine->text) != 0)
	  {
	    string_assign(&my->oldRoutine, inst->in_routine);

	    if (strcmp(my->oldRoutine.text, "regular") == 0)
	      {
		s_log(2, "Using regular invert routine");
		my->invert = invert;
	      }
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
	    else if (s_mmx_supported &&
		     strcmp(my->oldRoutine.text, "mmx") == 0)
	      {
		s_log(2, "Using mmx invert routine");
		my->invert = invert_mmx;
	      }
#endif
	    else
	      {
		char buffer[128];
		snprintf(buffer, sizeof(buffer),
			 "Unsupported invert routine: '%s', using 'regular' "
			 "instead",
			 my->oldRoutine.text);
		s_log(0, buffer);
		my->invert = invert;
	      }
	  }
  
    my->invert(inst->out_r->framebuffer,
               inst->in_b->framebuffer,
               inst->in_b->xsize * inst->in_b->ysize);
}

/*****************************************************************************/

static void invert(uint_32* dst_, const uint_32* src_, int size)
{
	int i;
	unsigned char* dst = (unsigned char*) dst_;
	const unsigned char* src = (const unsigned char*) src_;

    for (i = 4*(size-1); i >= 0; --i)
	{
	  *(dst++) = 255 - *(src++);
	}
}


#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void invert_mmx(uint_32* dst, const uint_32*src, int size)
{
	unsigned char masq[8];
	int _size = size*4;
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
          invert(dst + pos, src + pos, rest);
	}
}
#endif
