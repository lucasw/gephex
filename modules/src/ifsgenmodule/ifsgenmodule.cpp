#include "ifsgenmodule.h"
#include <cassert>

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
  
  inst->out_ifs->numfun = trim_int(inst->in_num_fun->number,2,IFS_MAX_FUN);
  
  // initialize with random
  for(int funNr = 0;funNr!=inst->out_ifs->numfun;++funNr)
    {
      for(int q=0;q!=6;++q)
	{
	  inst->out_ifs->ifs[q][funNr]=1.0*(0.5- (static_cast<double>(rand())/RAND_MAX) );
	}
    }
}

