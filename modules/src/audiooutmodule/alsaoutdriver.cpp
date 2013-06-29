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

#include "alsaoutdriver.h"

#include <sstream>
#include <cstdio>
#include <stdexcept>

#include <alsa/asoundlib.h>

#include "basic_types.h"

#define BUFFER_SIZE 10240

struct AlsaOutDriver::Impl
{
  Impl() : handle(0), buf_pos(0), bytes_per_sample(0) {}

  snd_pcm_t* handle;

  int_16 buffer[BUFFER_SIZE];
  int buf_pos;
  int bytes_per_sample;
};

//---------------------------------------------------------------------------

AlsaOutDriver::AlsaOutDriver()
  : m_impl(new Impl())
{
}

AlsaOutDriver::~AlsaOutDriver()
{
  if (this->is_open())
    this->close();
}

void AlsaOutDriver::open(device_id_t device,
			 int sample_rate,
			 sample_format format,
			 int channels,
			 int num_samples,
			 int num_periods)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  snd_pcm_t* handle;
  snd_pcm_hw_params_t* hw_params;
  int err;
  char buffer[32];

  snprintf(buffer, sizeof(buffer), "plughw:%i,0,0", device);

  err = snd_pcm_open(&handle, buffer,
                     SND_PCM_STREAM_PLAYBACK, 
                     SND_PCM_NONBLOCK);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot open audio device " 
	 << buffer << "(" << snd_strerror(err)
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

  err = snd_pcm_hw_params_any(handle, hw_params);
  if (err < 0) {
    std::ostringstream os;
    os << "cannot initialize hardware parameter structure ("
       << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }

  err = snd_pcm_hw_params_set_access(handle, hw_params,
                                      SND_PCM_ACCESS_RW_INTERLEAVED);
  if (err < 0) {
    std::ostringstream os;
    os << "cannot set access type (" << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }
  
  //TODO: use format
  int bytes_per_sample = 2;
  err = snd_pcm_hw_params_set_format(handle, hw_params,
                                     SND_PCM_FORMAT_S16_LE);
  if (err < 0)
    {
      std::ostringstream os;
      os <<"cannot set sample format (" << snd_strerror(err) << ")";
    snd_pcm_hw_params_free(hw_params);
    snd_pcm_close(m_impl->handle);
    throw std::runtime_error(os.str().c_str());
  }
	
  err = snd_pcm_hw_params_set_rate(handle, hw_params, 
                                        sample_rate, 0);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set sample rate (" << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());    
    }

  err = snd_pcm_hw_params_set_channels(handle, hw_params, channels);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set channel count (%s)" << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
    }

  /* Set number of periods. Periods used to be called fragments. */ 
  err = snd_pcm_hw_params_set_periods(handle, hw_params, num_periods, 0);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set periods (%s)" << snd_strerror(err) << ")";

      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(handle);
      throw std::runtime_error(os.str().c_str());
  }

  /* Set buffer size (in frames). The resulting latency is given by */
  /* latency = periodsize * periods / (rate * bytes_per_frame)     */
  err = snd_pcm_hw_params_set_buffer_size(handle, hw_params, 
                                          (num_samples*num_periods)
                                          / bytes_per_sample);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set buffersize (%s)" << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(handle);
      throw std::runtime_error(os.str().c_str());
  }
	
  err = snd_pcm_hw_params(handle, hw_params);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot set parameters (" << snd_strerror(err) << ")";
      snd_pcm_hw_params_free(hw_params);
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
  }
	
  snd_pcm_hw_params_free(hw_params);
	
  err = snd_pcm_prepare(handle);
  if (err < 0)
    {
      std::ostringstream os;
      os << "cannot prepare audio interface for use ("
	 << snd_strerror(err) << ")";
      snd_pcm_close(m_impl->handle);
      throw std::runtime_error(os.str().c_str());
    }

  m_impl->handle = handle;
  m_impl->buf_pos = 0;
  m_impl->bytes_per_sample = bytes_per_sample;
}


void AlsaOutDriver::close()
{
  if (!this->is_open())
    return;

  snd_pcm_close(m_impl->handle);
  m_impl->handle = 0;
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int AlsaOutDriver::write(const unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  int len = min(BUFFER_SIZE - m_impl->buf_pos - 1, num_samples);

  memcpy(m_impl->buffer + m_impl->buf_pos,
	 data,
	 len * m_impl->bytes_per_sample);

  m_impl->buf_pos += len;
  assert(m_impl->buf_pos  < BUFFER_SIZE);

  int err = snd_pcm_writei(m_impl->handle, m_impl->buffer, m_impl->buf_pos);
  if (err == -EPIPE) // buffer underrun
    {
      // just restart the device
      //      printf("restarting device\n");
      int e = snd_pcm_prepare(m_impl->handle);
      if (e < 0)
        {
	  std::string msg = "cannot prepare audio interface for use )";
	  msg += snd_strerror(e);
	  msg += ")";
	  throw std::runtime_error(msg.c_str());
        }
      return 0;
    }
  else if (err == -EAGAIN) // nothing to read
    {
      //printf("could not write (EAGAIN)\n");
      return 0;
    }
  else if (err < 0)
    {
      std::string msg = "write to audio interface failed (";
      msg += snd_strerror(err);
      msg += ")";
      throw std::runtime_error(msg.c_str());
    }

  //  printf("wrote %i samples (%i -> %i)\n", err, m_impl->buf_pos, m_impl->buf_pos-err);
  assert(err <= m_impl->buf_pos);
  memmove(m_impl->buffer, m_impl->buffer+err, (m_impl->buf_pos-err)*
	  m_impl->bytes_per_sample);
  m_impl->buf_pos -= err;

  return err;
}

bool AlsaOutDriver::is_open() const
{
  return m_impl->handle != 0;
}

//---------------------------------------------------------------------------
