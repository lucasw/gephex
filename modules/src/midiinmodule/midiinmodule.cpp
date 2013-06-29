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

#include <map>
#include <string>
#include <cassert>
#include <algorithm>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

static logT s_log;

#if defined(WITH_OSS)
#include "ossmidiindriver.h"
#endif
#if defined(WITH_ASOUNDLIB)
#include "alsamidiindriver.h"
#include "alsaseqmidiindriver.h"
#endif

#if defined(OS_WIN32)
#include "wavemidiindriver.h"
#endif

#if defined(OS_DARWIN)
#include "macosxmidiindriver.h"
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

namespace
{
  MidiInDriver* create_driver(const char* driver_name)
  {
    if (strcmp(driver_name, "default") == 0)
      {
#if defined(WITH_ASOUNDLIB)
	return new AlsaSeqMidiInDriver();
#elif defined(WITH_OSS)
	return new OSSMidiInDriver();
#elif defined(OS_WIN32)	  
	return new WaveMidiInDriver();
#elif defined(OS_DARWIN)
	return new MacOSXMidiInDriver();
#endif
      }
#if defined(WITH_OSS)
    else if (strcmp(driver_name, "oss") == 0)
      {
	return new OSSMidiInDriver();
      }
#endif
#if defined(WITH_ASOUNDLIB)
    else if (strcmp(driver_name, "alsa") == 0)
      {
	return new AlsaMidiInDriver();
      }
    else if (strcmp(driver_name, "alsaseq") == 0)
      {
	return new AlsaSeqMidiInDriver();
      }
#endif
#if defined(OS_WIN32)
    else if (strcmp(driver_name, "wavein") == 0)
      {
	return new WaveMidiInDriver();
      }
#endif
#if defined(OS_DARWIN)
    else if (strcmp(driver_name, "coremidi") == 0)
      {
	return new MacOSXMidiInDriver();
      }
#endif
    else
      {
#if defined(OS_WIN32)
	return new WaveMidiInDriver();
	s_log(2, "Unkown driver - using WaveIn driver");
#elif defined(WITH_OSS)
	return new OSSMidiInDriver();
	s_log(2, "Unkown driver - using OSS driver");
#elif defined(WITH_ALSA)
	return new AlsaMidiInDriver();
	s_log(2, "Unkown driver - using alsa driver");
#elif defined(OS_DARWIN)
	return new MacOSXMidiInDriver();
	s_log(2, "Unkown driver - using coremidi driver");
#endif
      }
  }

  typedef std::pair<int, std::string> DriverKey;
  typedef std::pair<MidiInDriver*, int> DriverData;

  typedef std::map<DriverKey, DriverData> DriverMap;

  static DriverMap s_map;

  MidiInDriver* get_driver(const char* driver_name,
			   int device_id)
  {
    DriverMap::const_iterator it = s_map.find(DriverKey(device_id,
							std::string(driver_name)));
    if (it != s_map.end())
      {
	DriverData data = it->second;
	data.second += 1;  // Increase reference count
	return data.first;
      }
    else
      {
	MidiInDriver* drv = create_driver(driver_name);
	assert(drv != 0);

	s_map.insert(std::make_pair(DriverKey(device_id, std::string(driver_name)),
				    DriverData(drv, 1)));
	return drv;
      }
  }

  void release_driver(MidiInDriver* drv,
		      const char* driver_name,
		      int device_id)
  {
    DriverMap::iterator it = s_map.find(DriverKey(device_id,
						  std::string(driver_name)));

    assert(it != s_map.end());

    DriverData& data = it->second;

    assert(data.first == drv);
    assert(data.second >= 1);
    data.second -= 1;

    if (data.second == 0)
      {
	s_map.erase(it);
	delete drv;
      }
  }
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int device = trim_int(inst->in_device->number, 0, 256);
  const char* driver_name = inst->in_driver->text;

  try
    {
      
      if (my->driver_name == 0 ||
	  my->drv == 0 ||
	  strcmp(driver_name, my->driver_name) != 0)
	{
	  delete[] my->driver_name;
	  my->driver_name = strcopy(driver_name);

	  if (my->drv != 0)
	    release_driver(my->drv, my->driver_name, my->device);

	  my->drv = get_driver(my->driver_name, my->device);
	}

      assert(my->drv != 0);
      
      if (device != my->device || !my->drv->is_open())
	{
	  my->device = device;
	  
	  if (my->drv->is_open())
	    my->drv->close();

	  assert(!my->drv->is_open());
	  
	  try
	    {
	      my->drv->open(device);
	    }
	  catch (std::exception& e)
	    {
	      char buf[128];
	      snprintf(buf, sizeof(buf), "Error while opening: %s", e.what());
	      s_log(0, buf);
	      throw;
	    }
	  assert(my->drv->is_open());
	}

      assert(my->drv->is_open());

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
	  throw;
	}
    }
  catch (std::exception& e)
    {
      midi_set_buffer(inst->out_r, 0, 0);
    }
}
