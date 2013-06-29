#include "numoscmodule.h"

#include<algorithm>
#include<cstring>

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

  const size_t size_len = sizeof(unsigned int);
  const size_t ttag_len = 4;
  const size_t value_len = sizeof(float);
    
  const char* address = inst->in_address->text;
  size_t address_len = strlen(inst->in_address->text);

  size_t pad_len = 4 - (address_len % 4);

  assert( (address_len + pad_len) % 4 == 0);

  const unsigned int p_len = address_len + pad_len + ttag_len + value_len;
    
  osc_resize( inst->out_r , p_len + size_len );
  inst->out_r->len = p_len + size_len;
  // push length
  std::copy(reinterpret_cast<const unsigned char*>(&p_len),
	    reinterpret_cast<const unsigned char*>(&p_len)+size_len,
	    inst->out_r->data);
    
  // push address
  std::copy(address, address+address_len, inst->out_r->data + size_len);
  std::fill(inst->out_r->data + size_len + address_len,
	    inst->out_r->data + size_len + address_len + pad_len,
	    0);
  
  // push type tag for float ",f"
  unsigned char ttag[] = {',','f','\0','\0'};
  
  std::copy(ttag, ttag+ ttag_len,
	    inst->out_r->data + size_len + address_len + pad_len);
  
  // push float value
  float value = static_cast<float>(inst->in_value->number);
  std::copy(reinterpret_cast<char*>(&value),
	    reinterpret_cast<char*>(&value) + 4,
	    inst->out_r->data + size_len + address_len + pad_len + 4 );

  assert (osc_invariant(inst->out_r) );
}

