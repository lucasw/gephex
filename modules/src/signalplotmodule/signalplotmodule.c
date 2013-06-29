#include "signalplotmodule.h"

static logT s_log;

typedef struct _MyInstance {

 int x;

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

  my->x = 0;

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

static const double RANGE  = 3;
static const int    WIDTH  = 640;
static const int    HEIGHT = 480;

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  double v = trim_double(inst->in_val->number, -RANGE/2, RANGE/2);
    int x = my->x;
    int y = (int) ((RANGE/2-v) * (HEIGHT-1) / RANGE);

    FrameBufferAttributes attr;
    attr.xsize = WIDTH;
    attr.ysize = HEIGHT;
    framebuffer_changeAttributes(inst->out_r, &attr);

    my->x += 1;
    if (my->x >= 640)
      my->x = 0;

    assert(0 <= x && x < WIDTH);
    assert(0 <= y && y < HEIGHT);

    {
      uint_32* frb  = ((uint_32*) inst->out_r->framebuffer) + x;
      uint_32* ff   = frb + y*WIDTH;
      uint_32* fend = inst->out_r->framebuffer + HEIGHT*WIDTH - 1;
	  
      for (; frb < ff; frb += WIDTH)
        *frb = 0x00000000;
	  
      *ff = 0x0000ff00;
	  
      frb = ff + WIDTH;
      for (; frb < fend; frb += WIDTH)
        *frb = 0x00000000;
    }
}

