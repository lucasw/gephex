#include "planemodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "planemodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_planemodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_planemodule] number_of_inputs=[8] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=t const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=rot const=true strong_dependency=true default=0 } ";
  break;
  case 2:
    return "input_spec { type=typ_PositionType id=pos const=true strong_dependency=true default=[0.5 0.5] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=xres const=true strong_dependency=true default=640 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=yres const=true strong_dependency=true default=480 } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType id=d const=true strong_dependency=true default=0.5 } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType id=shading const=true strong_dependency=true default=0 } ";
  break;
  case 7:
    return "input_spec { type=typ_FrameBufferType id=b const=true strong_dependency=true  } ";
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
   inst->in_t = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_rot = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_pos = (PositionType *) typePointer;
  break;
  case 3:
   inst->in_xres = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_yres = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_d = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_shading = (NumberType *) typePointer;
  break;
  case 7:
   inst->in_b = (FrameBufferType *) typePointer;
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
  static const char* INFO = "info { name=[Plane] group=[Effects] inputs=[8 Motion{precision=[2] widget_type=[unboundednumber_selector] display_format=[fixed] } Z-Rotation{lower_bound=[0] precision=[2] widget_type=[number_selector] step_size=[0.5] higher_bound=[90] display_format=[fixed] } Position{hidden=[true] } Size(X){lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] display_format=[fixed] help=[Size of output in pixels] } Size(Y){lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] display_format=[fixed] help=[Size of output in pixels] } Plane-Distance{lower_bound=[0.1] widget_type=[number_selector] step_size=[0.01] higher_bound=[1] hidden=[true] } Shading{lower_bound=[0] precision=[2] widget_type=[number_selector] step_size=[0.05] higher_bound=[1] hidden=[true] display_format=[fixed] help=[Degree of Shading] } Image ] outputs=[1 Image ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(planemodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(planemodule_xpm);
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
          char* source = planemodule_xpm[i];
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
