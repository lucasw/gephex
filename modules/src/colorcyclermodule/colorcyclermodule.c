#include "colorcyclermodule.h"

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
  MyInstancePtr my = inst->my;
  
    inst->out_Farbe->r = (double) rand() / (double) RAND_MAX;
	inst->out_Farbe->g = (double) rand() / (double) RAND_MAX;
	inst->out_Farbe->b = (double) rand() / (double) RAND_MAX;
}

