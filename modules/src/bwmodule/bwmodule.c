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

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  //MyInstancePtr my = inst->my;
  

  int xsize, ysize; 
  uint_32 *src, *dst;
  int xysize, i;

  src = (int*)inst->in_1->framebuffer;
  xsize = inst->in_1->xsize;
  ysize = inst->in_1->ysize;


  {
    FrameBufferAttributes attr;
    attr.xsize = xsize;
    attr.ysize = ysize;

    framebuffer_changeAttributes(inst->out_r, &attr);
  }

  dst = inst->out_r->framebuffer;

  xysize = xsize * ysize;

	
  for(i=xysize; --i;)
    {
      int tmpbw;
      unsigned char* tmpc = (unsigned char*)src;
      tmpbw = (tmpc[0] + tmpc[1] + tmpc[2]) / 3;
      *dst = (tmpbw << 16) | (tmpbw << 8) | tmpbw;
      ++dst;
      ++src;
    }
}

