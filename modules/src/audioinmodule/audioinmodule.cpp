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

#include "audioinmodule.h"

#include <string>
#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "audioindriver.h"

#if defined(WITH_ASOUNDLIB)
#include "alsadriver.h"
#endif
#if defined(WITH_OSS)
#include "ossdriver.h"
#endif

#if defined(OS_WIN32)
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

#if defined(WITH_OSS)
      if (m_driver_name == "oss"  || m_driver_name == "default")
	{
	  my->drv = new OSSDriver();
	  s_log(2, "Using OSS driver");
	}
      else
#endif
#if defined(WITH_ASOUNDLIB)
        if (m_driver_name == "alsa")
	{
	  my->drv = new AlsaDriver();
	  s_log(2, "Using alsa driver");
	}
#endif
#if defined(WITH_ASOUNDLIB)
      else
	{
	  my->drv = new AlsaDriver();
	  s_log(2, "Unkown driver - using alsa driver");
	}
#elif defined(WITH_OSS)
	{
	  my->drv = new OSSDriver();
	  s_log(2, "Unkown driver - using OSS driver");
	}
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
#else
#error No sound driver!
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

  /*  if (len == 0)
      s_log(2,"nothing to read!");
      else*/
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

