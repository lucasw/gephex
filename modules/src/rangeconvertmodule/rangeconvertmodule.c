#include "rangeconvertmodule.h"

#include <assert.h>

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

  double delta_in = inst->in_max_in->number - inst->in_min_in->number;
  double delta_out = inst->in_max_out->number - inst->in_min_out->number;

  double in = trim_double(inst->in_n->number, inst->in_min_in->number,
			  inst->in_max_in->number);
  double result;
  if (delta_out < 0 || delta_in < 0)
    {
      result = inst->in_n->number;
    }
  else
    {
      result = (in - inst->in_min_in->number) * (delta_out / delta_in)
	+ inst->in_min_out->number;

      /*      assert(inst->in_min_out->number <= result &&
	      result <= inst->in_max_out->number);*/
    }


  inst->out_r->number = result;
}

