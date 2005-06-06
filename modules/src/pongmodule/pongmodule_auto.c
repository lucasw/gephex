#include "pongmodule.h"
#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
#include "dllutils.h"
#include "pongmodule.xpm"

static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, "mod_pongmodule", msg);
}

const char* getSpec(void) {
 return "mod_spec { name=[mod_pongmodule] number_of_inputs=[7] number_of_outputs=[6] deterministic=[true] }";
}
const char* getInputSpec(int index) {
 switch(index) {
   case 0:
    return "input_spec { type=typ_NumberType id=p1 const=true strong_dependency=true default=[0.5] } ";
  break;
  case 1:
    return "input_spec { type=typ_NumberType id=p2 const=true strong_dependency=true default=[0.5] } ";
  break;
  case 2:
    return "input_spec { type=typ_NumberType id=ball_x const=true strong_dependency=true default=[0.01] } ";
  break;
  case 3:
    return "input_spec { type=typ_NumberType id=ball_y const=true strong_dependency=true default=[0.01] } ";
  break;
  case 4:
    return "input_spec { type=typ_NumberType id=speed_x const=true strong_dependency=true default=[0.01] } ";
  break;
  case 5:
    return "input_spec { type=typ_NumberType id=speed_y const=true strong_dependency=true default=[0.01] } ";
  break;
  case 6:
    return "input_spec { type=typ_NumberType id=start const=true strong_dependency=true default=[1] } ";
  break;
 }
 return 0;
}
const char* getOutputSpec(int index) {
 switch(index) {
   case 0:
    return "output_spec { type=typ_FrameBufferType id=screen } ";
  break;
  case 1:
    return "output_spec { type=typ_NumberType id=speed_x } ";
  break;
  case 2:
    return "output_spec { type=typ_NumberType id=speed_y } ";
  break;
  case 3:
    return "output_spec { type=typ_NumberType id=ball_x } ";
  break;
  case 4:
    return "output_spec { type=typ_NumberType id=ball_y } ";
  break;
  case 5:
    return "output_spec { type=typ_NumberType id=status } ";
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
   inst->in_p1 = (NumberType *) typePointer;
  break;
  case 1:
   inst->in_p2 = (NumberType *) typePointer;
  break;
  case 2:
   inst->in_ball_x = (NumberType *) typePointer;
  break;
  case 3:
   inst->in_ball_y = (NumberType *) typePointer;
  break;
  case 4:
   inst->in_speed_x = (NumberType *) typePointer;
  break;
  case 5:
   inst->in_speed_y = (NumberType *) typePointer;
  break;
  case 6:
   inst->in_start = (NumberType *) typePointer;
  break;
 } //switch(index) 
 return 1;
}
int setOutput(void* instance,int index, void* typePointer)
{
 InstancePtr inst = (InstancePtr) instance;
 switch(index) {
  case 0:
   inst->out_screen = (FrameBufferType* ) typePointer;
  break;
  case 1:
   inst->out_speed_x = (NumberType* ) typePointer;
  break;
  case 2:
   inst->out_speed_y = (NumberType* ) typePointer;
  break;
  case 3:
   inst->out_ball_x = (NumberType* ) typePointer;
  break;
  case 4:
   inst->out_ball_y = (NumberType* ) typePointer;
  break;
  case 5:
   inst->out_status = (NumberType* ) typePointer;
  break;
 } //switch(index) 
 return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Pong Game] group=[Games] inputs=[7 Player1Position{lower_bound=[0] step_size=[0.01] higher_bound=[1] } Player2Position{lower_bound=[0] step_size=[0.01] higher_bound=[1] } BallX BallY SpeedX SpeedY Start{widget_type=[radio_button] false_value=[0] true_value=[1] } ] outputs=[6 Videoout SpeedX SpeedY BallX BallY RightPad ] type=xpm } ";
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(pongmodule_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(pongmodule_xpm);
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
          char* source = pongmodule_xpm[i];
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
