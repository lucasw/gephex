#include "effectvpuzzlemodule.h"

static logT s_log;

#include "libeffectv.h"
#include "sdldummy.h"
#include "puzzle.c"

typedef struct _MyInstance {
  struct effectv_Effect* effect;
  int left, right, up, down;
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

  my->left = my->right = my->up = my->down = 0;
  my->effect = effectv_init(puzzleRegister, 0, 0);

  if (my->effect)
    return my;
  else
    {
      free (my);
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

  int left  = trim_bool(inst->in_left->number);
  int right = trim_bool(inst->in_right->number);
  int up    = trim_bool(inst->in_up->number);
  int down  = trim_bool(inst->in_down->number);

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r, &attribs);

  if (left != my->left)
    {
      SDL_Event event;

      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_a;
      puzzleEvent(&event);
    }

  if (right != my->right)
    {
      SDL_Event event;

      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_d;
      puzzleEvent(&event);
    }

  if (up != my->up)
    {
      SDL_Event event;

      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_w;
      puzzleEvent(&event);
    }

  if (down != my->down)
    {
      SDL_Event event;

      event.type = SDL_KEYDOWN;
      event.key.keysym.sym = SDLK_s;
      puzzleEvent(&event);
    }

  effectv_draw(my->effect,
               (unsigned char*) inst->in_b->framebuffer,
	       (unsigned char*) inst->out_r->framebuffer,
	       xsize, ysize);
}

