#include "tunnelmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "tunnelmodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_tunnelmodule] number_of_inputs=[8] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_PositionType const=true strong_dependency=true  } ";
  break;
  case 3:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=640 } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=480 } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";
  break;
  case 7:
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
 }
 return 0;
}
void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

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
   inst->in_t = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_rot = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_pos = (PositionType *) typePointer;
  break;
  case 3:
   inst->in_b = (FrameBufferType *) typePointer;
  break;
  case 4:
   inst->in_xres = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_yres = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_radius = (NumberType *) typePointer;
  break;
  case 7:
   inst->in_shading = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Tunnel] group=[GrafikEffekte] inputs=[8 Bewegung Drehung Position Bild Groesse(X){absolute=[true] hidden=[true] higher_bound=[1024] widget_type=[number_selector] lower_bound=[0] help=[Größe des Outputs in Pixeln] } Groesse(Y){absolute=[true] hidden=[true] higher_bound=[1024] widget_type=[number_selector] lower_bound=[0] help=[Größe des Outputs in Pixeln] } Radius Shading{absolute=[true] hidden=[true] higher_bound=[10] widget_type=[number_selector] lower_bound=[0] help=[Stärke des Shadings] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(tunnelmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(tunnelmodule_xpm);
      tmpBuf = malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = tunnelmodule_xpm[i];
	  memcpy(offset,source,strlen(source)+1);
	  offset += strlen(source) + 1;
	}			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;	
}


static void* attributes[8];

void initAttributes()
{
	static FrameBufferAttributes attr3;

	int i = 0;

	for (i = 0; i < 8; ++i)
		attributes[i] = 0;

	attr3.xsize = 512; attr3.ysize = 512;
	attributes[3] = &attr3;	

}

void* getInputAttributes(int index)
{
	return attributes[index];
}
	
int initSO(logT log_function) 
{
	initAttributes();
	return init(log_function);
}
