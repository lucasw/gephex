#include "oscmergemodule.h"

#include<algorithm>
#include<vector>

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

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

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

  assert( osc_invariant(inst->in_1) );
  assert( osc_invariant(inst->in_2) );

  std::vector<unsigned char> data;
  data.reserve(inst->in_1->len + inst->in_2->len); // optimization
  
  std::copy(inst->in_1->data,
	    inst->in_1->data+inst->in_1->len,
	    std::back_inserter(data));
  
  std::copy(inst->in_2->data,
	    inst->in_2->data+inst->in_2->len,
	    std::back_inserter(data));

  osc_resize( inst->out_r , data.size() );
  inst->out_r->len = data.size() ;

  std::copy(data.begin(),data.end(),inst->out_r->data);

  assert( osc_invariant(inst->out_r) );
}
