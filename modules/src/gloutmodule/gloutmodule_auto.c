#include "gloutmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "glmonitor.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_gloutmodule] number_of_inputs=[3] number_of_outputs=[0] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=320 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=240 } ";
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
   inst->in_in = (FrameBufferType *) typePointer;
  break;
  case 1:
   inst->in_xsize = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_ysize = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[OpenGL] group=[Outputs] inputs=[3 Bild xsize{hidden=[true] higher_bound=[1280] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[[ Set the x-size of the output window. If set to 0 the window size is set to the size of the input ]] } ysize{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[[ Set the y-size of the output window. If set to 0 the window size is set to the size of the input ]] } ] outputs=[0] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(glmonitor_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(glmonitor_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = glmonitor_xpm[i];
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
      s_log_function(level, "mod_gloutmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
