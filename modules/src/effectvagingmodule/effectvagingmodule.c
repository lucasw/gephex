#include "effectvagingmodule.h"

static logT s_log;

#include "libeffectv.h"
#include "aging.c"

typedef struct _MyInstance {
  struct effectv_Effect* effect;
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

  my->effect = effectv_init(agingRegister, 0, 0);

  if (my->effect)
    return my;
  else
    {
      free(my);
      return 0;
    }
  return my;
}

void destruct(MyInstance* my)
{
  effectv_teardown(my->effect);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  FrameBufferAttributes attribs;
  int xsize = inst->in_b->xsize;
  int ysize = inst->in_b->ysize;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  effectv_draw(my->effect,
               inst->in_b->framebuffer,
	       inst->out_r->framebuffer,
	       xsize, ysize);
}

