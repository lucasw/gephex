#include "flashmodule.h"

#define ATTACK 3
#define SUSTAIN 2
#define DECAY 10

#define MAX_COUNT (ATTACK + DECAY + SUSTAIN)

typedef struct _MyInstance {

 int counter;

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

  my->counter = 0;

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

  int trigger = inst->in_trigger->number;  

  FrameBufferAttributes attribs;

  int fadeValue;
  int negfadeValue;
  int xsize = inst->in_src->xsize;
  int ysize = inst->in_src->ysize;
  int c;

  if (trigger == 0 && my->counter == 0)
  {
	  return;
  }

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (trigger != 0 && my->counter == 0)
  {
	  my->counter = MAX_COUNT;
  }


  c = MAX_COUNT - my->counter;

  if (c <= ATTACK)
  {

	  fadeValue = (int) ((255.* c)
			/ (double) (ATTACK));
      negfadeValue = 255 - fadeValue;
  }
  else if (c <= ATTACK + SUSTAIN)
  {
	  fadeValue = 255;
	  negfadeValue = 0;
  }
  else
  {
	fadeValue = (int) ((255.* my->counter)/ (double) (DECAY));
      negfadeValue = 255 - fadeValue;
  }
  

  fadeValue *= 255;

  {
	unsigned char* result    = (unsigned char*) inst->out_r->framebuffer;
	unsigned char* framebuf1 = (unsigned char*) inst->in_src->framebuffer;
    unsigned char* end	     = result + (xsize*ysize-1)*4;
    
		
      while (result != end)
	  {
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  ++framebuf1;
		  ++result;
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  ++framebuf1;
		  ++result;
		  *result = (fadeValue + *framebuf1*negfadeValue)>>8;
		  
		  framebuf1 += 2; 
		  result += 2;
	  }
  }

  my->counter = my->counter - 1;
	  
}

void patchLayout(Instance* inst, int out2in[])
{
   int trigger = inst->in_trigger->number;

   if (trigger == 0 && inst->my->counter == 0)
   {
	   out2in[out_r] = in_src;
   }
}

