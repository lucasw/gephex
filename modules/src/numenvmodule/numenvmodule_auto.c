#include "numenvmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "numenvmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_num2env", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_num2env] number_of_inputs=[5] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1.0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.01 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.01 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1.0 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.0 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_EnvType } ";
  break;
 }
 return 0;
}
void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

  if (inst == 0)
  {
	  logger(0, "Could not allocate memory for instance struct!\n");
	  return 0;
  }

  inst->my = construct();

  if (inst->my == 0)
  {
    free(inst);
    return 0;
  }

  return inst;
}

void deleteInstance(void* instance)
{
  Instance* inst = (Instance*) instance;

  destruct(inst->my);

  free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->in_amount = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_attack = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_decay = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_sustain_level = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_release = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_result = (EnvType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Number->Env] group=[Audio] inputs=[5 Amount{lower_bound=[0] step_size=[0.01] higher_bound=[1] } Attack{lower_bound=[0] step_size=[0.01] higher_bound=[1] } Decay{lower_bound=[0] step_size=[0.01] higher_bound=[1] } Sustain_Level{lower_bound=[0] step_size=[0.01] higher_bound=[1.0] } Release{lower_bound=[0] step_size=[0.01] higher_bound=[1] } ] outputs=[1 Env Control ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(numenvmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(numenvmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
	  if (tmpBuf == 0)
	  {
	     printf("Could not allocate memory in getInfo\n");
		 return 0;
	  }
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = numenvmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}



int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
