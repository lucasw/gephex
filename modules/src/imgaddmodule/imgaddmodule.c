#include "imgaddmodule.h"

#include <limits.h>

#include "config.h"

typedef struct _MyInstance {
int dummy;
}MyInstance, *MyInstancePtr;

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
  // Add your cleanup here
	
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

	//TODO: kleineres bild nehmen, in_amount mit rein
	unsigned int _size = inst->in_input1->xsize * inst->in_input1->ysize * 4;
	//unsigned int align = _size % 64;
	unsigned int i;

	/*for(i=0; i<_size; i+= 4)
	{
		*dst++ = ((*src1++)+ (int)((*src2++)*in_amount))%255;
		*dst++ = ((*src1++)+ (int)((*src2++)*in_amount))%255;
		*dst++ = ((*src1++)+ (int)((*src2++)*in_amount))%255;
		*dst++ = ((*src1++)+ (int)((*src2++)*in_amount))%255;
	}*/

	unsigned char masq[8];

	for(i=0; i<8; i+=4)
	{
		masq[i] = in_amount;
		masq[i+1] = in_amount;
		masq[i+2] = in_amount;
		masq[i+3] = 0; //TODO: alpha?
	}


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
			paddusb mm0, mm2 
			paddusb mm1, mm3
			movq [edi], mm0
			movq [edi+8], mm1
			add esi, 16
			add ebx, 16
			add edi, 16
			dec eax
		jnz inst_loop
		emms
	}

#else
	printf("not implemented for yet!");
#endif	

}

