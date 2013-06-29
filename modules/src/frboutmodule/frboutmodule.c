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
#endif

#if defined(OS_DARWIN)
#include "quartzoutput.h"
#endif

#if defined(HAVE_X11)
#include "x11output.h"
#endif

#if defined(WITH_V4L)
#include "vloopbackoutput.h"
#endif

#if defined(WITH_SDL)
#include "sdloutput.h"
#endif

#if defined(WITH_GL)
#include "gloutput.h"
#endif

#if defined (WITH_AALIB)
#include "aaoutput.h"
#endif

#include "slist.h"

//------------------------------------------------------------------------

#define TEMP_BUF_SIZE 1024

static logT s_log;

struct DriverInfo
{
  const char* name;
  struct OutputDriver* (*get_driver)();
};

static int s_mmx_supported = 0; //TODO: set correctly

#define MAX_NUM_DRIVERS 16

// array of available DriverInfos
static struct DriverInfo s_known_drivers[MAX_NUM_DRIVERS];
static int s_num_drivers = 0;

//------------------------------------------------------------------------

static struct OutputDriver* lookup_driver(const char* driver_name)
{
  struct OutputDriver* drv = 0;
  int i;
  char buffer[TEMP_BUF_SIZE] = "";

  // look for the driver
  for (i = 0; i < s_num_drivers; ++i)
    {
      struct DriverInfo* current = s_known_drivers + i;
      if (strcmp(current->name, driver_name) == 0 ||
          strcmp("default", driver_name) == 0)
        {
          snprintf(buffer, sizeof(buffer),
                   "Using %s output driver", current->name);

          drv = current->get_driver();
          s_log(2, buffer);
          break;
        }
    }

  if (drv == 0)
    {
      struct DriverInfo* dd = s_known_drivers + 0;
      
      if (s_num_drivers < 1 || dd->name == 0 || dd->get_driver == 0)
        {
          s_log(0, "error: no driver registered");
          return 0;
        }
      snprintf(buffer, sizeof(buffer),
               "Unknown driver name : '%s', using %s driver",
               driver_name, dd->name);

      s_log(0, buffer);
      drv = dd->get_driver();
    }

  if (drv == 0)
    {
      snprintf(buffer, sizeof(buffer), "getDriver() failed!");
      s_log(0, buffer);
    }

  return drv;
}

//------------------------------------------------------------------------
struct output_id
{
  char* driver_name;
  char* server_name;
};

struct output_descriptor
{
  struct OutputDriver* drv;

  struct output_id id;

  int ref_count;  
};

static slist_t s_outputs = 0;

//------------------------------------------------------------------------

static char* strcopy(const char* str)
{
  int l;
  char* r;

  if (str == 0)
    return 0;

  l = strlen(str) + 1;
  r = malloc(l);

  if (r == 0)
    return 0;

  memcpy(r, str, l);

  return r;
}

static struct output_descriptor*
output_descriptor_create(const char* driver_name,
                         const char* server_name)
{
  struct output_descriptor* od = malloc(sizeof(*od));
  od->id.driver_name           = strcopy(driver_name);
  od->id.server_name           = strcopy(server_name);
  //  printf("created '%s:%s'\n", driver_name, server_name);
  od->drv                      = 0;
  od->ref_count                = 0;

  return od;
}

static void output_descriptor_free(struct output_descriptor* od)
{
  free(od->id.driver_name);
  free(od->id.server_name);
  free(od);
}

