#include "joystickmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "joystickmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_joystickmodule] number_of_inputs=[1] number_of_outputs=[5] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_NumberType } ";
  break;
  case 1:
    return "output_spec { type=typ_NumberType } ";
  break;
  case 2:
    return "output_spec { type=typ_NumberType } ";
  break;
  case 3:
    return "output_spec { type=typ_NumberType } ";
  break;
  case 4:
    return "output_spec { type=typ_MidiType } ";
  break;
 }
 return 0;
}
void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

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
   inst->in_joy_id = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_signal_x = (NumberType* ) typePointer;
  break;
  case 1:
   inst->out_signal_y = (NumberType* ) typePointer;
  break;
  case 2:
   inst->out_button_1 = (NumberType* ) typePointer;
  break;
  case 3:
   inst->out_button_2 = (NumberType* ) typePointer;
  break;
  case 4:
   inst->out_midi = (MidiType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Joystick] group=[Input] inputs=[1 Joystick_ID{hidden=[true] lower_bound=[0] higher_bound=[4] step_size=[1] widget_type=[number_selector] } ] outputs=[5 X_Richtung Y_Richtung Button_1 Button_2 midiOut ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(joystickmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(joystickmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = joystickmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}



static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_joystickmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
