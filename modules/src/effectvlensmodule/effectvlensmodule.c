#include "effectvlensmodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#define init initLENSLENSLENS
#include "lens.c"
#undef init

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

  my->effect = effectv_init(lensRegister, 0, 0);

  if (my->effect)
    return my;
  else
    {
      free(my);
      return 0;
    }
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

  int size = trim_int(inst->in_size->number, 10, 500);
  int xpos = (int) (trim_double(inst->in_pos->x, 0, 1) * (xsize-size));
  int ypos = (int) (trim_double(inst->in_pos->y, 0, 1) * (ysize-size));
  int interactive = trim_bool(inst->in_interactive->number);
  int mag = trim_int(inst->in_mag->number, 5, 200);

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (size != lens_width)
    {
      SDL_Event event;

      event.type = SDL_MOUSEMOTION;
      event.button.button = SDL_BUTTON_LEFT;
      event.motion.yrel = -lens_width + size;

      lensEvent(&event);
    }

  if (xpos != x || ypos != y)
    {
      SDL_Event event;

      event.type = SDL_MOUSEMOTION;
      event.button.button = 0;
      event.motion.xrel = -x + xpos;
      event.motion.yrel = -y + ypos;

      lensEvent(&event);
    }

  if (mag != lens_zoom)
    {
      SDL_Event event;

      event.type = SDL_MOUSEMOTION;
      event.button.button = 2;
      event.motion.yrel = -lens_zoom + mag;

      lensEvent(&event);

      //      printf("lens_zoom = %i\t mag = %i\n", lens_zoom, mag);
    }

  if (interactive != mode)
    {
      SDL_Event event;

      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_SPACE;

      lensEvent(&event);
    }

  /*  if (inst->in_bg->number != my->old_bg)
    {
      SDL_Event event;
      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_SPACE;

      fireEvent(&event);

      my->old_bg = inst->in_bg->number;
      }*/

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

