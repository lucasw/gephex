#include "isingnoizemodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "isingnoizemodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_isingnoizemodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=4 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=8 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=640 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=480 } ";
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
   inst->in_temp = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_border_growth = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_spont_growth = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_outx = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_outy = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Isingnoize] group=[Quellen] inputs=[5 Temperatur{higher_bound=[6] help=[Relative Temperatur] lower_bound=[0] widget_type=[unboundednumber_selector] } Randwachstum{hidden=[true] higher_bound=[16] widget_type=[number_selector] step_size=[0.5] lower_bound=[1] help=[Gibt an, wie stark der Rand fluktuiert] } Spontanes_Wachstum{hidden=[true] higher_bound=[48] widget_type=[number_selector] step_size=[0.5] lower_bound=[1] help=[Gibt an, wie stark Flächen fluktuieren] } outx{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[Groesse des Ergebnis-Bildes] } outy{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[Groesse des Ergebnis-Bildes] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(isingnoizemodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(isingnoizemodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = isingnoizemodule_xpm[i];
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
      s_log_function(level, "mod_isingnoizemodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
