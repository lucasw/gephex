#include "frbinmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "frbinmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_frbinmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_frbinmodule] number_of_inputs=[7] number_of_outputs=[2] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_StringType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0.0 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 5:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=no } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType } ";
  break;
  case 1:
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
   inst->in_fileName = (StringType *) typePointer;
  break;
  case 1:
   inst->in_seek = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_position = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_x_size = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_y_size = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_cache = (StringType *) typePointer;
  break;
  case 6:
   inst->in_flush = (NumberType *) typePointer;
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
  case 1:
   inst->out_position = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Image Source] group=[Sources] inputs=[7 Filename{file_mask2_name=[Images] file_mask1_name=[All files] widget_type=[file_selector] file_mask3_name=[Videos] file_mask1=[*.*] file_mask3=[*.avi;*.mpg;*.mpeg;*.divx;*.rm;*.mov;*.wmv] file_mask2=[*.bmp;*.jpg;*.png;*.tiff;*.ppm;*.pcx;*.gif;*.jpeg;*.xpm] hidden=[true] } seek{widget_type=[radio_button] false_value=[0] true_value=[1] hidden=[true] help=[seek to position] } Position{lower_bound=[0] widget_type=[number_selector] step_size=[0.001] higher_bound=[1] hidden=[false] } Size(x){lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] help=[If x_size and y_size > 0 the image is scaled] } Größe(y){lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[1024] hidden=[true] help=[If x_size and y_size > 0 the image is scaled] } Use-Cache{widget_type=[combo_box] values=[yes,no] hidden=[true] } FlushCache{true_value=[1] widget_type=[radio_button] false_value=[0] hidden=[true] } ] outputs=[2 Video Position ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(frbinmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(frbinmodule_xpm);
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
	  char* source = frbinmodule_xpm[i];
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
