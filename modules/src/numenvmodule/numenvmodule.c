#include "numenvmodule.h"

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
  inst->out_result->amount = trim_double(inst->in_amount->number,0,1);
  inst->out_result->attack = trim_double(inst->in_attack->number,0,1);
  inst->out_result->decay = trim_double(inst->in_decay->number,0,1);
  inst->out_result->sustain_level = trim_double(inst->in_sustain_level->number,0,1);
  inst->out_result->release = trim_double(inst->in_release->number,0,1);

}


