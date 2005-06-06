#include "effectvrevmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "effectvrevmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_effectvrevmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_effectvrevmodule] number_of_inputs=[4] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType id=b const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=vgrabtime const=true strong_dependency=true default=[1] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=linespace const=true strong_dependency=true default=[6] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=vscale const=true strong_dependency=true default=[25] } ";
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
static struct _MyInstance* s_inst = 0;
static int s_ref_count = 0;

void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

  if (inst == 0)
  {
          logger(0, "Could not allocate memory for instance struct!\n");
          return 0;
  }

  s_ref_count += 1;

  if (s_ref_count == 1)
  {
    s_inst = construct();
    if (s_inst == 0)
    {
      free(inst);
      s_ref_count = 0;
      return 0;
    }
  }
  
  inst->my = s_inst;    

  return inst;
}

void deleteInstance(void* instance)
{
  Instance* inst = (Instance*) instance;

  s_ref_count -= 1;

  if (s_ref_count == 0)
        destruct(s_inst);
        
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
   inst->in_vgrabtime = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_linespace = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_vscale = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Rev] group=[EffecTV] inputs=[4 Image VGrabTime{lower_bound=[1] precision=[0] higher_bound=[255] hidden=[true] display_format=[fixed] } LineSpace{lower_bound=[1] precision=[0] higher_bound=[255] hidden=[true] display_format=[fixed] } VScale{lower_bound=[1] precision=[0] higher_bound=[255] hidden=[true] display_format=[fixed] } ] outputs=[1 Image ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(effectvrevmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(effectvrevmodule_xpm);
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
          char* source = effectvrevmodule_xpm[i];
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
