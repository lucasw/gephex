#include "gloutmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "glutil.h" // dafuer gibts zwei implementierungen

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif

static logT s_log;

typedef struct _MyInstance {
  int width;
  int height;

  FrameBufferType* scaledFrb;
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

  my->width = 160;
  my->height = 120;
  my->scaledFrb = 0;
  
  if(!initOutput("Ge-Phex Output Window", my->width, my->height, 32))
    {
      free(my);
      s_log(0, "Could not initialize the Output window!");
      return 0; // error
    }	

  return my;
}

void destruct(MyInstance* my)
{
  shutdownOutput();

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int new_xsize, new_ysize;

  FrameBufferAttributes attribs;
  uint_32* framebuffer;

  new_xsize = trim_int(inst->in_xsize->number,0,FRAMEBUFFER_X_MAX);
  new_ysize = trim_int(inst->in_ysize->number,0,FRAMEBUFFER_Y_MAX);  

  if ( new_xsize == 0 || new_ysize == 0)
    {
      new_xsize = inst->in_in->xsize;
      new_ysize = inst->in_in->ysize;
    }

  // do not allow to small windows
  if (new_xsize<160)
    new_xsize=160;

  if (new_ysize<120)
    new_ysize=120;

  // need to resize window?
  if (new_xsize != my->width || new_ysize != my->height)
    {
      char buffer[128];
      
      snprintf(buffer, sizeof(buffer),
	       "resize window from %ix%i to %ix%i",
	       my->width, my->height, new_xsize, new_ysize);
      s_log(2, buffer);

      my->width = new_xsize;
      my->height = new_ysize;

      resizeOutput(new_xsize, new_ysize);
    }

  // need to scale input
  if (my->height != inst->in_in->ysize ||
      my->width  != inst->in_in->xsize)
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
      framebuffer = inst->in_in->framebuffer;
	  if (my->scaledFrb != 0)
	  {
		  framebuffer_deleteInstance(my->scaledFrb);
		  my->scaledFrb = 0;
	  }
    }
  
  updateOutput(framebuffer);
}
