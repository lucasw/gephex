#include "x11outmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "x11outmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_x11outmodule] number_of_inputs=[5] number_of_outputs=[0] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=640 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=480 } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=XImage } ";
  break;
  case 4:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=:0.0 } ";
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
  case 3:
   inst->in_driver = (StringType *) typePointer;
  break;
  case 4:
   inst->in_server = (StringType *) typePointer;
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
  static const char* INFO = "info { name=[X11 Output] group=[Outputs] inputs=[5 Bild xsize{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[[Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert]] } ysize{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[[Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert]] } OutputDriver{values=[XImage,XShm] hidden=[true] widget_type=[combo_box] } Xserver{hidden=[true] } ] outputs=[0] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(x11outmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(x11outmodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = x11outmodule_xpm[i];
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
      s_log_function(level, "mod_x11outmodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
