#include "number2colormodule.h"

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

	unsigned char r, g, b;
	unsigned int number = inst->in_number->number;


	r = (number&0x000000ff);
	g = (number&0x0000ff00)<<8;
	b = (number&0x00ff0000)<<16;


	inst->out_color->r = r;
	inst->out_color->g = g;
	inst->out_color->b = b;
 
}

