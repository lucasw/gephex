#include "flipflopmodule.h"

static logT s_log;

typedef struct _MyInstance {

  double old_clk;
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

  my->old_clk = 0;
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
  double clk = inst->in_clk->number;
  double tol = inst->in_tol->number;

  if (clk > my->old_clk && clk - my->old_clk > tol)
    {
      my->old_d = inst->in_d->number;
    }

  inst->out_r->number = my->old_d;
  my->old_clk = clk;
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  double tol     = inst->in_tol->number;
  double clk     = inst->in_clk->number;
  double old_clk = inst->my->old_clk;
  if (clk <= old_clk || clk - old_clk <= tol)
    neededInputs[in_d] = 0;
}

