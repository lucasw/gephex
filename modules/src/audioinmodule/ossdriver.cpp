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

#include "ossdriver.h"

//#include <iostream>
#include <stdexcept>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

struct OSSDriver::Impl
{
  Impl() : fd(-1), bytes_per_sample(-1) {}

  int fd;
  int bytes_per_sample;
};

static int open_device(const char* device_name, int* fd);
static void close_device(int *fd);
static int read_data(int fd, unsigned char* buf, int buf_len);

//---------------------------------------------------------------------------

OSSDriver::OSSDriver()
  : m_impl(new Impl())
{
}

OSSDriver::~OSSDriver()
{
  if (this->is_open())
    this->close();
}

void OSSDriver::open(logT /*logger*/,
		     device_id_t device,
                     int sample_rate,
                     sample_format format,
                     int channels)
{
  if (this->is_open())
    throw std::logic_error("Device already open");
  
  char device_string[64];
  int fd;
  snprintf(device_string, sizeof(device_string), "/dev/dsp%i", device);
  if (!open_device(device_string, &fd))
    {
      std::string msg = "Cannot open device: '";
      msg += device_string;
      msg += "'";
      throw std::runtime_error(msg.c_str());
    }

  int bytes_per_sample;
  try
    {
      // init to samplerate etc. pp.
      int f, f_o;
      if (format == SF_16LE)
	{
	  f = f_o = AFMT_S16_LE;
	  bytes_per_sample = 2;
	}
      else
	throw std::invalid_argument("Unknown sample format");

      if (ioctl(fd, SNDCTL_DSP_SETFMT, &f) == -1)
	{
	  throw std::runtime_error("Error when setting audio format");
	}
      if (f != f_o) 
	{
	  throw std::runtime_error("Sample format not supported");
	}
  
      int ch = channels;
      if (ioctl(fd, SNDCTL_DSP_CHANNELS, &ch) == -1)
	{
	  throw std::runtime_error("Error when setting channels");
	}
      if (ch != channels)
	{
	  throw std::runtime_error("Channels not supported");
	}
  
      int speed = sample_rate;
      if (ioctl(fd, SNDCTL_DSP_SPEED, &speed)==-1)
	{
	  throw std::runtime_error("Error when setting sample rate");
	}
      if ( speed != sample_rate)
	{
	  throw std::runtime_error("sample rate not supported");
	}

      // set fragments
      // note: periods are called fragments in the OSS world
      // the parameter has the number of fragments in teh upper 16 bit
      // and the logarithm base 2 of the fragment size in the lower
      // 16 bit.
      int frag;
      const int PERIOD_SIZE = 128;
      frag = (sample_rate / (10*PERIOD_SIZE)) << 16;
      int bytes_per_period = PERIOD_SIZE * bytes_per_sample;
      int power = 0;
      // determine power = min {k | 2^k >= bytes_per_period}
      while (1 << power < bytes_per_period)
        ++power;

      frag |= power;

      if (ioctl(fd, SNDCTL_DSP_SETFRAGMENT, &frag) == -1)
        {
	  throw std::runtime_error("Error when setting buffer");
	}
      // check fragment size
      audio_buf_info info;
      if (ioctl(fd, SNDCTL_DSP_GETISPACE, &info) == -1)
        {
	  throw std::runtime_error("Error when querying buffers");
	}
      /*      std::cout << "fragment size = " << info.fragsize << "\n";
      std::cout << "frags total   = " << info.fragstotal << "\n";
      std::cout << "fragments     = " << info.fragments << "\n";*/

      int frag_size;
      if (ioctl(fd, SNDCTL_DSP_GETBLKSIZE, &frag_size) == -1)
        {
	  throw std::runtime_error("Error when querying fragment size");
	}
      //      std::cout << "fragment size = " << frag_size << "\n";
    }
  catch (...)
    {
      this->close();
      throw;
    }

  m_impl->fd = fd;
  m_impl->bytes_per_sample = bytes_per_sample;
}


void OSSDriver::close()
{
  if (!this->is_open())
    return;

  close_device(&m_impl->fd);
  m_impl->fd = -1;
  m_impl->bytes_per_sample = -1;
}

int minimum(int a, int b)
{
  return (a < b) ? a : b;
}

int OSSDriver::read(unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  // check fragment size
  audio_buf_info info;
  if (ioctl(m_impl->fd, SNDCTL_DSP_GETISPACE, &info) == -1)
    {
      throw std::runtime_error("Error when querying buffers");
    }
  //std::cout << "fragment size = " << info.fragsize << "\n";
  //  std::cout << "frags total   = " << info.fragstotal << "\n";
  //  std::cout << "fragments     = " << info.fragments << "\n";
  int bytes_to_read = minimum(info.fragments * info.fragsize,
                              num_samples*m_impl->bytes_per_sample);

  int len = read_data(m_impl->fd, data,
                      bytes_to_read);

  if (len < 0)
    throw std::runtime_error("Error at read");

  return len / m_impl->bytes_per_sample;
}

bool OSSDriver::is_open() const
{
  return m_impl->fd != -1;
}

//---------------------------------------------------------------------------

// returns 1 on success
static int open_device(const char* device_name, int* fd)
{

  // open the OSS device for reading
  *fd = open(device_name, O_RDONLY, 0);
  if (*fd < 0)
      return 0;

  return 1;
}

static void close_device(int *fd)
{
  if (*fd != -1)
    {
      close(*fd);
      *fd = -1;
    }
}

static int read_data(int fd, unsigned char* buf, int buf_len)
{
  fd_set readfds;
  int len;

  if (fd < 0)
    return -1;

  {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(fd,&readfds);
    select(fd+1,&readfds,0,0,&tv);
    //TODO: handle EINTR
  }
  
  if (FD_ISSET(fd, &readfds))
    {
      errno = 0;
      //      do
	{
	  len = read(fd, buf, buf_len);
	  if (len == -1 && errno != EINTR)
	    {
	      return -1;
	    }
	  else
	    {
	      return len;
	    }
        }// while (errno != EINTR);
    }
  else
    {
      return 0;
    }
}

