#include "v4lmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "v4lmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_v4lmodule] number_of_inputs=[3] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=/dev/video0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 2:
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
   inst->in_devicefile = (StringType *) typePointer;
  break;
  case 1:
   inst->in_x_size = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_y_size = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Video4Linux] group=[Quellen] inputs=[3 Devicename{file_mask_name=[Gerätedatei] help=[Gerätedatei der Video 4 Linux Gerätes (z.B. /dev/video0)] file_mask=[*] hidden=[true] widget_type=[file_selector] } Größe(x){absolute=[true] hidden=[true] higher_bound=[1024] widget_type=[number_selector] lower_bound=[0] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } Größe(y){absolute=[true] hidden=[true] higher_bound=[1024] widget_type=[number_selector] lower_bound=[0] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(v4lmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(v4lmodule_xpm);
      tmpBuf = malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = v4lmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}


int initSO(logT log_function) 
{
	
	return init(log_function);
}
