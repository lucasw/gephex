#include "centermodule.h"

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

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

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  // Add your effect here!
  int xsize, ysize; 
  int x,y; 

  double v_acc, x_acc, y_acc;

  uint_32 *src;
  src = (int*)inst->in_1->framebuffer;

  xsize = inst->in_1->xsize;
  ysize = inst->in_1->ysize;

  x_acc=0;
  y_acc=0;
  v_acc=0;

  for (y=0; y != ysize; ++y)
    for (x=0; x != xsize; ++x)
      {
	double tmpbw;
	unsigned char* tmpc = (unsigned char*)(src+x+y*xsize);
	tmpbw = (double)(tmpc[0] + tmpc[1] + tmpc[2]);

	x_acc += x * tmpbw;
	y_acc += y * tmpbw;
	v_acc += tmpbw;
      }

  if (v_acc==0)
    {
      inst->out_r->x= 0.5;
      inst->out_r->y= 0.5;
    }
  else
    {
      inst->out_r->x= 1.0-(x_acc / (v_acc*(double)xsize));
      inst->out_r->y= 1.0-(y_acc / (v_acc*(double)ysize));
    }
}

