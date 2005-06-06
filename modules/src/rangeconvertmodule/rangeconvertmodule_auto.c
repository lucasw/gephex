#include "rangeconvertmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "rangeconvertmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_rangeconvertmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_rangeconvertmodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=n const=true strong_dependency=true default=[0] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=min_in const=true strong_dependency=true default=[0] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=max_in const=true strong_dependency=true default=[1] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=min_out const=true strong_dependency=true default=[0] } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=max_out const=true strong_dependency=true default=[1] } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_NumberType id=r } ";
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
   inst->in_n = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_min_in = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_max_in = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_min_out = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_max_out = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_r = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[RangeKonvert0r] group=[Number] inputs=[5 Input{widget_type=[unboundednumber_selector] } Min_In{widget_type=[unboundednumber_selector] hidden=[true] } Max_In{widget_type=[unboundednumber_selector] hidden=[true] } Min_Out{widget_type=[unboundednumber_selector] hidden=[true] } Max_Out{widget_type=[unboundednumber_selector] hidden=[true] } ] outputs=[1 Output ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(rangeconvertmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(rangeconvertmodule_xpm);
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
          char* source = rangeconvertmodule_xpm[i];
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
