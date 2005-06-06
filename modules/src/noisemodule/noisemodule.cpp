#include "noisemodule.h"

#include "crandgen.h"

#include<algorithm>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

uint32_t mono_noise()
{
  uint8_t color[4];
  uint8_t tmp = rnd_lcg1() >> 24;
  color[0] = tmp;
  color[1] = tmp;
  color[2] = tmp;
  color[3] = 0;
  return *reinterpret_cast<uint32_t*>(&color);
}

uint32_t chroma_noise()
{
  uint8_t color[4];
  color[0] = rnd_lcg1() >> 24;
  color[1] = rnd_lcg1() >> 24;
  color[2] = rnd_lcg1() >> 24;
  color[3] = 0;
  return *reinterpret_cast<uint32_t*>(&color);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // resize output
  int xsize = trim_int(inst->in_outx->number, 1, 1024);
  int ysize = trim_int(inst->in_outy->number, 1, 1024);
  {
    FrameBufferAttributes attr;
    attr.xsize = xsize;
    attr.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attr);
  }
  // for_each pixel set random
  if (trim_bool(inst->in_monochrom->number))
    std::generate_n(inst->out_r->data, xsize*ysize, mono_noise);
  else
    std::generate_n(inst->out_r->data, xsize*ysize, chroma_noise);
}

