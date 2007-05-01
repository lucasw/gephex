#include "midikeyrangedecmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "midikeyrangedecmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_midikeyrangedecmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_midikeyrangedecmodule] number_of_inputs=[5] number_of_outputs=[3] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_MidiType id=midi const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=channel const=true strong_dependency=true default=[0] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=note_nr_min const=true strong_dependency=true default=[0] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=note_nr_max const=true strong_dependency=true default=[0] } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=default const=true strong_dependency=true default=[0] } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_NumberType id=pos } ";
  break;
  case 1:
    return "output_spec { type=typ_NumberType id=event } ";
  break;
  case 2:
    return "output_spec { type=typ_NumberType id=pressed } ";
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
   inst->in_midi = (MidiType *) typePointer;
  break;
  case 1:
   inst->in_channel = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_note_nr_min = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_note_nr_max = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_default = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_pos = (NumberType* ) typePointer;
  break;
  case 1:
   inst->out_event = (NumberType* ) typePointer;
  break;
  case 2:
   inst->out_pressed = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[key range dec] group=[Midi] inputs=[5 MidiStream{hidden=[false] help=[The Midi stream] } MIDI_Channel{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[15] hidden=[true] help=[Midi Channel] } min{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[127] hidden=[true] help=[The Number of the Note] } max{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[127] hidden=[true] help=[The Number of the Note] } default key{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[127] hidden=[true] help=[The Number of the Note] } ] outputs=[3 pos event event ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(midikeyrangedecmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(midikeyrangedecmodule_xpm);
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
          char* source = midikeyrangedecmodule_xpm[i];
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
