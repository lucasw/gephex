#include "signalgenmodule.h"

#include <limits.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415
#endif

static const double TIME_STEP = 0.25;

typedef struct _MyInstance {
  double time;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  // Add your initialization here
  my->time = 0;

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // Add your effect here!

  double amp = inst->in_Amplitude->number / 2.0;
  double freq = inst->in_Frequenz->number / (double) UINT_MAX;
  double shift = 2*M_PI*inst->in_Phase->number / (double) UINT_MAX;

  double transMax = (double) UINT_MAX / 2.0 - amp;

  double trans = 2.0 * transMax * (((double) inst->in_Position->number) / (double) UINT_MAX);
  double result;
  const char* signalArt = inst->in_Signal->text;

  my->time += TIME_STEP;

  if (strcmp(signalArt,"sinus") == 0)
    {
      result = (amp*(1.0 + sin(freq*my->time+shift)));
    }
  else if (strcmp(signalArt,"saegezahn") == 0)
    {				
      double time = fmod(my->time + shift,1.0 / freq);
      result =  (amp*2.0*freq*time);
    }
  else if (strcmp(signalArt,"rechteck") == 0)
    {
      double T = 1.0 / freq;
      double time = fmod(my->time + shift,T);
      if (time < 0.5*T)
	result = 2*amp;
      else
	result = 0;
    }
  else
    {
      printf("mister: %s!\n",signalArt);
      result = 0;
    }

  inst->out_Signal->number = (unsigned int) (result + trans);
}

