#include "audiooutmodule.h"

#include <string>
#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "audiooutdriver.h"
#if defined(OS_POSIX)
#if defined(HAVE_ALSA_ASOUNDLIB_H)
#include "alsaoutdriver.h"
#endif
#if defined(HAVE_SYS_SOUNDCARD_H)
#include "ossoutdriver.h"
#endif
#elif defined(OS_WIN32)
#include "waveoutdriver.h"
#endif

#ifndef max
int max(int a, int b) {
  return (a < b) ? b : a;
}
#endif

static logT s_log;

static const int NUM_SAMPLES = 1024;
static const int SAMPLE_RATE = 44100;
static const AudioOutDriver::sample_format SAMPLE_FORMAT = 
AudioOutDriver::SF_16LE;
static const int BYTES_PER_SAMPLE = 2;
static const int CHANNELS = 1;

typedef struct _MyInstance {

  AudioOutDriver* drv;

  int device_number;

  int latency;

  std::string* driver_name;

} MyInstance, *MyInstancePtr;


#if defined(OS_WIN32)

#endif

int init(logT log_function)
{
  s_log = log_function;

  /*#if defined(OS_WIN32)
  if (info() > 0)
	return 1;
  else {
	  s_log(0, "No waveIn devices found");
	  return 0;
	}
        #endif*/

  return 1;

}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0) {
    s_log(0, "Could not allocate memory for MyInstance!");
    return 0;
  }

  my->device_number = -1;

  my->latency = 200;
  my->driver_name = new std::string("");
  my->drv = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->drv)
    delete my->drv;

  delete my->driver_name;

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  char buffer[256];
  int len;
  int num_samples;
  int device  = trim_int(inst->in_device->number, 0, 256);
  int latency = trim_int(inst->in_latency->number, 0, 1000);
  const char* driver_name = inst->in_driver->text;
  std::string& m_driver_name = *my->driver_name;
  if (inst->in_audio->sample_rate != SAMPLE_RATE ||
      inst->in_audio->channels != CHANNELS)
    {
      snprintf(buffer, sizeof(buffer),
               "sample_rate = %i; channels = %i",
               inst->in_audio->sample_rate,
               inst->in_audio->channels);
      s_log(0, buffer);
               //      s_log(0, "Wrong audio format!");
      return;
    }

  if (m_driver_name != driver_name || my->drv == 0)
    {
      m_driver_name = driver_name;
      if (my->drv)
	delete my->drv;

#if defined(OS_POSIX)
#if defined(HAVE_SYS_SOUNDCARD_H)
      if (m_driver_name == "oss"  || m_driver_name == "default")
	{
	  my->drv = new OSSOutDriver();
	  s_log(2, "Using OSS driver");
	}
      else
#endif
#if defined(HAVE_ALSA_ASOUNDLIB_H)
        if (m_driver_name == "alsa")
	{
	  my->drv = new AlsaOutDriver();
	  s_log(2, "Using alsa driver");
	}
#endif
#if defined(HAVE_ALSA_ASOUNDLIB_H)
      else
	{
	  my->drv = new AlsaOutDriver();
	  s_log(2, "Unkown driver - using alsa driver");
	}
#elif defined(HAVE_SYS_SOUNDCARD_H)
	{
	  my->drv = new OSSOutDriver();
	  s_log(2, "Unkown driver - using OSS driver");
	}
#else
#error OSS or alsa support needed
#endif
#elif defined(OS_WIN32)
      if (m_driver_name == "waveout" || m_driver_name == "default")
	{
	  my->drv = new WaveOutDriver();
	  s_log(2, "Using WaveOut driver");
	}
      else
	{
	  my->drv = new WaveOutDriver();
	  s_log(2, "Unkown driver - using WaveOut driver");
	}
#endif

    }

  assert(my->drv);

  if (device != my->device_number || latency != my->latency 
      || !my->drv->is_open())
    {
      int num_periods;
      if (my->drv->is_open())
	my->drv->close();
    
      num_periods = (int) max(1, (int) (((double)latency/1000.)
					* SAMPLE_RATE) / NUM_SAMPLES);

      try
	{
	  my->drv->open(device,
			SAMPLE_RATE,
			SAMPLE_FORMAT,
			CHANNELS, NUM_SAMPLES,
			num_periods);

	  my->device_number = device;
	  my->latency = latency;
	}
      catch (std::exception& e)
	{
	  s_log(0, e.what());
	}
  }

  if (!my->drv->is_open())
    return;  

  unsigned char* sample_buffer;
  double* samples = inst->in_audio->samples;
  int i;

  num_samples = inst->in_audio->len;
  sample_buffer = new unsigned char[num_samples * BYTES_PER_SAMPLE];
  for (i = 0; i < num_samples; ++i)
    {
      // this should work on big endian machines as well
      int value = (int) (samples[i] * ((1 << 15) -1));
      sample_buffer[2*i]   = (unsigned char)   value & 0x00ff;
      sample_buffer[2*i+1] = (unsigned char) ((value & 0xff00) >> 8);
    }
  try
    {
      len = my->drv->write(sample_buffer, num_samples);
      assert(len >= 0);
    }
  catch (std::exception& e)
    {
      s_log(0, e.what());
    }

  delete[] sample_buffer;

  /*	else
	printf("wrote %i samples\n", len);*/

}

