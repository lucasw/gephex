#include "x11outmodule.h"

#include <assert.h>

#include "ximageoutput.h"
#include "xshmoutput.h"

#include "outputdriver.h"

static logT s_log;

typedef struct _MyInstance {

  struct OutputDriver* drv;
  int width;
  int height;

  StringType* server;
  StringType* driver_name;

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

  my->drv         = 0;
  my->width       = my->height = 1;

  my->server      = string_newInstance();
  my->driver_name = string_newInstance();

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
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  char buffer[128];
  int error;
  uint_32* framebuffer;

  int new_xsize, new_ysize;

  new_xsize = trim_int(inst->in_xsize->number, 0, 1024);
  new_ysize = trim_int(inst->in_ysize->number, 0, 1024);

  if ( new_xsize == 0 || new_ysize == 0)
    {
      new_xsize = inst->in_in->xsize;
      new_ysize = inst->in_in->ysize;
    }

  if (strcmp(inst->in_driver->text, my->driver_name->text) != 0
      || my->drv == 0)
    {
      string_assign(my->driver_name, inst->in_driver);

      if (my->drv != 0)
        {
          if (my->drv->inst != 0)
            my->drv->destroy(my->drv->inst);

          my->drv->inst = 0; // paranoia
          free(my->drv);
          my->drv = 0;       // paranoia
        }

      if (strcmp(inst->in_driver->text, "XImage") == 0)
        {
          my->drv = getXImageDriver();
          s_log(2, "Using XImage output driver");
        }
      else if (strcmp(inst->in_driver->text, "XShm") == 0)
        {
          my->drv = getXShmDriver();
          s_log(2, "Using XShm output driver");
        }
      else
        {
          snprintf(buffer, sizeof(buffer),
                   "Unknown driver name : '%s', using XImage driver",
                   inst->in_driver->text);

          s_log(0, buffer);
          my->drv = getXImageDriver();
        }

    }

  if (strcmp(inst->in_server->text, my->server->text) != 0 ||
      my->drv->inst == 0)
    /** initialize the driver **/
    {
      snprintf(buffer, sizeof(buffer), "Trying to connect to server '%s'...",
               inst->in_server->text);
      s_log(2, buffer);

      my->drv->inst = my->drv->new_instance(inst->in_server->text,
                                            new_xsize,
                                            new_ysize,
                                            buffer,
                                            sizeof(buffer));
      if (my->drv->inst == 0)
        {
          s_log(0, buffer);
          my->drv->destroy(my->drv->inst);
          
          free(my->drv);
          my->drv = 0;
          return;
        }

      s_log(2, "...done");
      string_assign(my->server, inst->in_server);
    }

  assert(my->drv != 0);
  assert(my->drv->inst != 0);


  if (new_xsize != my->width || new_ysize != my->height)
    {
      my->width  = new_xsize;
      my->height = new_ysize;

      if (my->drv->resize(my->drv->inst, new_xsize, new_ysize))
        return;
    }

  error = my->drv->blit(my->drv->inst,
                        (const char*) inst->in_in->framebuffer,
                        inst->in_in->xsize,
                        inst->in_in->ysize,
                        buffer, sizeof(buffer));

  if (error)
    {
      s_log(0, buffer);
    }
}
