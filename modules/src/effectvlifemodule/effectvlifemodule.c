#include "effectvlifemodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "life.c"

typedef struct _MyInstance {

  struct effectv_Effect* effect;

  double old_bg;

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

  my->old_bg = 0;

  my->effect = effectv_init(lifeRegister, 0, 0);

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

  if (inst->in_bg->number != my->old_bg)
    {
      SDL_Event event;
      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_SPACE;

      lifeEvent(&event);

      my->old_bg = inst->in_bg->number;
    }

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

