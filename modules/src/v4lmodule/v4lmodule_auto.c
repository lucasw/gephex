#include "v4lmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "v4lmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_v4lmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_v4lmodule] number_of_inputs=[9] number_of_outputs=[1] deterministic=[false] }";
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
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 7:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.5 } ";
  break;
  case 8:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1 } ";
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
   inst->in_devicefile = (StringType *) typePointer;
  break;
  case 1:
   inst->in_x_size = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_y_size = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_brightness = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_hue = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_colour = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_contrast = (NumberType *) typePointer;
  break;
  case 7:
   inst->in_whiteness = (NumberType *) typePointer;
  break;
  case 8:
   inst->in_drops = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Video4Linux] group=[Sources] inputs=[9 Devicename{help=[Gerätedatei der Video 4 Linux Gerätes (z.B. /dev/video0)] file_mask=[*] widget_type=[file_selector] hidden=[true] file_mask_name=[Gerätedatei] } Größe(x){lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } Größe(y){lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } Brigthness{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] } Hue{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] } Colour{lower_bound=[0] widget_type=[number_selector] step_size=[0.01] higher_bound=[1] hidden=[true] } Contrast{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] } Whiteness{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] } Droprate{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[200] hidden=[true] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(v4lmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(v4lmodule_xpm);
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
          char* source = v4lmodule_xpm[i];
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
