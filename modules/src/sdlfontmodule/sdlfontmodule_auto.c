#include "sdlfontmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "sdlfontmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_sdlfontmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_sdlfontmodule] number_of_inputs=[10] number_of_outputs=[1] deterministic=[false] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_StringType id=scroll const=true strong_dependency=true default=[horizontal_scroll] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=effect_time const=true strong_dependency=true  } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=options const=true strong_dependency=true default=[0] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=point_size const=true strong_dependency=true default=[24] } ";
  break;
  case 4:
    return "input_spec { type=typ_PositionType id=pos const=true strong_dependency=true default=[[0.0 1.0]] } ";
  break;
  case 5:
    return "input_spec { type=typ_StringType id=font const=true strong_dependency=true  } ";
  break;
  case 6:
    return "input_spec { type=typ_RGBType id=color const=true strong_dependency=true default=[[0.7 0.3 0.1]] } ";
  break;
  case 7:
    return "input_spec { type=typ_FrameBufferType id=b const=true strong_dependency=true  } ";
  break;
  case 8:
    return "input_spec { type=typ_StringType id=text_ const=true strong_dependency=true default=[NIX] } ";
  break;
  case 9:
    return "input_spec { type=typ_NumberType id=patch const=true strong_dependency=true default=[0] } ";
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
   inst->in_scroll = (StringType *) typePointer;
  break;
  case 1:
   inst->in_effect_time = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_options = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_point_size = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_pos = (PositionType *) typePointer;
  break;
  case 5:
   inst->in_font = (StringType *) typePointer;
  break;
  case 6:
   inst->in_color = (RGBType *) typePointer;
  break;
  case 7:
   inst->in_b = (FrameBufferType *) typePointer;
  break;
  case 8:
   inst->in_text_ = (StringType *) typePointer;
  break;
  case 9:
   inst->in_patch = (NumberType *) typePointer;
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
  static const char* INFO = "info { name=[Font Module] group=[Font] inputs=[10 ScrollEffect{widget_type=[combo_box] values=[vertical_scroll,horizontal_scroll,sine_scroll,static] hidden=[true] } Time{hidden=[false] } Options{widget_type=[check_box] values=[Bold,Italic,Underlined] hidden=[true] } FontSize{lower_bound=[1] widget_type=[number_selector] step_size=[1] higher_bound=[256] hidden=[true] help=[This is the selected font's size (index into fonts size table)] } Position{hidden=[true] help=[Use this to position the font on screen] } Font{file_mask2_name=[True Type Fonts] file_mask1_name=[All files] widget_type=[file_selector] file_mask1=[*.*] file_mask2=[*.ttf] hidden=[true] help=[Specify a true type font file here.] } Color{widget_type=[color_selector] hidden=[true] help=[The color of the font.] } Image ScrollText PatchInput{widget_type=[check_box] values=[Patch] hidden=[true] } ] outputs=[1 Image ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(sdlfontmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(sdlfontmodule_xpm);
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
          char* source = sdlfontmodule_xpm[i];
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
