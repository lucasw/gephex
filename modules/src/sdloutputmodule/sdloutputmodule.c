#include "sdloutputmodule.h"

#include <stdlib.h>

#include "SDL.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0x0000ff00
#define gmask 0x00ff0000
#define bmask 0xff000000
#define amask 0x000000ff
#else
#define rmask 0x00ff0000
#define gmask 0x0000ff00
#define bmask 0x000000ff
#define amask 0xff000000
#endif

static logT s_log;
typedef struct _MyInstance {

  SDL_Surface* Screen;

  int width;
  int height;

  FrameBufferType* scaledFrb;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;

  if(SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
      {
	if(SDL_InitSubSystem(SDL_INIT_VIDEO)==-1)
	  {
	    return 0;
	  }
      }
    else
      {
	//	atexit(SDL_QUIT);
      }
    }

  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->width = -1;
  my->height = -1;

  my->scaledFrb = 0;

  my->Screen = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFrb != 0)
    {
      framebuffer_deleteInstance(my->scaledFrb);
      my->scaledFrb = 0;
    }
  // according to the sdl docu, the surface that is created
  // by SDL_SetVideoMode does not have to be freed.
  //  if (my->Screen != 0)
  //  SDL_FreeSurface(my->Screen);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  FrameBufferAttributes attribs;

  SDL_Surface* tmp = 0;
  SDL_Surface* tmp2 = 0;

  int new_xsize, new_ysize;

  uint_32* framebuffer;

  if (inst->in_xsize->number == 0 || inst->in_ysize->number == 0)
    {
      new_xsize = inst->in_in->xsize;
      new_ysize = inst->in_in->ysize;
    }
  else
    {
      new_xsize = inst->in_xsize->number;
      new_ysize = inst->in_ysize->number;		
    }

  if (new_xsize != my->width || new_ysize != my->height || my->Screen == 0)
    {
      char buffer[128];
      // according to the sdl docu, the surface that is created
      // by SDL_SetVideoMode does not have to be freed.
      //      SDL_FreeSurface(my->Screen);
      
      snprintf(buffer, sizeof(buffer),
               "Resizing from %ix%i to %ix%i",
               my->width, my->height, new_xsize, new_ysize);
      s_log(2, buffer);

      my->width  = new_xsize;
      my->height = new_ysize;

      my->Screen = SDL_SetVideoMode(my->width, my->height,
                                    32,
				    SDL_SWSURFACE | SDL_DOUBLEBUF);

      
      if (my->Screen == 0)
	{
          char buffer[128];
	  snprintf(buffer, sizeof(buffer), "%s", SDL_GetError());
          s_log(0, buffer);
	  return;
	} 
    }

  //scale the input framebuffer
  if (inst->my->height != inst->in_in->ysize
      || inst->my->width != inst->in_in->xsize)
    {
      //input needs to be scaled
      if (my->scaledFrb == 0)
	my->scaledFrb = framebuffer_newInstance();
      
      attribs.xsize = inst->my->width;
      attribs.ysize = inst->my->height;
      
      framebuffer_convertType(my->scaledFrb, inst->in_in, &attribs);
      
      framebuffer = my->scaledFrb->framebuffer;
    }
  else
    {
      if (my->scaledFrb != 0)
	{
	  framebuffer_deleteInstance(my->scaledFrb);
	  my->scaledFrb = 0;
	}
  
      framebuffer = inst->in_in->framebuffer;
  }
  

  tmp = SDL_CreateRGBSurfaceFrom(framebuffer,
				 my->width, my->height, 32,
				 my->width*sizeof(uint_32),
				 rmask, gmask, bmask, amask);

  if (tmp == 0)
    {
      char buffer[128];
      snprintf(buffer, sizeof(buffer), "%s", SDL_GetError());
      s_log(0, buffer);
      return;
    }
  
  tmp2 = SDL_DisplayFormat(tmp);
  if (tmp2 == 0)
    {
      char buffer[128];
      snprintf(buffer, sizeof(buffer), "%s", SDL_GetError());
      s_log(0, buffer);
      SDL_FreeSurface(tmp);
      return;
    }

  SDL_BlitSurface(tmp2, NULL, my->Screen, NULL);
  SDL_Flip(my->Screen);
  
  SDL_FreeSurface(tmp2);
  SDL_FreeSurface(tmp);
}
