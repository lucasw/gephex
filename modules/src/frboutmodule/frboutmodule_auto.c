#include "frboutmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "frboutmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_frboutmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_frboutmodule] number_of_inputs=[10] number_of_outputs=[0] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_FrameBufferType id=in const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=options const=true strong_dependency=true default=2 } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=xsize const=true strong_dependency=true default=0 } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=ysize const=true strong_dependency=true default=480 } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=brightness const=true strong_dependency=true default=0.5 } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType id=contrast const=true strong_dependency=true default=1 } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType id=gamma const=true strong_dependency=true default=1 } ";
  break;
  case 7:
    return "input_spec { type=typ_NumberType id=monitor const=true strong_dependency=true default=0 } ";
  break;
  case 8:
    return "input_spec { type=typ_StringType id=driver const=true strong_dependency=true default=default } ";
  break;
  case 9:
    return "input_spec { type=typ_StringType id=server const=true strong_dependency=true default=default } ";
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
   inst->in_options = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_xsize = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_ysize = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_brightness = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_contrast = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_gamma = (NumberType *) typePointer;
  break;
  case 7:
   inst->in_monitor = (NumberType *) typePointer;
  break;
  case 8:
   inst->in_driver = (StringType *) typePointer;
  break;
  case 9:
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
  static const char* INFO = "info { name=[Image Output] group=[Outputs] inputs=[10 Image Options{widget_type=[check_box] toggle_keys=[p[0,1]] values=[On Top,Frame,Mirror X,Mirror Y,Invert] hidden=[true] } xsize{lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[1] special_text=[auto] higher_bound=[2560] hidden=[true] display_format=[fixed] help=[If x_size and y_size > 0 the image is scaled] } ysize{lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[1] special_text=[auto] higher_bound=[1600] hidden=[true] display_format=[fixed] help=[If x_size and y_size > 0 the image is scaled] } Brightness{hidden=[true] help=[Brightness (0.5:no change)] } Contrast{lower_bound=[0] higher_bound=[4] hidden=[true] help=[Contrast (1:no change)] } Gamma{lower_bound=[0.01] higher_bound=[4] hidden=[true] help=[Gamma correction (1:no change)] } Monitor{lower_bound=[0] widget_type=[number_selector] step_size=[1] higher_bound=[3] hidden=[true] help=[On which monitor should the window be placed?] } OutputDriver{widget_type=[combo_box] values=[default,SDL,GL,aalib,vloopback] hidden=[true] } Display{toggle_keys=[p[:0.1,:0.0]] hidden=[true] help=[Format is default or SERVER_HOSTNAME:XSERVER:SCREEN (for vloopback this is the video device, e.g. '/dev/video0')] } ] outputs=[0] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(frboutmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(frboutmodule_xpm);
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
          char* source = frboutmodule_xpm[i];
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
