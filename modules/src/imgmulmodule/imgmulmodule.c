#include "imgmulmodule.h"
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
  return my;
}

void destruct(MyInstance* my)
{
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

	unsigned char in_amount = (int) ((double)inst->in_amount->number/(double)UINT_MAX * 255);

	unsigned int _size = inst->in_input1->xsize * inst->in_input1->ysize * 4;
	unsigned int i;

	unsigned char masq[8];
	unsigned char masq_neg[8];
	unsigned char zero[8];

	for(i=0; i<8; i+=4)
	{
		masq[i] = in_amount;
		masq[i+1] = in_amount;
		masq[i+2] = in_amount;
		masq[i+3] = 0; //TODO: alpha?
		//masq[i+3] = in_amount;

		zero[i] = 0;
		zero[i+1] = 0;
		zero[i+2] = 0;
		zero[i+3] = 0;

		
		masq_neg[i] = 255-in_amount;
		masq_neg[i+1] = 255-in_amount;
		masq_neg[i+2] = 255- in_amount;
		masq_neg[i+3] = 0;
		//masq_neg[i+3] = 255-in_amount;
	}


#if defined(COMP_VC) && defined(CPU_I386) && defined (CPU_HAS_MMX)
	_asm{
		mov esi, src1
		mov ebx, src2
		mov edi, dst
		mov eax, _size
		movq mm5, zero
		shr eax, 3
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
		emms
	}

	//TODO: aehhhh...
#else
	printf("not implemented for yet!");
#endif	
}

