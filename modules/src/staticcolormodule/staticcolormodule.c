#include "staticcolormodule.h"

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
  attribs.xsize = inst->in_xsize->number;
  attribs.ysize = inst->in_ysize->number;
  framebuffer_changeAttributes(inst->out_r, &attribs);
  
  {
  int i;
  unsigned char color[8];
  unsigned char* dst = (unsigned char*)inst->out_r->framebuffer;
  int size_ = inst->out_r->xsize*inst->out_r->ysize*4;
  
  static int oldColor = 0;

  for(i=0; i<8; i+=4)
	{
		color[i] = (unsigned char)(inst->in_col->r*255);
		color[i+1] = (unsigned char)(inst->in_col->g*255);
		color[i+2] = (unsigned char)(inst->in_col->b*255);
		color[i+3] = 0; //TODO: alpha?
	}

	if (oldColor == *((int*) color))
	  return;

	oldColor = *((int*) color);

#if defined(COMP_VC) && defined(CPU_I386) && defined (CPU_HAS_MMX)

	_asm
	{
		mov edi, dst
		mov eax, size_
		shr eax, 5
		movq mm1, [color]
		loop_1:
			movq [edi], mm1
			movq [edi+8], mm1
			movq [edi+16], mm1
			movq [edi+24], mm1
			add edi, 32
			dec eax
		jnz loop_1
		emms
	}	

#else
	{
		unsigned char* pointer = 0;
		for (pointer = dst + size_ - 4; pointer >= dst; pointer -= 4)
		{
			*((int*) pointer) = *((int*) color);
		}
	}
	

#endif
  }
}

