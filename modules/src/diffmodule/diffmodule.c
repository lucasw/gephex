#include "diffmodule.h"

static logT s_log;

typedef struct _MyInstance {

  double old_d;

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

  my->old_d = 0;

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

  double d = inst->in_d->number;
  double old_d = my->old_d;

  double diff = (old_d - d);

  inst->out_r->number = diff;
  my->old_d = inst->in_d->number;
}

