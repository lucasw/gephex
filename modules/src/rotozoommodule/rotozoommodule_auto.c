#include "rotozoommodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "rotozoommodule.xpm"

const char* getSpec(void) {
 return "mod_spec { name=[mod_rotozoommodule] number_of_inputs=[9] number_of_outputs=[1] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=1 } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 2:
    return "input_spec { type=typ_PositionType const=true strong_dependency=true default=[0.5 0.5] } ";
  break;
  case 3:
    return "input_spec { type=typ_FrameBufferType const=true strong_dependency=true  } ";
  break;
  case 4:
    return "input_spec { type=typ_FrameBufferType const=false strong_dependency=false  } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=0 } ";
  break;
  case 6:
    return "input_spec { type=typ_StringType const=true strong_dependency=true default=regular } ";
  break;
  case 7:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=640 } ";
  break;
  case 8:
    return "input_spec { type=typ_NumberType const=true strong_dependency=true default=480 } ";
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
   inst->in_zoom = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_rot = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_disp = (PositionType *) typePointer;
  break;
  case 3:
   inst->in_texture = (FrameBufferType *) typePointer;
  break;
  case 4:
   inst->in_background = (FrameBufferType *) typePointer;
  break;
  case 5:
   inst->in_copy_background = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_routine = (StringType *) typePointer;
  break;
  case 7:
   inst->in_outx = (NumberType *) typePointer;
  break;
  case 8:
   inst->in_outy = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Rotary Zoomer] group=[GrafikEffekte] inputs=[9 Zoom{lower_bound=[0] higher_bound=[4] step_size=[0.04] widget_type=[number_selector] } Drehung{lower_bound=[0] higher_bound=[360] step_size=[1] widget_type=[number_selector] } Verschiebung Textur Hintergrund{help=[Das Hintergrundbild] } Hintergrund_Kopieren{false_value=[0] help=[Soll Hintergrund kopiert werden oder direkt reingeschrieben werden?] hidden=[true] true_value=[1] widget_type=[radio_button] } Rotozoom-Routine{values=[regular,poly] help=[regular ist besser getestet, poly ist schneller] hidden=[true] widget_type=[combo_box] } outx{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[Groesse des Ergebnis-Bildes] } outy{hidden=[true] higher_bound=[1024] widget_type=[number_selector] step_size=[1] lower_bound=[0] help=[Groesse des Ergebnis-Bildes] } ] outputs=[1 Bild ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(rotozoommodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(rotozoommodule_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
	{
	  char* source = rotozoommodule_xpm[i];
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

  static int neededIns[9];
  *neededInputs = neededIns;
	
	neededIns[in_zoom] = 0;
	neededIns[in_rot] = 0;
	neededIns[in_disp] = 0;
	neededIns[in_texture] = 0;
	neededIns[in_background] = 1;
	neededIns[in_copy_background] = 0;
	neededIns[in_routine] = 0;
	neededIns[in_outx] = 0;
	neededIns[in_outy] = 0;



  strongDependencies(inst, neededIns);
}

void getPatchLayout(void* instance,int** out2in)
{
  InstancePtr inst = (InstancePtr) instance;

  static int out2in_[1];
  *out2in = out2in_;
	
	out2in_[out_r] = -1;


  patchLayout(inst, out2in_);
}


static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_rotozoommodule", msg);
}

int initSO(log2T log_function) 
{
	s_log_function = log_function;
	
	

	return init(logger);
}
