#include "audioinmodule.h"

#include <string>
#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "audioindriver.h"

#if defined(OS_POSIX)
#if defined(HAVE_ALSA_ASOUNDLIB_H)
#include "alsadriver.h"
#endif
#if defined(HAVE_SYS_SOUNDCARD_H)
#include "ossdriver.h"
#endif
#elif defined(OS_WIN32)
#include "waveindriver.h"
#endif

static logT s_log;


static const int SAMPLE_RATE = 44100;
static const AudioInDriver::sample_format 
SAMPLE_FORMAT = AudioInDriver::SF_16LE;
static const int BYTES_PER_SAMPLE = 2;
static const int CHANNELS = 1;

static const int AUDIO_BUFFER_SIZE = SAMPLE_RATE*BYTES_PER_SAMPLE/6;

typedef struct _MyInstance {

  AudioInDriver* drv;

  std::string* driver_name;
  int device_number;

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

  my->device_number = -1;
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
  unsigned char data[AUDIO_BUFFER_SIZE];
  int device = trim_int(inst->in_device->number, 0, 256);
  const char* driver_name = inst->in_driver->text;
  std::string& m_driver_name = *my->driver_name;

  inst->out_r->sample_rate      = SAMPLE_RATE;
  inst->out_r->channels         = CHANNELS;

  if (m_driver_name != driver_name || my->drv == 0)
    {
      m_driver_name = driver_name;
      if (my->drv)
        {
          delete my->drv;
          my->drv = 0;
        }

#if defined(OS_POSIX)
#if defined(HAVE_SYS_SOUNDCARD_H)
      if (m_driver_name == "oss"  || m_driver_name == "default")
	{
	  my->drv = new OSSDriver();
	  s_log(2, "Using OSS driver");
	}
      else
#endif
#if defined(HAVE_ALSA_ASOUNDLIB_H)
        if (m_driver_name == "alsa")
	{
	  my->drv = new AlsaDriver();
	  s_log(2, "Using alsa driver");
	}
#endif
#if defined(HAVE_ALSA_ASOUNDLIB_H)
      else
	{
	  my->drv = new AlsaDriver();
	  s_log(2, "Unkown driver - using alsa driver");
	}
#elif defined(HAVE_SYS_SOUNDCARD_H)
	{
	  my->drv = new OSSDriver();
	  s_log(2, "Unkown driver - using OSS driver");
	}
#else
#error OSS or alsa support needed
#endif
#elif defined(OS_WIN32)
      if (m_driver_name == "wavein" || m_driver_name == "default")
	{
	  my->drv = new WaveInDriver();
	  s_log(2, "Using WaveIn driver");
	}
      else
	{
	  my->drv = new WaveInDriver();
	  s_log(2, "Unkown driver - using WaveIn driver");
	}
#endif

    }

  assert(my->drv != 0);

  if (device != my->device_number || !my->drv->is_open())
    {
      if (my->drv->is_open())
        {
          my->drv->close();
        }

      try 
	{
	  my->drv->open(device,
			SAMPLE_RATE,
			SAMPLE_FORMAT,
			CHANNELS);
	}
      catch (std::exception& e)
	{
	  s_log(0, e.what());
	}

    my->device_number = device;
  }

  if (!my->drv->is_open())
    return;

  int len;
  memset(data, 0, sizeof(data));
  try
    {
      len = my->drv->read(data, 
			  sizeof(data) / BYTES_PER_SAMPLE);
    }
  catch (std::exception& e)
    {
      s_log(0, e.what());
    }

  assert(len >= 0);

  if (len == 0)
    s_log(2,"nothing to read!");
  else
    {
      double* samples;
      
      //      printf("read %i samples\n", len);
      audio_resize(inst->out_r, len);
      inst->out_r->len = len;
      samples = inst->out_r->samples;
      for (int i = 0; i < len; ++i)
	{
          int value = *((int_16*)(data + 2*i));
	  // this should work on big endian machines as well
          /*	  unsigned char low_byte  = data[2*i];
	  unsigned char high_byte = data[2*i+1];
	  int value = ((high_byte << 8) | low_byte);*/
	  samples[i] = ((double) value) / ((double)(1 << 15)); 
	}
    }
}

