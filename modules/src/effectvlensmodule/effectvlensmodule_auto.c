#include "effectvlensmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "effectvlensmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_effectvlensmodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_PositionType const=true strong_dependency=true default=[0.5 0.5] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=150 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=30 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType } ";
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
   inst->in_b = (FrameBufferType *) typePointer;
  break;
  case 1:
   inst->in_pos = (PositionType *) typePointer;
  break;
  case 2:
   inst->in_size = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_mag = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_interactive = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_r = (FrameBufferType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Lens] group=[EffecTV] inputs=[5 Bild Linsenposition Linsengroesse{higher_bound=[500] lower_bound=[10] widget_type=[unboundednumber_selector] } Vergroesserung{higher_bound=[200] lower_bound=[5] widget_type=[unboundednumber_selector] } Interaktiv{false_value=[0] true_value=[1] widget_type=[radio_button] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(effectvlensmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(effectvlensmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = effectvlensmodule_xpm[i];
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
      s_log_function(level, "mod_effectvlensmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
