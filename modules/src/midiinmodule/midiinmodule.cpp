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

#include "midiinmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

static logT s_log;

#if defined(WITH_OSS)
#include "ossmidiindriver.h"
#endif
#if defined(WITH_ASOUNDLIB)
#include "alsamidiindriver.h"
#endif

#if defined(OS_WIN32)
#include "wavemidiindriver.h"
#endif


typedef struct _MyInstance {

  int device;
  MidiInDriver* drv;

  char* driver_name;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->device = -1;

  my->driver_name = 0;

  my->drv = 0;

  return my;
}

void destruct(MyInstance* my)
{
  my->device = -1;

  if (my->driver_name)
    {
      delete my->driver_name;
      my->driver_name = 0;
    }

  if (my->drv)
    {
      delete my->drv;
      my->drv = 0;
    }

  free(my);
}

char* strcopy(const char* s)
{
  if (s == 0)
    return 0;

  int l = strlen(s) + 1;

  char* r = new char[l];
  memcpy(r, s, l);

  return r;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int device = trim_int(inst->in_device->number, 0, 256);
  const char* driver_name = inst->in_driver->text;

  if (my->driver_name == 0 ||
      my->drv == 0 ||
      strcmp(driver_name, my->driver_name) != 0)
    {
      delete my->driver_name;
      my->driver_name = strcopy(driver_name);

      if (my->drv)
        {
          my->drv->close();
          delete my->drv;
        }

      if (strcmp(driver_name, "default") == 0)
        {
#if defined(WITH_OSS)
          my->drv = new OSSMidiInDriver();
#elif defined(WITH_ASOUNDLIB)
          my->drv = new OSSMidiInDriver();
#elif defined(OS_WIN32)
          my->drv = new WaveMidiInDriver();
#endif
        }
#if defined(WITH_OSS)
      else if (strcmp(driver_name, "oss") == 0)
        {
          my->drv = new OSSMidiInDriver();
        }
#endif
#if defined(WITH_ASOUNDLIB)
      else if (strcmp(driver_name, "alsa") == 0)
        {
          my->drv = new AlsaMidiInDriver();
        }
#endif
#if defined(OS_WIN32)
      else if (strcmp(driver_name, "wavein") == 0)
        {
          my->drv = new WaveMidiInDriver();
        }
#endif
      else
        {
#if defined(OS_WIN32)
	  my->drv = new WaveMidiInDriver();
	  s_log(2, "Unkown driver - using WaveIn driver");
#elif defined(WITH_OSS)
	  my->drv = new OSSMidiInDriver();
	  s_log(2, "Unkown driver - using OSS driver");
#elif defined(WITH_OSS)
	  my->drv = new AlsaMidiInDriver();
	  s_log(2, "Unkown driver - using alsa driver");
#endif
        }
    }

  if (device != my->device || !my->drv->is_open())
    {
      my->device = device;
	  
      if (my->drv->is_open())
        my->drv->close();
	  
      try
        {
          my->drv->open(device);
        }
      catch (std::exception& e)
        {
          char buf[128];
          snprintf(buf, sizeof(buf), "Error while opening: %s", e.what());
          s_log(0, buf);
        }      
    }

  if (!my->drv->is_open())
    return;
  
  try
    {
      static const int MAX_MSG_LEN = 1024;
      unsigned char buffer[MAX_MSG_LEN];
      int len = my->drv->read(buffer, sizeof(buffer));

      midi_set_buffer(inst->out_r, buffer, len);
    }
  catch (std::exception& e)
    {
      char buf[128];
      snprintf(buf, sizeof(buf), "Error while reading: %s", e.what());
      s_log(0, buf);
    }
  
}
