/* Framebuffer Output.
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

#include "frboutmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <stdio.h>

#include "outputdriver.h"

#if defined(OS_WIN32)
#include "gdioutput.h"
//#include "gloutput.h"
#elif defined(OS_POSIX)
#include "ximageoutput.h"
#include "xshmoutput.h"
#endif

#if defined (HAVE_AALIB_H)
#include "aaoutput.h"
#endif

#if defined(HAVE_SDL)
#include "sdloutput.h"
#endif

static logT s_log;

//------------------------------------------------------------------------

typedef struct _MyInstance {
    
  struct OutputDriver* drv;
	
  int        on_top;
  int        monitor;
  int        caption;
		
  int width;
  int height;
	
  StringType* server;
  StringType* driver_name;

  int win_xpos;
  int win_ypos;
    
} MyInstance, *MyInstancePtr;

//------------------------------------------------------------------------


int init(logT log_function)
{
  char buffer[128];
	
  s_log = log_function;    

#if defined(OS_WIN32)    
  if (!GDI_init(buffer, sizeof(buffer)))
    {	
      s_log(0, buffer);
      return 0;
    }
#endif

#if defined(HAVE_SDL)
  if (!SDL_init(buffer, sizeof(buffer)))
  {
	  s_log(0, buffer);
	  return 0;
  }
#endif

  return 1;
}

void shutDown(void)
{   
  char buffer[128];	

#if defined(OS_WIN32)	
  if (!GDI_shutdown(buffer, sizeof(buffer)))
    {
      s_log(0, buffer);
    }
#endif

#if defined(HAVE_SDL)
  if (!SDL_shutdown(buffer, sizeof(buffer)))
    {
      s_log(0, buffer);
    }
#endif
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
    
  my->width       = 640;
  my->height      = 480;    
  my->on_top      = 0;
  my->monitor     = 1;
  my->caption     = 0;
    
  my->drv         = 0;
  my->server      = string_newInstance();
  my->driver_name = string_newInstance();

  my->win_xpos    = 0;
  my->win_ypos    = 0;
  return my;
}

void destruct(MyInstance* my)
{	            
  if (my->drv != 0)
    {
      if (my->drv->inst != 0)
        my->drv->destroy(my->drv->inst);
		
      free(my->drv);
    }
	
  string_deleteInstance(my->server);
  string_deleteInstance(my->driver_name);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst	= (InstancePtr) instance;
  MyInstancePtr my	= inst->my;
  int options		= trim_int(inst->in_options->number, 0, (1u<<31)-1);
  int on_top		= options & 1;
  int monitor		= trim_int(inst->in_monitor->number, 0, 3);
  int caption		= options & 2;
  int win_xsize		= trim_int(inst->in_xsize->number, 0, 1024);
  int win_ysize		= trim_int(inst->in_ysize->number, 0, 1024);
  int fb_xsize		= inst->in_in->xsize;
  int fb_ysize		= inst->in_in->ysize;
  int mirrorx		= options & 4;
  int mirrory		= options & 8;
  double brightness = trim_double(inst->in_brightness->number, 0, 1);
  double contrast	= trim_double(inst->in_contrast->number, 0, 4);
  double gamma		= trim_double(inst->in_gamma->number, 0.01, 4);
  int    invert		= options & 16;

  int result;

  char buffer[128];

  const char* default_driver_name = "";
  struct OutputDriver* (*default_get_driver)();

  if (strcmp(inst->in_driver->text, my->driver_name->text) != 0
      || my->drv == 0)
  {
      string_assign(my->driver_name, inst->in_driver);
	  
      if (my->drv != 0)
	  {
          if (my->drv->inst != 0)
		  {			
              if (my->drv->window_pos)
			  {
                  int xpos;
                  int ypos;
				  
                  if (!my->drv->window_pos(my->drv->inst, &xpos, &ypos,
					  buffer, sizeof(buffer))) {
					  s_log(0, buffer);
                  }
                  else {
					  my->win_xpos = xpos;
					  my->win_ypos = ypos;
                  }
			  }
              my->drv->destroy(my->drv->inst);
		  }
		  
          my->drv->inst = 0; // paranoia
          free(my->drv);
          my->drv = 0;       // paranoia
	  }

#if defined(OS_WIN32)
	  default_driver_name = "GDI";
	  default_get_driver  = GDI_get_driver;
      if (strcmp(inst->in_driver->text, "default") == 0 ||
          strcmp(inst->in_driver->text, "GDI") == 0)
	  {
          my->drv = GDI_get_driver();
          s_log(2, "Using GDI output driver");
	  }	  
#elif defined(OS_POSIX)
	  default_driver_name = "XImage";
	  default_get_driver  = XImage_get_driver;
      if (strcmp(inst->in_driver->text, "default") == 0 ||
          strcmp(inst->in_driver->text, "XImage") == 0)
        {
          my->drv = XImage_get_driver();
          s_log(2, "Using XImage output driver");
        }
      else if (strcmp(inst->in_driver->text, "XShm") == 0)
        {
          my->drv = XShm_get_driver();
          s_log(2, "Using XShm output driver");
        }      
#endif
	 /*else if (strcmp(inst->in_driver->text, "GL") == 0)
	  {
          my->drv = GL_get_driver();
          s_log(2, "Using GL output driver");
	  }*/
