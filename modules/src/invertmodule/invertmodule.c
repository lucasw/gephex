#include "invertmodule.h"

#include <stdio.h>

#include "config.h"

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

   FrameBufferAttributes attribs;
	  
	  framebuffer_getAttributes(inst->in_b, &attribs);
	  framebuffer_changeAttributes(inst->out_r, &attribs);
  
	  {
		  unsigned int* source = inst->in_b->framebuffer;
		  unsigned int* result = inst->out_r->framebuffer;
		  
		  char *src = (char *) source;
		  char *dst = (char *) result;
		  
		  int i;
		  
		  unsigned int _size = inst->in_b->xsize * inst->in_b->ysize * 4;
		  //unsigned int align = _size % 64;
		  
		  unsigned char masq[8];
		  
		  for (i = 0; i < 8; i+=4)
		  {
			  masq[i] = 255;
			  masq[i+1] = 255;
			  masq[i+2] = 255;
			  masq[i+3] = 0;
		  }
		  
		  
#if defined(COMP_VC) && defined(CPU_I386) && defined (CPU_HAS_MMX)
		  _asm{
			  mov esi, src
				  mov edi, dst
				  mov eax, _size
				  shr eax, 5
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
		  }
	  
#elif defined(COMP_GNUC) && defined(CPU_I386) && defined (CPU_HAS_MMX)
		  {
			  unsigned char* masqPtr = masq;
			  
			  asm(
				  "movq (%0),%%mm4                      \n"
				  "movl %1,%%esi                        \n"
				  "movl %2,%%edi                        \n"
				  "shr $5,%%eax                         \n"
				  "1:                                   \n"
				  "    movq (%%esi), %%mm0              \n"
				  "    movq 8(%%esi), %%mm1             \n"
				  "    movq 16(%%esi),%%mm2             \n"
				  "    movq 24(%%esi), %%mm3            \n"
				  "    pxor %%mm4, %%mm0                \n"
				  "    pxor %%mm4, %%mm1                \n"
				  "    pxor %%mm4, %%mm2                \n"
				  "    pxor %%mm4, %%mm3                \n"
				  "    movq %%mm0, (%%edi)              \n"
				  "    movq %%mm1, 8(%%edi)             \n"
				  "    movq %%mm2, 16(%%edi)            \n"
				  "    movq %%mm3, 24(%%edi)            \n"
				  "    addl $32, %%esi                  \n"
				  "    addl $32, %%edi                  \n"
				  "    decl %%eax                       \n"
				  "jnz 1b                               \n"
				  "emms                                 \n"
				  :
			  : "r"(masqPtr), "m" (src), "m"(dst), "a" (_size)
				  );
		  }
#else
	printf("not implemented for yet!");
#endif	
	  }
}
