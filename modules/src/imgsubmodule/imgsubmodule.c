#include "imgsubmodule.h"
#include <limits.h>

#include "config.h"

typedef struct _MyInstance {
	int dummy;
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
	/*my->out_result.xsize = 640;
	my->out_result.ysize = 480;
	my->out_result.framebuffer = (int*) malloc(sizeof(int) * 640*480);*/	
	return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
	//free(my->out_result.framebuffer);
	free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

	unsigned int* source1 = inst->in_input1->framebuffer;
	unsigned int* source2 = inst->in_input2->framebuffer;
	unsigned int* out_result = inst->out_result->framebuffer;

	char *src1 = (char *) source1;
	char *src2 = (char *) source2;
	char *dst = (char *) out_result;

	int in_amount = (int) ((double)inst->in_amount->number/(double)UINT_MAX * 255);
	unsigned int _size = inst->in_input1->xsize * inst->in_input1->ysize * 4;
	unsigned int i;

	unsigned char masq[8];

	for(i=0; i<8; i+=4)
	{
		masq[i] = in_amount;
		masq[i+1] = in_amount;
		masq[i+2] = in_amount;
		masq[i+3] = 0; //TODO: alpha?
	}

	//printf("amount: %d\t", inst->in_amount->number);


#if defined(COMP_VC) && defined(CPU_I386) && defined (CPU_HAS_MMX)
	_asm{
		mov esi, src1
		mov ebx, src2
		mov edi, dst
		mov eax, _size
		movq mm4, masq
		shr eax, 4
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
		emms
	}

	//TODO: aehhhh...
#elif defined(CPU_I386) && defined(CPU_HAS_MMX) && defined(COMP_GNUC)
/*
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
	      "    psubusb %%mm4, %%mm0             \n"
	      "    psubusb %%mm4, %%mm1              \n"
	      "    psubusb %%mm4, %%mm2             \n"
	      "    psubusb %%mm4, %%mm3             \n"
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
	}*/

	//irgendwie so, ich check das net...

#else
	printf("not implemented for yet!");
#endif	
  // Add your effect here!
}

