#include "mirrormodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "mirrormodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_mirrormodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_mirrormodule] number_of_inputs=[4] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=lrrl const=true strong_dependency=true default=[1] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=tbbt const=true strong_dependency=true default=[1] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=mode const=true strong_dependency=true default=[0] } ";
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
   inst->in_lrrl = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_tbbt = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_mode = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Mirror] group=[Filter] inputs=[4 lr-rl{lower_bound=[1] widget_type=[number_selector] step_size=[1] higher_bound=[2] hidden=[true] help=[Copy left to right (1) or right to left (2)] } tb-bt{lower_bound=[1] widget_type=[number_selector] step_size=[1] higher_bound=[2] hidden=[true] help=[Copy top to bottom (1) or bottom to top (2)] } Mode{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[3] hidden=[true] help=[None (0) / Left-Right (1) / Top-Bottom (2) / Both (3)] } Bild ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(mirrormodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(mirrormodule_xpm);
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
          char* source = mirrormodule_xpm[i];
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
