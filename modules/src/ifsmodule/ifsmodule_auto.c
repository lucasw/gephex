#include "ifsmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "ifsmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_ifsmodule] number_of_inputs=[6] number_of_outputs=[1] deterministic=[false] }";
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
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=10000 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.2 } ";
  break;
  case 4:
    return "input_spec { type=typ_IfsType const=true strong_dependency=true  } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=5 } ";
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
static struct _MyInstance* s_inst = 0;
static int s_ref_count = 0;

void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

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
   inst->in_x_size = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_y_size = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_num_dot = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_amount = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_ifs = (IfsType *) typePointer;
  break;
  case 5:
   inst->in_num_rec = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_out = (FrameBufferType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[IFS] group=[Ifs] inputs=[6 Größe(x){hidden=[true] higher_bound=[1024] step_size=[1] widget_type=[number_selector] lower_bound=[0] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } Größe(y){hidden=[true] higher_bound=[1024] step_size=[1] widget_type=[number_selector] lower_bound=[0] help=[Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert] } dotnum{help=[try something 5000 - 100000] hidden=[true] widget_type=[unboundednumber_selector] } lightness{hidden=[true] higher_bound=[1] widget_type=[number_selector] step_size=[0.01] lower_bound=[0] help=[lightness] } ifsin recdeep{help=[puh] hidden=[true] lower_bound=[0] higher_bound=[255] widget_type=[number_selector] } ] outputs=[1 Frame ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(ifsmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(ifsmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = ifsmodule_xpm[i];
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
      s_log_function(level, "mod_ifsmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
