#include "resultmodule.h"

typedef struct _MyInstance {

	int schrott;

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

  if(!trim_bool(inst->in_shut_up->number))
    printf("resultmodule: %g\n", inst->in_in->number);
}

