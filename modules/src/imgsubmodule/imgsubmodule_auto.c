#include "imgsubmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "imgsubmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_imgsubmodule] number_of_inputs=[4] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=regular } ";
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
   inst->in_amount = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_input1 = (FrameBufferType *) typePointer;
  break;
  case 2:
   inst->in_input2 = (FrameBufferType *) typePointer;
  break;
  case 3:
   inst->in_routine = (StringType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_result = (FrameBufferType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Bild-Subtrahierer] group=[Mixer] inputs=[4 Amount{lower_bound=[0] higher_bound=[1] step_size=[0.01] widget_type=[hslider] } Bild1 Bild2 Fade-Routine{values=[regular,mmx] hidden=[true] widget_type=[combo_box] } ] outputs=[1 Bild1-Bild2 ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(imgsubmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(imgsubmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = imgsubmodule_xpm[i];
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
      s_log_function(level, "mod_imgsubmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
