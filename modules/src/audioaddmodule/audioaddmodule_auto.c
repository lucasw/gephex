#include "audioaddmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "audioaddmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_audioaddmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_audioaddmodule] number_of_inputs=[6] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_AudioType id=lhs const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=w_lhs const=true strong_dependency=true default=1 } ";
  break;
  case 2:
    return "input_spec { type=typ_AudioType id=rhs const=true strong_dependency=true  } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=w_rhs const=true strong_dependency=true default=1 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=thr const=true strong_dependency=true default=512 } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType id=flush const=true strong_dependency=true  } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_AudioType id=r } ";
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
   inst->in_lhs = (AudioType *) typePointer;
  break;
  case 1:
   inst->in_w_lhs = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_rhs = (AudioType *) typePointer;
  break;
  case 3:
   inst->in_w_rhs = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_thr = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_flush = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_r = (AudioType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Adder] group=[Audio] inputs=[6 Signal1 AmpLeft Signal2 AmpRight Threshold{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[4096] hidden=[true] } FlushBuffers{widget_type=[radio_button] hidden=[true] } ] outputs=[1 AddedSignal ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(audioaddmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(audioaddmodule_xpm);
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
          char* source = audioaddmodule_xpm[i];
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