static int output_id_equals(const struct output_id* lhs,
                            const struct output_id* rhs)
{
  if (strcmp(lhs->driver_name, rhs->driver_name) == 0 &&
      strcmp(lhs->server_name, rhs->server_name) == 0)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int id_equals(void* od_, void* closure)
{
  const struct output_descriptor* od = (const struct output_descriptor*) od_;
  const struct output_id* oid = (const struct output_id*) closure;

  return output_id_equals(&od->id, oid);
}

struct OutputDriver* output_open(const char* driver_name,
                                 const char* server_name)
{
  struct output_id id;
  slist_iterator_t it ;
  struct output_descriptor* od = 0;

  id.driver_name = (char*) driver_name;
  id.server_name = (char*) server_name;
  it = slist_find_if(s_outputs, id_equals, &id);


  if (it == slist_end(s_outputs))
    {
      /*      char buffer[TEMP_BUF_SIZE];
      snprintf(buffer, sizeof(buffer),
               "Creating new output descriptor: '%s:%s'",
               driver_name, server_name);
               s_log(2, buffer);*/

      od = output_descriptor_create(driver_name, server_name);
      slist_push_front(s_outputs, od);
    }
  else
    {
      od = (struct output_descriptor*) slist_iter_deref(it);
    }

  assert(od->ref_count >= 0);

  // create drv if necessary
  if (od->ref_count == 0)
    {
      od->drv = lookup_driver(driver_name);
    }

  // increase refcount
  if (od->drv != 0)
    {
      ++od->ref_count;
    }

  return od->drv;
}

void output_close(const char* driver_name,
                  const char* server_name)
{
  // find
  struct output_id id;
  slist_iterator_t it;
  struct output_descriptor* od = 0;

  id.driver_name = (char*) driver_name;
  id.server_name = (char*) server_name;
  it = slist_find_if(s_outputs, id_equals, &id);

  if (it == slist_end(s_outputs))
    {
      char buffer[TEMP_BUF_SIZE];
      snprintf(buffer, sizeof(buffer),
               "Trying to close invalid output: '%s:%s'",
               driver_name, server_name);
      s_log(0, buffer);
      return;
    }

  od = (struct output_descriptor*) slist_iter_deref(it);

  assert(od->ref_count >= 1);

  // delete drv and descriptor if necessary
  if (od->ref_count == 1)
    {
      struct OutputDriver* drv = od->drv;
      if (drv->inst != 0)
        {
          drv->destroy(drv->inst);
          drv->inst = 0;
        }

      free(drv);
      od->drv = 0;
    }

  // decrease refcount
  od->ref_count -= 1;
}

//------------------------------------------------------------------------

typedef struct _MyInstance {
    
  struct OutputDriver* drv;

  int        on_top;
  int        monitor;
  int        frame;

  int width;
  int height;

  StringType* server_name;
  StringType* driver_name;

  int win_xpos;
  int win_ypos;

} MyInstance, *MyInstancePtr;

//------------------------------------------------------------------------

static void insert_driver(const char* name,
			  struct OutputDriver* (*get_driver)())
{ 
  if (s_num_drivers < 0 || s_num_drivers >= MAX_NUM_DRIVERS)
    {
      s_log(0, "internal error in driver registry");
      return;
    }

  s_known_drivers[s_num_drivers].name       = name;
  s_known_drivers[s_num_drivers].get_driver = get_driver;
  ++s_num_drivers;
}

//------------------------------------------------------------------------

int init(logT log_function)
{
  char buffer[TEMP_BUF_SIZE];
	
  s_log = log_function;

  s_outputs = slist_create();

  // now init the driver info array
  // and the drivers that need it
#if defined(OS_WIN32)
  if (!GDI_init(buffer, sizeof(buffer)))
    {
      char et[TEMP_BUF_SIZE];
      snprintf(et, sizeof(et),
               "Could not init GDI driver: '%s' - skipping",
	       buffer);
      s_log(0, et);
    }
  else
    insert_driver("GDI",    GDI_get_driver);
#endif

#if defined(OS_DARWIN)
  if (!Quartz_init(buffer, sizeof(buffer)))
    {
      char et[TEMP_BUF_SIZE];
      snprintf(et, sizeof(et),
               "Could not init quartz driver: '%s' - skipping",
	       buffer);
      s_log(0, et);
    }
  else
    {
      insert_driver("quartz", Quartz_get_driver);
    }
#endif

#if defined(HAVE_X11)
  insert_driver("x11",    X11_get_driver);
#endif

#if defined(WITH_SDL)
  insert_driver("SDL",    SDL_get_driver);
#endif

#if defined(WITH_GL)
  insert_driver("GL",     GL_get_driver);
#endif

#if defined(WITH_AALIB)
  insert_driver("aalib",  AA_get_driver);
#endif

#if defined(WITH_V4L)
  insert_driver("vloopback", VLoopback_get_driver);
#endif

  if (s_num_drivers == 0)
    {
      s_log(0, "No driver found - quitting");
      return 0;
    }
  else
    {
      return 1;
    }
}

void shutDown(void)
{   
  char buffer[TEMP_BUF_SIZE];

#if defined(OS_WIN32)	
  if (!GDI_shutdown(buffer, sizeof(buffer)))
    {
      s_log(0, buffer);
    }
#endif

 {
  slist_iterator_t it = slist_begin(s_outputs);

  while (it != slist_end(s_outputs))
    {
      struct output_descriptor*
        od = (struct output_descriptor*) slist_iter_deref(it);

      output_descriptor_free(od);

      slist_iter_advance(&it);
    }
  slist_free(s_outputs);

  // TODO: why is this commented out?
  /*#if defined (WITH_GL)
    if(!GL_shutdown(buffer, sizeof(buffer)))
    {
    s_log(0, buffer);
    }
    #endif*/
 }
}

  
MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
    
  my->width       = 640;
  my->height      = 480;    
  my->on_top      = 0;
  my->monitor     = 1;
  my->frame       = 0;
    
  my->drv         = 0;
  my->server_name = string_newInstance();
  my->driver_name = string_newInstance();

  my->win_xpos    = 0;
  my->win_ypos    = 0;

  return my;
}

