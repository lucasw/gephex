#include "imgarithmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "imgarithmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_imgarithmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_imgarithmodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=amount const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_FrameBufferType id=input1 const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_FrameBufferType id=input2 const=true strong_dependency=false  } ";
  break;
  case 3:
    return "input_spec { type=typ_StringType id=mmx const=true strong_dependency=true default=yes } ";
  break;
  case 4:
    return "input_spec { type=typ_StringType id=op const=true strong_dependency=true default=[x + c*y] } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType id=result } ";
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
   inst->in_amount = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_input1 = (FrameBufferType *) typePointer;
  break;
  case 2:
   inst->in_input2 = (FrameBufferType *) typePointer;
  break;
  case 3:
   inst->in_mmx = (StringType *) typePointer;
  break;
  case 4:
   inst->in_op = (StringType *) typePointer;
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
  static const char* INFO = "info { name=[Image Calculon] group=[Mixer] inputs=[5 c{lower_bound=[0] widget_type=[hslider] step_size=[0.01] higher_bound=[1] } x y Use-MMX{widget_type=[combo_box] values=[yes,no] hidden=[true] } Operation{widget_type=[combo_box] values=[x + c*y,x - c*y,(1-c)*x + c*(x*y),x + c,x - c,x * 4*c,1 - x] hidden=[true] help=[x und y sind die beiden Bilder, c ist eine konstante Zahl] } ] outputs=[1 Result ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(imgarithmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(imgarithmodule_xpm);
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
          char* source = imgarithmodule_xpm[i];
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

  static int neededIns[5];
  *neededInputs = neededIns;
        
	neededIns[in_amount] = 0;
	neededIns[in_input1] = 0;
	neededIns[in_input2] = 1;
	neededIns[in_mmx] = 0;
	neededIns[in_op] = 0;



  strongDependencies(inst, neededIns);
}


int initSO(log2T log_function) 
{
        s_log_function = log_function;
        
        

        return init(logger);
}
