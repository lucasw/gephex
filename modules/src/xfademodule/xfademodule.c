#include "xfademodule.h"

#include <limits.h>

typedef struct _MyInstance {

 FrameBufferType* scaledFb;

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

  my->scaledFb = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFb != 0)
	  framebuffer_deleteInstance(my->scaledFb);

  free(my);
}

void fade(int xsize, int ysize, unsigned char* framebuf1,
		  unsigned char* framebuf2, unsigned char* result, int fadeValue)
{	
      uint_32 size_ = xsize*ysize*4;
      unsigned char* end = result + (xsize*ysize)*4;      
      int negfadeValue = 255 - fadeValue;

/*#ifdef WIN32      
      char masq[8];
      char masq_neg[8];
      int i;
		
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

    _asm
	{  
		mov edi, result
	    mov esi, framebuf1
	    mov ebx, framebuf2
	    mov eax, size_
	    shr eax, 3
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
	    emms
				
	    }
			
#endif
#ifdef LINUX*/
		
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
	  
      
//#endif
}


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
	
  if (inst->in_x->number == 0 || inst->in_x->number == UINT32_MAX)
    {
      //no need to do anything because the inputs are patched directly to the outputs.
	  return;
    }
  else
    {
	  unsigned char* fb1 = 0;
	  unsigned char* fb2 = 0;
	  int didScale = 0;

	  int xsize = 0, ysize = 0;
	  int fadeValue = (int) (((double)inst->in_x->number/(double)UINT32_MAX)*255);

	  if (inst->in_1->xsize != inst->in_2->xsize || inst->in_1->ysize != inst->in_2->ysize)
	  {
		  if (my->scaledFb == 0)
			my->scaledFb = framebuffer_newInstance();

		  didScale = 1;

		  if (inst->in_1->xsize * inst->in_1->ysize > inst->in_2->xsize * inst->in_2->ysize)
		  {
			  fb1 = (unsigned char*) inst->in_1->framebuffer;		  
			  xsize = inst->in_1->xsize;
			  ysize = inst->in_1->ysize;

			  framebuffer_scale(my->scaledFb,inst->in_2,xsize, ysize);
			  fb2 = (unsigned char*) my->scaledFb->framebuffer;
		  }
		  else
		  {
			  fb2 = (unsigned char*) inst->in_2->framebuffer;
			  xsize = inst->in_2->xsize;
			  ysize = inst->in_2->ysize;

			  framebuffer_scale(my->scaledFb,inst->in_1,xsize, ysize);
			  fb1 = (unsigned char*) my->scaledFb->framebuffer;
		  }
	  }
	  else
	  {
		  fb1 = (unsigned char*) inst->in_1->framebuffer;
		  fb2 = (unsigned char*) inst->in_2->framebuffer;
		  xsize = inst->in_1->xsize;
		  ysize = inst->in_1->ysize;		  
	  }

	 
	  {
		FrameBufferAttributes attribs;
		
		attribs.xsize = xsize;
		attribs.ysize = ysize;
		framebuffer_changeAttributes(inst->out_r, &attribs);
	  }


	  fade(xsize, ysize, fb1, fb2, (unsigned char*) inst->out_r->framebuffer, fadeValue);
      
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
  if (inst->in_x->number == 0)
    neededInputs[in_2] = 0;
  else if (inst->in_x->number == UINT32_MAX)
    neededInputs[in_1] = 0;
}

void patchLayout(Instance* inst, int out2in[])
{
  if (inst->in_x->number == 0)
    out2in[out_r] = in_1;
  else if (inst->in_x->number == UINT32_MAX)
    out2in[out_r] = in_2;
}
