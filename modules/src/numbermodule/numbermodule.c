#include "numbermodule.h"

#include <limits.h>

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
  inst->out_r->number = (unsigned int) ((double) UINT_MAX * ((double) rand() / (double)  RAND_MAX));	

}

