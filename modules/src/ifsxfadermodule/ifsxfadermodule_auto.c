#include "ifsxfadermodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "ifsxfadermodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_ifsxfadermodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_ifsxfadermodule] number_of_inputs=[3] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 1:
    return "input_spec { type=typ_IfsType const=true strong_dependency=false  } ";
  break;
  case 2:
    return "input_spec { type=typ_IfsType const=true strong_dependency=false  } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_IfsType } ";
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
   inst->in_x = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_1 = (IfsType *) typePointer;
  break;
  case 2:
   inst->in_2 = (IfsType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_r = (IfsType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Ifs_x_fader] group=[Ifs] inputs=[3 Fader ifs1 Ifs2 ] outputs=[1 mixedifs ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(ifsxfadermodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(ifsxfadermodule_xpm);
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
          char* source = ifsxfadermodule_xpm[i];
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

  static int neededIns[3];
  *neededInputs = neededIns;
        
	neededIns[in_x] = 0;
	neededIns[in_1] = 1;
	neededIns[in_2] = 1;



  strongDependencies(inst, neededIns);
}


int initSO(log2T log_function) 
{
        s_log_function = log_function;
        
        

        return init(logger);
}
