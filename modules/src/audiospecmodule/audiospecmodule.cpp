#include "audiospecmodule.h"

#include <cmath>
#include "fft.hh"

static logT s_log;

static const int NUM_SAMPLES = 1024;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

template <typename T>
T my_min(T a, T b) {
	return (a < b) ? a : b;
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  int len = my_min(inst->in_audio->len, NUM_SAMPLES);
  std::vector<std::complex<double> > src(NUM_SAMPLES);


  if (inst->in_audio->channels != 1) {
    s_log(0, "channels not 1!");
    return;
  }

  audio_resize(inst->out_f, len);
  inst->out_f->len = len;
  double* out_samples = inst->out_f->samples;

  const double* samples = inst->in_audio->samples;

  int i;
  for (i = 0; i < NUM_SAMPLES; ++i) {
    if (i < len)
      src[i] = std::complex<double>(samples[i], 0);
    else
      src[i] = 0;
  }

  math::fftInplace(src, 1);

  for (i = 0; i < len/2; ++i) {
    src[i] /= NUM_SAMPLES/2;
    out_samples[2*i]   = src[i].real();
    out_samples[2*i+1] = src[i].imag();
  }

  inst->out_f->sample_rate = inst->in_audio->sample_rate;
  inst->out_f->channels = 1;
}


