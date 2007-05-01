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

#include "alsadriver.h"

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdio> // snprintf

#include <alsa/asoundlib.h>

struct AlsaDriver::Impl
{
  Impl(snd_pcm_t* h)
    : handle(h) {}

  snd_pcm_t* handle;
};

//---------------------------------------------------------------------------

AlsaDriver::AlsaDriver()
  : m_impl(new Impl(0))
{
}

AlsaDriver::~AlsaDriver()
{
  if (this->is_open())
    {
      this->close();
    }
}

void AlsaDriver::open(logT /*logger*/,
		      device_id_t device,
                      int sample_rate,
                      sample_format format,
                      int channels)
{
  if (m_impl->handle)
    throw std::logic_error("Device already open");

  snd_pcm_t* capture_handle;
  snd_pcm_hw_params_t* hw_params;
  int err;
  char buffer[256];

  snprintf(buffer, sizeof(buffer), "plughw:%i,0,0", device);

  err = snd_pcm_open(&capture_handle, buffer,
                     SND_PCM_STREAM_CAPTURE, 
                     SND_PCM_NONBLOCK);
  
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot open audio device " 
	 << buffer << " (" << snd_strerror(err)
	 << ")";
  
      throw std::runtime_error(os.str().c_str());
    }

  err = snd_pcm_hw_params_malloc(&hw_params);	   
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot allocate hardware parameter structure ("
	 << snd_strerror(err) << ")";
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
    }

  err = snd_pcm_hw_params_any(capture_handle, hw_params);
  if (err < 0) {
    std::ostringstream os;
    os << "cannot initialize hardware parameter structure ("
       << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }

  err = snd_pcm_hw_params_set_access(capture_handle, hw_params,
                                     SND_PCM_ACCESS_RW_INTERLEAVED);
  if (err < 0) {
    std::ostringstream os;
    os << "cannot set access type ("
       << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }
  
  //TODO: use format
  err = snd_pcm_hw_params_set_format(capture_handle, hw_params,
                                     SND_PCM_FORMAT_S16_LE);
  if (err < 0)
    {
      std::ostringstream os;
      os <<"cannot set sample format ("
	 << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }
	
  err = snd_pcm_hw_params_set_rate(capture_handle, hw_params, 
				   sample_rate, 0);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set sample rate ("
	 << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());    
    }

  err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, channels);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set channel count ("
	 << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
    }
	
  err = snd_pcm_hw_params(capture_handle, hw_params);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set parameters ("
	 << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
  }
	
  snd_pcm_hw_params_free(hw_params);
	
  err = snd_pcm_prepare(capture_handle);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot prepare audio interface for use ("
	 << snd_strerror(err) << ")";
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
    }

  m_impl->handle = capture_handle;
}


void AlsaDriver::close()
 {
  if (!this->is_open())
    return;

  snd_pcm_close(m_impl->handle);
  m_impl->handle = 0;
 }

int AlsaDriver::read(unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  int err = snd_pcm_readi(m_impl->handle, data, num_samples);
  if (err == -EPIPE) // buffer overrun
    {
      int e;
      // just restart the device
      //printf("restarting device\n");
      e = snd_pcm_prepare(m_impl->handle);
      if (e < 0)
        {
	  std::ostringstream os;
	  os << "[restart] cannot prepare audio interface for use ("
	     << snd_strerror(e) << ")";
          throw std::runtime_error(os.str().c_str());
        }
      return 0;
    }
  else if (err == -EAGAIN) // nothing to read
    {
      //printf("nothing to read\n");
      return 0;
    }
  else if (err < 0)
    {
      std::ostringstream os;
      os << "read from audio interface failed ("
	 << snd_strerror(err) << ")";
      throw std::runtime_error(os.str().c_str());      
    }

  //  printf("read %i samples\n", err);
  return err;
}

bool AlsaDriver::is_open() const
{
  return m_impl->handle != 0;
}
//---------------------------------------------------------------------------
