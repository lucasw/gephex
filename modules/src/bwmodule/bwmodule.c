#include "bwmodule.h"

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
  //MyInstancePtr my = inst->my;

  // Add your effect here!

  int xsize, ysize; 
  int *src, *dst;
  int xysize, i;

  src = (int*)inst->in_1->framebuffer;
  xsize = inst->out_r->xsize;
  ysize = inst->out_r->ysize;
  dst = inst->out_r->framebuffer;

  xysize = xsize * ysize;

	
  for(i=xysize; --i;)
    {
      int tmpbw;
      char* tmpc = (char*)src;
      tmpbw = (tmpc[0] + tmpc[1] + tmpc[2]) / 3;
      *dst = (tmpbw << 16) | (tmpbw << 8) | tmpbw;
      ++dst;
      ++src;
    }
}

