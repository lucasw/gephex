#include "flashmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "flashmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_flashmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_flashmodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=3 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=2 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=10 } ";
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
   inst->in_trigger = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_src = (FrameBufferType *) typePointer;
  break;
  case 2:
   inst->in_attack = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_sustain = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_decay = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Flashfader] group=[Filter] inputs=[5 Trigger{widget_type=[radio_button] } Bild Attack{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[10] hidden=[true] } Sustain{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[10] hidden=[true] } Decay{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[25] hidden=[true] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(flashmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(flashmodule_xpm);
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
	  char* source = flashmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}


void getPatchLayout(void* instance,int** out2in)
{
  InstancePtr inst = (InstancePtr) instance;

  static int out2in_[1];
  *out2in = out2in_;
	
	out2in_[out_r] = -1;


  patchLayout(inst, out2in_);
}


int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
