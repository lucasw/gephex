#include "stringtokenizermodule.h"

#include <string>
#include <sstream>
#include <vector>

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

  const char delimiter =',';

  std::string input = inst->in_string->text;
  size_t nr = trim_int(inst->in_entry->number,1,1000);

  std::istringstream ist(input);
  
  std::vector<std::string> tokens;

  std::string w;
  while (std::getline(ist,w,delimiter)) 
    tokens.push_back(w);

  if (tokens.size()<nr)
    string_charAssign(inst->out_token,"");
  else
    string_charAssign(inst->out_token,tokens[nr-1].c_str());
}

void strongDependencies(Instance* inst, int neededInputs[])
{
	// set the inputs to 0 that are not needed!
}

