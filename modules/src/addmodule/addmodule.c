#include "addmodule.h"

typedef struct _MyInstance {
void* a;
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

  // Add your effect here!

  inst->out_r->number = inst->in_lhs->number + inst->in_rhs->number;

  // set to max
  if (inst->out_r->number<inst->in_lhs->number||inst->out_r->number<inst->in_rhs->number)
	inst->out_r->number=UINT32_MAX;


}

