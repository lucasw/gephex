#include "numbermodule.h"

#include <limits.h>

typedef struct _MyInstance {
  double lastnoise;
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
  double newnoise;
  double feedback;
  double min;
  double max;
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  feedback=trim_double(inst->in_tpf->number,0.0,1.0);
  min= inst->in_min->number;
  max= inst->in_max->number;

  newnoise=(((double)rand() / (double)RAND_MAX));
  
  my->lastnoise =((1.0-feedback)*newnoise) + (feedback)*my->lastnoise;
  if (min<max)
    {
  inst->out_r->number =min+my->lastnoise*(max-min);
    }
  else
    {
  inst->out_r->number =max+my->lastnoise*(min-max);
    }

}

