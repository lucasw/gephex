#include "xfademodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "xfademodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_xfademodule] number_of_inputs=[4] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=false  } ";
  break;
  case 2:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=false  } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=regular } ";
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
   inst->in_x = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_1 = (FrameBufferType *) typePointer;
  break;
  case 2:
   inst->in_2 = (FrameBufferType *) typePointer;
  break;
  case 3:
   inst->in_routine = (StringType *) typePointer;
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
  static const char* INFO = "info { name=[Crossfader] group=[Mixer] inputs=[4 Fader{step_size=[0.01] lower_bound=[0] higher_bound=[1] } Bild1 Bild2 Fade-Routine{values=[regular,mmx] hidden=[true] widget_type=[combo_box] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(xfademodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(xfademodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = xfademodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}

void strongDependenciesCalculated(void* instance,int** neededInputs)
{
  InstancePtr inst = (InstancePtr) instance;

  static int neededIns[4];
  *neededInputs = neededIns;
	
	neededIns[in_x] = 0;
	neededIns[in_1] = 1;
	neededIns[in_2] = 1;
	neededIns[in_routine] = 0;



  strongDependencies(inst, neededIns);
}

void getPatchLayout(void* instance,int** out2in)
{
  InstancePtr inst = (InstancePtr) instance;

  static int out2in_[1];
  *out2in = out2in_;
	
	out2in_[out_r] = -1;


  patchLayout(inst, out2in_);
}


static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_xfademodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
