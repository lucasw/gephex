/* SDL Output driver.
  Copyright (C) 2003 Georg Seidel
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/
#include "sdloutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "SDL.h"

#include "framebuffertype.h"

static const int SDL_VIDEO_FLAGS = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT | SDL_ANYFORMAT;

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

#include "outputdriver.h"

//static const char* classname = "GE-PHEX_SDL_OUTPUT_WINDOW";

//-----------------------------------------------------------------------

struct DriverInstance {

  SDL_Surface* Screen;

  int width;
  int height;

  FrameBufferType* scaledFrb;
};

//-----------------------------------------------------------------------

static struct DriverInstance* SDL_new_instance(const char* server_name,
											   int xpos, int ypos,
											   int width, int height,
											   char* error_text, int buflen);

static void SDL_destroy(struct DriverInstance* sh);

static int SDL_resize(struct DriverInstance* sh,int width, int height,
		  		      char* error_text, int text_len);

static int SDL_blit_(struct DriverInstance* sh,
                    const unsigned char* fb, int width, int height,
					struct blit_params* params,
                    char* error_text, int buflen);

//-----------------------------------------------------------------------

struct OutputDriver* SDL_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->new_instance  = SDL_new_instance;
  drv->destroy       = SDL_destroy;
  drv->resize        = SDL_resize;
  drv->blit          = SDL_blit_;
  drv->window_pos    = 0;
  drv->frame         = 0;
  drv->always_on_top = 0;
  drv->to_monitor    = 0;

  drv->inst          = 0;
  return drv;
}

int SDL_init(char* error_text, int text_len)
{
    if((SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO) == 0)
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

int SDL_shutdown(char* error_text, int text_len)
{   
	//TODO: deinit SDL?
	return 1;
}


//-----------------------------------------------------------------------

static struct DriverInstance*
SDL_new_instance(const char* server_name,
				 int xpos, int ypos,
                 int width, int height,
                 char* error_text, int text_len)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));

  if (sh == 0)
  {
	  snprintf(error_text, text_len, "SDL_new_instance: Could not allocate memory");
	  return 0;
  }
  
  sh->width     = width;
  sh->height    = height;
  sh->scaledFrb = 0;

  sh->Screen = SDL_SetVideoMode(width, height,  32,	SDL_VIDEO_FLAGS);
  
  if (sh->Screen == 0)
  {	  
	  snprintf(error_text, text_len, "%s", SDL_GetError());
	  free(sh);
	  return 0;
  }  

  return sh;
}

static void SDL_destroy(struct DriverInstance* sh)
{
  if (sh->scaledFrb != 0)
    {
      framebuffer_deleteInstance(sh->scaledFrb);
      sh->scaledFrb = 0;
    }
  // according to the sdl docu, the surface that is created
  // by SDL_SetVideoMode should not be freed.
  // see http://sdldoc.csn.ul.ie/sdlsetvideomode.php
  //  if (sh->Screen != 0)
  //    SDL_FreeSurface(sh->Screen);

  free(sh);
}

static int SDL_resize(struct DriverInstance* sh, int width, int height,
                      char* error_text, int text_len)
{ 

  sh->width  = width;
  sh->height = height;

  // according to the sdl docu, the surface that is created
  // by SDL_SetVideoMode does not have to be freed.
  
  sh->Screen = SDL_SetVideoMode(width, height,  32,	SDL_VIDEO_FLAGS);
  
  if (sh->Screen == 0)
  {	  
	  snprintf(error_text, text_len, "%s", SDL_GetError());
	  free(sh);
	  return 0;
  } 

  return 1;
}

static int SDL_blit_(struct DriverInstance* sh,
                    const unsigned char* fb,
                    int width, int height,
					struct blit_params* params,
                    char* error_text, int text_len)
{
	FrameBufferAttributes attribs;
	
	SDL_Surface* tmp = 0;
	SDL_Surface* tmp2 = 0;
	
	uint_32* framebuffer;
	FrameBufferType in_in;
	in_in.data = (int_32*) fb;
	in_in.framebuffer = (int_32*) fb;
	in_in.xsize = width;
	in_in.ysize = height;
	in_in.size  = width*height*4;
	
	
	//scale the input framebuffer
	if (sh->height != height
		|| sh->width != width)
    {
		//input needs to be scaled
		if (sh->scaledFrb == 0)
			sh->scaledFrb = framebuffer_newInstance();
		
		attribs.xsize = sh->width;
		attribs.ysize = sh->height;
		
		framebuffer_convertType(sh->scaledFrb, &in_in, &attribs);
		
		framebuffer = sh->scaledFrb->framebuffer;
    }
	else
    {
		if (sh->scaledFrb != 0)
		{
			framebuffer_deleteInstance(sh->scaledFrb);
			sh->scaledFrb = 0;
		}
		
		framebuffer = (int_32*) fb;
	}
	

  tmp = SDL_CreateRGBSurfaceFrom(framebuffer,
				 sh->width, sh->height, 32,
				 sh->width*sizeof(uint_32),
				 rmask, gmask, bmask, amask);

  if (tmp == 0)
    {      
      snprintf(error_text, text_len, "%s", SDL_GetError());
      return 0;
    }
  
  tmp2 = SDL_DisplayFormat(tmp);
  if (tmp2 == 0)
    {      
      snprintf(error_text, text_len, "%s", SDL_GetError());
      return 0;
    }

  SDL_BlitSurface(tmp2, NULL, sh->Screen, NULL);
  SDL_Flip(sh->Screen);
  
  SDL_FreeSurface(tmp2);
  SDL_FreeSurface(tmp);
  
	return 1;
}

//-----------------------------------------------------------------------

