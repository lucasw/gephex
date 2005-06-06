#include "funparsemodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "funparsemodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_funparsemodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_funparsemodule] number_of_inputs=[5] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_StringType id=exp const=true strong_dependency=true default=[0] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=x1 const=true strong_dependency=false default=[0] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=x2 const=true strong_dependency=false default=[0] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=x3 const=true strong_dependency=false default=[0] } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=x4 const=true strong_dependency=false default=[0] } ";
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
   inst->in_exp = (StringType *) typePointer;
  break;
  case 1:
   inst->in_x1 = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_x2 = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_x3 = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_x4 = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[FunctionParser] group=[Number] inputs=[5 Expression{hidden=[true] help=[Enter an arithmetic expression here (the inputs can be accessed through the variables x1 to x4, e.g. 'x1 + x2').] } x1{widget_type=[unboundednumber_selector] } x2{widget_type=[unboundednumber_selector] } x3{widget_type=[unboundednumber_selector] } x4{widget_type=[unboundednumber_selector] } ] outputs=[1 Result ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(funparsemodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(funparsemodule_xpm);
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
          char* source = funparsemodule_xpm[i];
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
        
	neededIns[in_exp] = 0;
	neededIns[in_x1] = 1;
	neededIns[in_x2] = 1;
	neededIns[in_x3] = 1;
	neededIns[in_x4] = 1;



  strongDependencies(inst, neededIns);
}


int initSO(log2T log_function) 
{
        s_log_function = log_function;
        
        

        return init(logger);
}
