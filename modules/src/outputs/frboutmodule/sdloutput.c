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
#include <math.h>

#include "SDL.h"

#include "framebuffertype.h"

#include "libscale.h"

#define EPS 0.001

static const int SDL_VIDEO_FLAGS = SDL_HWSURFACE | SDL_DOUBLEBUF |
                                   SDL_ASYNCBLIT | SDL_ANYFORMAT;

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

static int s_instance_counter = 0;
static int s_call_sdl_quit    = 0;

//-----------------------------------------------------------------------

struct DriverInstance {

  SDL_Surface* Screen;

  int width;
  int height;

  uint_32* data;
  int data_size;

  ls_adjust_pal pal;
};

//-----------------------------------------------------------------------

static struct DriverInstance* SDL_new_instance(const char* server_name,
                                               int xpos, int ypos,
                                               int width, int height,
                                               int mmx_supported,
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

static int do_init(/*char* error_text, int text_len*/)
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
        {
          if (SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)
            {
              return 0;
            }
        }
      s_call_sdl_quit = 2;
    }
  else
    {
      s_call_sdl_quit = 1;
    }
    
  return 1;
}

static int do_shutdown(/*char* error_text, int text_len*/)
{
  if (s_call_sdl_quit == 1)
    {
      SDL_Quit();
    }
  else if (s_call_sdl_quit == 2)
    {
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
  return 1;
}


//-----------------------------------------------------------------------

static struct DriverInstance*
SDL_new_instance(const char* server_name,
                 int xpos, int ypos,
                 int width, int height, int mmx_supported,
                 char* error_text, int text_len)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));

  if (s_instance_counter == 0)
    {
      if (!do_init(/*error_text, text_len*/))
        {
          snprintf(error_text, text_len, "SDL_new_instance: "
                   "Could not initialize SDL");
          return 0;
        }
    }

  if (sh == 0)
    {
      snprintf(error_text, text_len, "SDL_new_instance: "
               "Could not allocate memory");
      return 0;
    }
  
  sh->width     = width;
  sh->height    = height;
  sh->data      = 0;
  sh->data_size = 0;

  sh->Screen = SDL_SetVideoMode(width, height, 32, SDL_VIDEO_FLAGS);
  
  if (sh->Screen == 0)
    {	  
      snprintf(error_text, text_len, "%s", SDL_GetError());
      free(sh);
      return 0;
    }  

  ++s_instance_counter;
  return sh;
}

static void SDL_destroy(struct DriverInstance* sh)
{
  if (sh->data != 0)
    {
      free(sh->data);
      sh->data      = 0;
      sh->data_size = 0;
    }
  // according to the sdl docu, the surface that is created
  // by SDL_SetVideoMode should not be freed.
  // see http://sdldoc.csn.ul.ie/sdlsetvideomode.php
  //    if (sh->Screen != 0)
  //      SDL_FreeSurface(sh->Screen);

  free(sh);
  --s_instance_counter;
  if (s_instance_counter == 0)
    do_shutdown();
}

static int SDL_resize(struct DriverInstance* sh, int width, int height,
                      char* error_text, int text_len)
{ 
  // according to the sdl docu, the surface that is created
  // by SDL_SetVideoMode does not have to be freed.
  
  if (sh->width != width || sh->height != height)
    {
      sh->Screen = SDL_SetVideoMode(width, height, 32, SDL_VIDEO_FLAGS);
  
      if (sh->Screen == 0)
        {
          snprintf(error_text, text_len, "%s", SDL_GetError());

          // try to open old screen
          sh->Screen = SDL_SetVideoMode(sh->width, sh->height,
                                        32, SDL_VIDEO_FLAGS);
          return 0;
        } 

      sh->width  = width;
      sh->height = height;
    }
  return 1;
}

static int SDL_blit_(struct DriverInstance* sh,
                     const unsigned char* fb,
                     int width, int height,
                     struct blit_params* params,
                     char* error_text, int text_len)
{
  SDL_Surface* tmp = 0;
  SDL_Surface* tmp2 = 0;
	
  uint_32* framebuffer;

  // first scale and adjust input framebuffer fb
  int needs_adjust = (fabs(params->brightness-0.5) > EPS 
                      || fabs(params->contrast-1.0) > EPS
                      || fabs(params->gamma-1.0) > EPS
                      || params->invert);

  if (sh->Screen == 0)
    return 1;

  //scale the input framebuffer
  if (width != sh->width || height != sh->height
      || params->mirrorx || params->mirrory || needs_adjust)
    {
      int size = sh->width*sh->height*4;

      if (sh->data == 0)
        {
          sh->data = malloc(size);
          sh->data_size = size;
        }
      else if (sh->data_size < size)
        {
          free(sh->data);
          sh->data = malloc(size);
          sh->data_size = size;
        }
      
      if (needs_adjust)
        {
          ls_set_adjustment(sh->pal, params->brightness, params->contrast,
                            params->gamma, params->invert);
                     
          ls_scale32m_adjust(sh->data, sh->width, sh->height,
                             (uint_32*)fb, width, height, params->mirrorx,
                             params->mirrory, sh->pal);
        }
      else
        {
          ls_scale32m(sh->data, sh->width, sh->height,
                      (uint_32*)fb, width, height, params->mirrorx,
                      params->mirrory);
        }

      framebuffer = sh->data;
    }
  else
    {
      if (sh->data != 0)
        {
          free(sh->data);
          sh->data = 0;
          sh->data_size = 0;
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

