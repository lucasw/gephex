#include "numxfadermodule.h"

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

  if (inst->in_x->number == 0)
    inst->out_r->number = inst->in_1->number;
  else if (inst->in_x->number == UINT32_MAX)
    inst->out_r->number = inst->in_2->number;
  else
    {
      double val1 = inst->in_1->number;
      double val2 = inst->in_2->number;
      double fader = (double)inst->in_x->number / UINT32_MAX;
      inst->out_r->number = (val2 * fader) + (val1 * (1.0 - fader));
    }
}

void strongDependencies(Instance* inst, int neededInputs[])
{  
  if (inst->in_x->number == 0)
    neededInputs[in_2] = 0;
  else if (inst->in_x->number == UINT32_MAX)
    neededInputs[in_1] = 0;
}
