#include "y4moutputmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "y4moutputmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_y4moutmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_y4moutmodule] number_of_inputs=[5] number_of_outputs=[0] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType id=in const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_StringType id=filename const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=xsize const=true strong_dependency=true default=[320] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=ysize const=true strong_dependency=true default=[240] } ";
  break;
  case 4:
    return "input_spec { type=typ_StringType id=color_model const=true strong_dependency=true default=[yuv420p] } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
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
   inst->in_in = (FrameBufferType *) typePointer;
  break;
  case 1:
   inst->in_filename = (StringType *) typePointer;
  break;
  case 2:
   inst->in_xsize = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_ysize = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_color_model = (StringType *) typePointer;
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
  static const char* INFO = "info { name=[YUV4MPEG2 Output] group=[Outputs] inputs=[5 Image Filename{hidden=[false] } xsize{lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[4] higher_bound=[2560] hidden=[true] display_format=[fixed] help=[If x_size and y_size > 0 the image is scaled] } ysize{lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[4] higher_bound=[1600] hidden=[true] display_format=[fixed] } ColorModel{widget_type=[combo_box] values=[yuv420p,bgra8888] hidden=[false] } ] outputs=[0] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(y4moutputmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(y4moutputmodule_xpm);
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
          char* source = y4moutputmodule_xpm[i];
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
