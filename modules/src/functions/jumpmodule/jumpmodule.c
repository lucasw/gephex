#include "jumpmodule.h"

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
  //MyInstancePtr my = inst->my;

  // Add your effect here!
  unsigned int input = inst->in_in->number;
  unsigned int thr = inst->in_thr->number;
  unsigned int lowval = inst->in_lower->number;
  unsigned int highval = inst->in_upper->number;
  
  if (input > thr)
    {
      inst->out_r->number = highval;
    } 
  else
    {
      inst->out_r->number = lowval;
    }
}

