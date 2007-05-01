#include "colorizemodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "colorizemodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_colorizemodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_colorizemodule] number_of_inputs=[4] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_RGBType id=color const=true strong_dependency=true default=[[0 0 0]] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=mode const=true strong_dependency=true default=[1] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=tolerance const=true strong_dependency=true default=[0.5] } ";
  break;
  case 3:
    return "input_spec { type=typ_FrameBufferType id=1 const=true strong_dependency=true  } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType id=r } ";
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
   inst->in_color = (RGBType *) typePointer;
  break;
  case 1:
   inst->in_mode = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_tolerance = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_1 = (FrameBufferType *) typePointer;
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
  static const char* INFO = "info { name=[Colorize] group=[Filter] inputs=[4 Color{hidden=[true] } Mode{lower_bound=[1] widget_type=[number_selector] step_size=[1] higher_bound=[7] hidden=[true] } Tolerance{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] } Bild ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(colorizemodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(colorizemodule_xpm);
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
          char* source = colorizemodule_xpm[i];
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
