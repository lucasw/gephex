#include "dplmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "dplmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_dplmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_dplmodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=amount const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=angle const=true strong_dependency=true default=0 } ";
  break;
  case 2:
    return "input_spec { type=typ_FrameBufferType id=displ_mask const=true strong_dependency=true  } ";
  break;
  case 3:
    return "input_spec { type=typ_FrameBufferType id=in const=true strong_dependency=true  } ";
  break;
  case 4:
    return "input_spec { type=typ_StringType id=mode const=true strong_dependency=true default=default } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType id=out } ";
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
   inst->in_angle = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_displ_mask = (FrameBufferType *) typePointer;
  break;
  case 3:
   inst->in_in = (FrameBufferType *) typePointer;
  break;
  case 4:
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
   inst->out_out = (FrameBufferType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Displacement] group=[Mixer] inputs=[5 Amount{lower_bound=[0] widget_type=[hslider] step_size=[0.01] higher_bound=[1] } Angle{lower_bound=[0] widget_type=[number_selector] step_size=[0.5] higher_bound=[360] } Displacement_Mask Input Mode{widget_type=[combo_box] values=[default,exact] hidden=[true] help=[displacement mode] } ] outputs=[1 Result ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(dplmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(dplmodule_xpm);
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
          char* source = dplmodule_xpm[i];
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
