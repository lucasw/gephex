#include "color2numbermodule.h"

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

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
  MyInstancePtr my = inst->my;

  unsigned char r,g,b;
  unsigned int color;
	r = (unsigned char)inst->in_color->r*255;
	g = (unsigned char)inst->in_color->g*255;
	b = (unsigned char)inst->in_color->b*255;

	color = (b>>24)|(g>>8)|r;

	inst->out_number->number = color; 
}

