#include "doepfermodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "doepfermodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_doepfermodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_doepfermodule] number_of_inputs=[3] number_of_outputs=[4] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 2:
    return "input_spec { type=typ_MidiType const=true strong_dependency=true  } ";
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
   inst->in_channel = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_button_group = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_midi = (MidiType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_signal_1 = (NumberType* ) typePointer;
  break;
  case 1:
   inst->out_signal_2 = (NumberType* ) typePointer;
  break;
  case 2:
   inst->out_signal_3 = (NumberType* ) typePointer;
  break;
  case 3:
   inst->out_signal_4 = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Doepferl] group=[Midi] inputs=[3 MIDI_Channel{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[15] hidden=[true] help=[Midi Kanal] } Key_Group{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[5] hidden=[true] help=[balh] } MidiStrom{help=[balh] } ] outputs=[4 Button_1 Button_2 Button_3 Button_4 ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(doepfermodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(doepfermodule_xpm);
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
          char* source = doepfermodule_xpm[i];
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
