#include "signalgenmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "signalgenmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_signalmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_signalmodule] number_of_inputs=[6] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 4:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=sinus } ";
  break;
  case 5:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=real } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_NumberType } ";
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
   inst->in_Amplitude = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_Frequenz = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_Phase = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_Position = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_signal = (StringType *) typePointer;
  break;
  case 5:
   inst->in_mode = (StringType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_Signal = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[SignalGenerator] group=[Number] inputs=[6 Amplitude{widget_type=[unboundednumber_selector] hidden=[true] } Frequency{widget_type=[unboundednumber_selector] hidden=[true] } Phase{lower_bound=[0] widget_type=[number_selector] step_size=[0.01] higher_bound=[1] hidden=[true] } Position{widget_type=[unboundednumber_selector] hidden=[true] } Signal{widget_type=[combo_box] values=[sinus,saegezahn,rampe,rechteck,noize] hidden=[true] } Mode{widget_type=[combo_box] values=[real,relativ] hidden=[true] help=[real is system time, relativ is relative to the frame rate] } ] outputs=[1 Signal ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(signalgenmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(signalgenmodule_xpm);
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
	  char* source = signalgenmodule_xpm[i];
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
