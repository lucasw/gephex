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

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;

	inst->out_color->r = (float) inst->in_r->number;
	inst->out_color->g = (float) inst->in_g->number;
	inst->out_color->b = (float) inst->in_b->number; 
}
