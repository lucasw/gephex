/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "audiooutmodule.h"

#include <string>
#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "audiooutdriver.h"
#include "a_cvt.h"

#if defined(WITH_ASOUNDLIB)
#include "alsaoutdriver.h"
#endif

#if defined(WITH_OSS)
#include "ossoutdriver.h"
#endif

#if defined(OS_WIN32)
#include "waveoutdriver.h"
#endif

#if defined(OS_DARWIN)
#include "coreaudiooutdriver.h"
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


#if defined(WITH_OSS)
      if (m_driver_name == "oss" )
	{
	  my->drv = new OSSOutDriver();
	  s_log(2, "Using OSS driver");
	}
      else
#endif
#if defined(WITH_ASOUNDLIB)
      if (m_driver_name == "alsa")
        {
          my->drv = new AlsaOutDriver();
          s_log(2, "Using alsa driver");
        }
      else
#endif
#if defined(OS_WIN32)
      if (m_driver_name == "waveout")
	{
	  my->drv = new WaveOutDriver();
	  s_log(2, "Using WaveOut driver");
	}
      else
#endif
#if defined(OS_DARWIN)
      if (m_driver_name == "coreaudio")
	{
	  my->drv = new CoreAudioOutDriver();
	  s_log(2, "Using CoreAudio driver");
	}
      else
#endif
#if defined(WITH_ASOUNDLIB)
	{
	  my->drv = new AlsaOutDriver();
          if (m_driver_name == "default")
            s_log(2, "Using alsa driver");
          else
            s_log(2, "Unkown driver - using alsa driver");
	}
#elif defined(WITH_OSS)
	{
	  my->drv = new OSSOutDriver();
          if (m_driver_name == "default")
            s_log(2, "Using OSS driver");
          else
            s_log(2, "Unkown driver - using OSS driver");
	}
#elif defined(OS_WIN32)
	{
	  my->drv = new WaveOutDriver();
          if (m_driver_name == "default")
            s_log(2, "Using WaveOut driver");
          else
            s_log(2, "Unkown driver - using WaveOut driver");
	}
#elif defined(OS_DARWIN)
	{
	  my->drv = new CoreAudioOutDriver();
          if (m_driver_name == "default")
            s_log(2, "Using CoreAudio driver");
          else
            s_log(2, "Unkown driver - using CoreAudio driver");
	}
#else
#error No audio driver !
#endif

    }

  assert(my->drv);

  if (device != my->device_number || latency != my->latency 
      || !my->drv->is_open())
    {
      if (my->drv->is_open())
	my->drv->close();
    
      const int num_periods = (int) max(1,
					(int) (0.5 + (((double)latency/1000.)
					  * SAMPLE_RATE) / NUM_SAMPLES));

      try
	{
	  my->drv->open(device,
			SAMPLE_RATE,
			SAMPLE_FORMAT,
			CHANNELS,
			NUM_SAMPLES,
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

  const int num_samples = inst->in_audio->len;
  unsigned char* sample_buffer
    = new unsigned char[num_samples * BYTES_PER_SAMPLE];

  a_cvt_double_to_16le_mono(inst->in_audio->samples,
			    reinterpret_cast<int16_t*>(sample_buffer),
			    num_samples);

  try
    {
      int len = my->drv->write(sample_buffer, num_samples);
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

