#include "audiooutmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "audiooutmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_audiooutmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_audiooutmodule] number_of_inputs=[4] number_of_outputs=[0] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_AudioType const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=200 } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=default } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
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
   inst->in_device = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_audio = (AudioType *) typePointer;
  break;
  case 2:
   inst->in_latency = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_driver = (StringType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Out] group=[Audio] inputs=[4 Device{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[256] hidden=[true] } Audio-Strom Latenz(ms){lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1000] hidden=[true] help=[[Latenz in Millisekunden - erhoehen wenn es oft zu Aussetzern kommt]] } Treiber{widget_type=[combo_box] values=[default,waveout,alsa,oss] hidden=[true] } ] outputs=[0] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(audiooutmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(audiooutmodule_xpm);
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
          char* source = audiooutmodule_xpm[i];
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
