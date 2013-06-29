#include "oscnummodule.h"

#include <string>

static logT s_log;

typedef struct _MyInstance {

 float value; 

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

  my->value=0.0;

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

  assert ( osc_invariant(inst->in_osc) );
  
  char* pos = reinterpret_cast<char*>(inst->in_osc->data);
  size_t len = inst->in_osc->len;

  while (len > 0)
    {
      assert( len >=4 );
      unsigned int p_len = *reinterpret_cast<unsigned int*>(pos);
      pos += 4;
      len -= 4;
      
      assert (len >= p_len );
      assert (p_len % 4 == 0);

      {
	char* p_pos=pos;

	std::string address(p_pos);
	p_pos += address.size()+ 4 - (address.size() % 4);

	if (address == std::string(inst->in_address->text))
	  {
	    std::string type_tag(p_pos);
	    p_pos += type_tag.size()+ 4 - (type_tag.size() % 4);
	    if (type_tag == std::string(",f"))
	      {
		// get float value
		std::copy(p_pos, p_pos+4, reinterpret_cast<char*>(&inst->my->value));
	      }
	  }
      }
      
      pos += p_len;
      len -= p_len;
    }

  inst->out_num->number=inst->my->value;
  
  assert( len == 0 );
}

