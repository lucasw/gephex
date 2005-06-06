#include "pixelizemodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "pixelizemodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_pixelizemodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_pixelizemodule] number_of_inputs=[3] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=bsize const=true strong_dependency=true default=[1] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=bsizey const=true strong_dependency=true default=[0] } ";
  break;
  case 2:
    return "input_spec { type=typ_FrameBufferType id=src const=true strong_dependency=true  } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType id=r } ";
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
   inst->in_bsize = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_bsizey = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_src = (FrameBufferType *) typePointer;
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
  static const char* INFO = "info { name=[Pixelizer] group=[Filter] inputs=[3 BlockSize(X){lower_bound=[1] precision=[0] widget_type=[number_selector] step_size=[1] higher_bound=[80] hidden=[false] display_format=[fixed] } BlockSize(Y){lower_bound=[0] precision=[0] widget_type=[number_selector] step_size=[1] special_text=[match x] higher_bound=[80] hidden=[false] display_format=[fixed] help=[if you set this value to 0, the y blocksize will match the x blocksize] } Image ] outputs=[1 Image ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(pixelizemodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(pixelizemodule_xpm);
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
          char* source = pixelizemodule_xpm[i];
          memcpy(offset,source,strlen(source)+1);
          offset += strlen(source) + 1;
        }                       
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;        
}


void getPatchLayout(void* instance,int** out2in)
{
  InstancePtr inst = (InstancePtr) instance;

  static int out2in_[1];
  *out2in = out2in_;
        
	out2in_[out_r] = -1;


  patchLayout(inst, out2in_);
}


int initSO(log2T log_function) 
{
        s_log_function = log_function;
        
        

        return init(logger);
}
