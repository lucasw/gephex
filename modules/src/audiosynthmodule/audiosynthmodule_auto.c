#include "audiosynthmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "audiosynthmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_audiosynthmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_audiosynthmodule] number_of_inputs=[9] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=24 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1.0 } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=sinus } ";
  break;
  case 4:
    return "input_spec { type=typ_EnvType const=true strong_dependency=true  } ";
  break;
  case 5:
    return "input_spec { type=typ_LfoType const=true strong_dependency=true  } ";
  break;
  case 6:
    return "input_spec { type=typ_EnvType const=true strong_dependency=true  } ";
  break;
  case 7:
    return "input_spec { type=typ_LfoType const=true strong_dependency=true  } ";
  break;
  case 8:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=44100 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_AudioType } ";
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
   inst->in_key_press = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_key = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_amplitude = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_signal = (StringType *) typePointer;
  break;
  case 4:
   inst->in_a_env = (EnvType *) typePointer;
  break;
  case 5:
   inst->in_a_lfo = (LfoType *) typePointer;
  break;
  case 6:
   inst->in_f_env = (EnvType *) typePointer;
  break;
  case 7:
   inst->in_f_lfo = (LfoType *) typePointer;
  break;
  case 8:
   inst->in_sample_rate = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Audiosynth] group=[Audio] inputs=[9 KeyOnOff{true_value=[1] widget_type=[radio_button] false_value=[0] hidden=[false] } Key{lower_bound=[0] widget_type=[number_selector] keys=[a[10];s[11];d[12];f[13];g[14];h[15];j[16]] step_size=[1] higher_bound=[127] hidden=[false] } Amplitude{lower_bound=[0] widget_type=[number_selector] step_size=[0.01] higher_bound=[1] hidden=[false] } Signal{widget_type=[combo_box] values=[sinus,saegezahn,rechteck,noize,brownnoize] hidden=[true] } Amplitude_ENV{hidden=[false] } Amplitude_LFO{hidden=[false] } Frequenz_ENV{hidden=[false] } Frequenz_LFO{hidden=[false] } SampleRate{lower_bound=[8000] widget_type=[number_selector] step_size=[1] higher_bound=[44100] hidden=[true] } ] outputs=[1 Audio-Strom ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(audiosynthmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(audiosynthmodule_xpm);
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
	  char* source = audiosynthmodule_xpm[i];
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
