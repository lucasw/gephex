#include "numposmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "numposmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_num2pos] number_of_inputs=[2] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_PositionType } ";
  break;
 }
 return 0;
}
void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

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
   inst->in_xpos = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_ypos = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_result = (PositionType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[X+Y->Position] group=[Position] inputs=[2 X-Position{higher_bound=[1] lower_bound=[0] step_size=[0.01] } Y-Position{higher_bound=[1] lower_bound=[0] step_size=[0.01] } ] outputs=[1 Ergebnis-Position ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(numposmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(numposmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = numposmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}



static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_num2pos", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
