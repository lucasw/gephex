#include "starfield.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "starfield.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_starfield] number_of_inputs=[4] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_RGBType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_RGBType const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";
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
   inst->in_colorStars = (RGBType *) typePointer;
  break;
  case 1:
   inst->in_colorBG = (RGBType *) typePointer;
  break;
  case 2:
   inst->in_speed = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_currentNumStars = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_result = (FrameBufferType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Moving Starfield] group=[Quellen] inputs=[4 Farbe Sterne{hidden=[true] widget_type=[color_selector] } Farbe Hintergrund{hidden=[true] widget_type=[color_selector] } Geschwindigkeit Anzahl Sterne ] outputs=[1 StarField ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(starfield_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(starfield_xpm);
      tmpBuf = malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = starfield_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}


int initSO(logT log_function) 
{
	
	return init(log_function);
}
