#include "submodule.h"

typedef struct _MyInstance {

 int dummy;

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

  if (inst->in_lhs->number < inst->in_rhs->number)
    inst->out_r->number = 0;
  else
    inst->out_r->number = inst->in_lhs->number - inst->in_rhs->number;
}