#if defined(HAVE_AALIB_H)
      else if (strcmp(inst->in_driver->text, "aalib") == 0)
        {
          my->drv = AA_get_driver();
          s_log(2, "Using aalib output driver");
        }
#endif
#if defined(HAVE_SDL)
	  else if (strcmp(inst->in_driver->text, "SDL") == 0)
	  {
          my->drv = SDL_get_driver();
          s_log(2, "Using SDL output driver");
	  }
#endif
      else
        {
          snprintf(buffer, sizeof(buffer),
                   "Unknown driver name : '%s', using %s driver",
                   inst->in_driver->text, default_driver_name);
			
          s_log(0, buffer);
          my->drv = default_get_driver();
        }
	
  if (my->drv == 0)
      {
         snprintf(buffer, sizeof(buffer), "getDriver() failed!");
         s_log(0, buffer);
         return;
       }
  }

  assert(my->drv != 0);

  if (my->drv->inst == 0 ||
      strcmp(inst->in_server->text, my->server->text) != 0)
    /** initialize the driver **/
    {
      if (my->drv->inst != 0)
        {
          if (my->drv->window_pos)
            {
              int xpos;
              int ypos;

              if (!my->drv->window_pos(my->drv->inst, &xpos, &ypos,
                                       buffer, sizeof(buffer))) {
                s_log(0, buffer);
              }
              else {
                my->win_xpos = xpos;
                my->win_ypos = ypos;
              }
            }

          my->drv->destroy(my->drv->inst);
        }
      //snprintf(buffer, sizeof(buffer), "Trying to connect to server '%s'...",
      //inst->in_server->text);
      //s_log(2, buffer);
		
      my->drv->inst = my->drv->new_instance(inst->in_server->text,
                                            my->win_xpos, my->win_ypos,
                                            my->width,
                                            my->height,
                                            buffer,
                                            sizeof(buffer));

      if (my->drv->inst == 0)
        {
          s_log(0, buffer);          
			
          free(my->drv);
          my->drv = 0;
          return;
        }
		
      // reset parameters to make sure they are initialized below
      my->caption = -1;
      my->monitor = -1;
      my->on_top  = -1;
		
      //s_log(2, "...done");
      string_assign(my->server, inst->in_server);
    }
	
  assert(my->drv != 0);
  assert(my->drv->inst != 0);
	
	
  if (on_top != my->on_top && my->drv->always_on_top)
    {
      int res = my->drv->always_on_top(my->drv->inst, on_top, buffer, sizeof(buffer));
      if (!res)
        s_log(0, buffer);
		
      my->on_top  = on_top;
    }
	
  if (monitor != my->monitor && my->drv->to_monitor)
    {		
      int res = my->drv->to_monitor(my->drv->inst, monitor, buffer, sizeof(buffer));
      if (!res)
        s_log(0, buffer);
		
      my->monitor = monitor;
    }
    
  if (win_xsize == 0 || win_ysize == 0)
    {
      win_xsize = fb_xsize;
      win_ysize = fb_ysize;
    }
	
  if (win_xsize != my->width || win_ysize != my->height)
    {        		
      int res =my->drv->resize(my->drv->inst, win_xsize, win_ysize,
                               buffer, sizeof(buffer));
		
      if (!res) {
        char msg[128];
        snprintf(msg, sizeof(msg), "Could not resize: %s", buffer);
        s_log(0, msg);
      }
		
      my->width   = win_xsize;
      my->height  = win_ysize;        
    }
	
  if (caption != my->caption && my->drv->frame)
    {				
      int res = my->drv->frame(my->drv->inst, caption, buffer, sizeof(buffer));
		
      if (!res)
        s_log(0, buffer);
      my->caption = caption;
    }
  {
    struct blit_params params;
    params.mirrorx    = mirrorx;
    params.mirrory    = mirrory;
    params.brightness = brightness;
    params.contrast   = contrast;
    params.gamma      = gamma;
    params.invert     = invert;
    
    result = my->drv->blit(my->drv->inst,
                           (const unsigned char*) inst->in_in->framebuffer,
                           inst->in_in->xsize,
                           inst->in_in->ysize,
                           &params, 
                           buffer, sizeof(buffer));
  }

  if (!result)
  {
    s_log(0, buffer);
  }
    
    
}

//------------------------------------------------------------------------

