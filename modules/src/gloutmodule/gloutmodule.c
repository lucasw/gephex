#include "gloutmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "glutil.h" // dafuer gibts zwei implementierungen


typedef struct _MyInstance {
  int width;
  int height;

  FrameBufferType* scaledFrb;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->width = 640;
  my->height = 480;

  my->scaledFrb = 0;

  if(!initOutput("Ge-Phex Output Window", my->width, my->height, 32))
    {
      free(my);
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

  if (new_xsize != my->width || new_ysize != my->height)
    {
      printf("GL Output: Changing from %ix%i to %ix%i\n",
	     my->width, my->height, new_xsize, new_ysize);

      my->width = new_xsize;
      my->height = new_ysize;

      resizeOutput(new_xsize, new_ysize);
    }

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

  updateOutput(framebuffer);
}