void destruct(MyInstance* my)
{	            
  if (my->drv != 0)
    {
      output_close(my->driver_name->text,
                   my->server_name->text);
    }
	
  string_deleteInstance(my->server_name);
  string_deleteInstance(my->driver_name);
  free(my);
}

static void get_drv_window_pos(struct OutputDriver* drv, int* xp, int* yp)
{
  if (drv->inst != 0)
    {
      if (drv->window_pos)
        {
          int xpos;
          int ypos;
	  char buffer[TEMP_BUF_SIZE] = "";		  
          if (!drv->window_pos(drv->inst, &xpos, &ypos,
                               buffer, sizeof(buffer)))
            {
              s_log(0, buffer);
            }
          else
            {
              *xp = xpos;
              *yp = ypos;
            }
        }

    }
}

void update(void* instance)
{
  InstancePtr inst      = (InstancePtr) instance;
  MyInstancePtr my      = inst->my;
  int    options        = trim_int(inst->in_options->number, 0, INT_MAX);
  int    on_top         = options & 1;
  int    frame          = options & 2;
  int    mirrorx        = options & 4;
  int    mirrory        = options & 8;
  int    invert         = options & 16;
  int    monitor        = trim_int(inst->in_monitor->number, 0, 3);
  int    win_xsize      = trim_int(inst->in_xsize->number, 0, 2048);
  int    win_ysize      = trim_int(inst->in_ysize->number, 0, 2048);
  double brightness     = trim_double(inst->in_brightness->number, 0, 1);
  double contrast       = trim_double(inst->in_contrast->number, 0, 4);
  double gamma          = trim_double(inst->in_gamma->number, 0.01, 4);
  int    fb_xsize       = inst->in_in->xsize;
  int    fb_ysize       = inst->in_in->ysize;

  int result;
  char buffer[TEMP_BUF_SIZE] = "";
  const char* driver_name = inst->in_driver->text;
  const char* server_name = inst->in_server->text;

  if (strcmp(driver_name, my->driver_name->text) != 0 ||
      strcmp(server_name, my->server_name->text) != 0 ||
      my->drv == 0)
    {  
      if (my->drv != 0)
        {
          get_drv_window_pos(my->drv, &my->win_xpos,&my->win_ypos); 

          output_close(my->driver_name->text, my->server_name->text);
          my->drv = 0;
        }

      string_assign(my->driver_name, inst->in_driver);
      string_assign(my->server_name, inst->in_server);

      my->drv = output_open(driver_name, server_name);
      if (my->drv == 0)
        return;
    }

  assert(my->drv != 0);

  if (my->drv->inst == 0)
    {
      /** initialize the driver **/
      my->drv->inst = my->drv->new_instance(server_name,
                                            my->win_xpos, my->win_ypos,
                                            my->width, my->height,
                                            s_mmx_supported,
                                            buffer, sizeof(buffer));

      if (my->drv->inst == 0)
        {
          s_log(0, buffer);
          output_close(driver_name, server_name);

          my->drv = 0;
          return;
        }
		
      // reset parameters to make sure they are initialized below
      my->frame   = -1;
      my->monitor = -1;
      my->on_top  = -1;
    }

  assert(my->drv != 0);
  assert(my->drv->inst != 0);

  if (on_top != my->on_top && my->drv->always_on_top)
    {
      int res = my->drv->always_on_top(my->drv->inst,
                                       on_top,
                                       buffer, sizeof(buffer));
      if (!res)
        s_log(0, buffer);

      my->on_top  = on_top;
    }

  if (monitor != my->monitor && my->drv->to_monitor)
    {		
      int res = my->drv->to_monitor(my->drv->inst,
                                    monitor,
                                    buffer, sizeof(buffer));
      if (!res)
        s_log(0, buffer);
		
      my->monitor = monitor;
    }

  if (win_xsize == 0 || win_ysize == 0)
    {
      win_xsize = fb_xsize;
      win_ysize = fb_ysize;
    }

  //  if (win_xsize != my->width || win_ysize != my->height)
    {        		
      int res = my->drv->resize(my->drv->inst, win_xsize, win_ysize,
                                buffer, sizeof(buffer));

      if (!res)
        {
          char msg[128];
          snprintf(msg, sizeof(msg), "Could not resize: %s", buffer);
          s_log(0, msg);
        }
		
      my->width   = win_xsize;
      my->height  = win_ysize;        
    }

  if (frame != my->frame && my->drv->frame)
    {				
      int res = my->drv->frame(my->drv->inst,
                               frame,
                               buffer, sizeof(buffer));

      if (!res)
        s_log(0, buffer);
      my->frame = frame;
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
                           (const uint8_t*) inst->in_in->framebuffer,
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
