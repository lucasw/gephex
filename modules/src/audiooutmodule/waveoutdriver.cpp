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

#include "waveoutdriver.h"

#include <stdexcept>
#include <stdio.h>
#include <windows.h>

#include "outbuffer.h"

//--------------------------------------------------------------------------

struct WaveOutDriver::Impl
{
  Impl() : handle(0), buf(0), bytes_per_sample(0) {}

  HWAVEOUT handle;
  struct out_buffer* buf;
  int bytes_per_sample;
};

//--------------------------------------------------------------------------

WaveOutDriver::WaveOutDriver()
  : m_impl(new Impl())
{
}

WaveOutDriver::~WaveOutDriver()
{
  if (this->is_open())
    this->close();
}

void WaveOutDriver::open(device_id_t device,
			 int sample_rate,
			 sample_format form,
			 int channels,
			 int num_samples,
			 int num_periods)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  WAVEFORMATEX format;
  MMRESULT res;

  int bytes_per_sample;
  if (form == SF_16LE)
    bytes_per_sample = 2;
  else
    throw std::invalid_argument("Unkown sample format");


  // set device parameters
  format.wFormatTag     = WAVE_FORMAT_PCM;
  format.nChannels      = channels;
  format.nSamplesPerSec = sample_rate;
  format.wBitsPerSample = bytes_per_sample*8;
  format.nBlockAlign    = format.nChannels*(format.wBitsPerSample / 8);
  
  res = waveOutOpen(&m_impl->handle, device, &format, 0, 0, CALLBACK_NULL);
  if (res != MMSYSERR_NOERROR)
  {
    char error_msg[128];    
    waveOutGetErrorText(res, error_msg, sizeof(error_msg));
    std::string msg = "waveOutOpen failed: ";
    msg += error_msg;

    throw std::runtime_error(msg.c_str());
  }
  //s_log(2,"Opened Device");

  // create the memory buffer
  m_impl->bytes_per_sample = bytes_per_sample;
  m_impl->buf = outb_create(m_impl->handle, 
						    num_samples * bytes_per_sample,
							num_periods);

  if (m_impl->buf == 0)
  {    
    throw std::runtime_error("Could not create the outbuffer!");
  }

  /*{
	  unsigned short volume[2];
	  waveOutGetVolume(m_impl->handle, volume);
	  printf("Volume = (%f,%f)\n", volume[0] / ((double)0xffff-1),
								   volume[1] / ((double)0xffff-1));
  }*/
}


void WaveOutDriver::close()
{
  if (!this->is_open())
    return;

  MMRESULT res = waveOutReset(m_impl->handle);
  if (res != MMSYSERR_NOERROR)
  {
    char error_msg[128];
   
    waveOutGetErrorText(res, error_msg, sizeof(error_msg));
    printf("waveOutReset failed: %s!", error_msg);    
  }

  outb_destroy(m_impl->buf);
  res = waveOutClose(m_impl->handle);
  if (res != MMSYSERR_NOERROR)
  {
    char error_msg[128];
   
    waveOutGetErrorText(res, error_msg, sizeof(error_msg));
    printf("waveOutClose failed: %s!", error_msg);    
  }
  
  m_impl->handle = 0;
}

int WaveOutDriver::write(const unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  char error_text[256];

  int bytes_written = outb_write(m_impl->buf, data,
				 num_samples*m_impl->bytes_per_sample,
				 error_text, sizeof(error_text));
  if (bytes_written < 0)
    {
      // TODO: evaluate error code
      throw std::runtime_error(error_text);
    }
  else
    return bytes_written / m_impl->bytes_per_sample;
}

bool WaveOutDriver::is_open() const
{
  return m_impl->handle != 0;
}


//--------------------------------------------------------------------------
/*
void print_caps(int id, WAVEOUTCAPS* caps)
{
	int f, c;
	char buffer[1024];

	sprintf(buffer, "Caps for device number %i:", id);
	s_log(2, buffer);
	_snprintf(buffer, sizeof(buffer), "Name: %s", caps->szPname);
	s_log(2, buffer);
	s_log(2,"Channels : ");
	c = caps->wChannels;
	if (c == 1)
		s_log(2,"mono");
	else if (c == 2)
		s_log(2,"stereo");
	else {
		sprintf(buffer, "unknown! (%i)", c);
		s_log(2, buffer);
	}

	s_log(2,"Supported Formats:");
	f = caps->dwFormats;
	if (f & WAVE_FORMAT_1M08)
		s_log(2,"11.025 kHz, mono, 8-bit");
	if (f & WAVE_FORMAT_1M16)
		s_log(2,"11.025 kHz, mono, 16-bit");
	if (f & WAVE_FORMAT_1S08)
		s_log(2,"11.025 kHz, stereo, 8-bit");
	if (f & WAVE_FORMAT_1S16)
		s_log(2,"11.025 kHz, stereo, 16-bit");
	if (f & WAVE_FORMAT_2M08)
		s_log(2,"22.05 kHz, mono, 8-bit");
	if (f & WAVE_FORMAT_2M16)
		s_log(2,"22.05 kHz, mono, 16-bit");
	if (f & WAVE_FORMAT_2S08)
		s_log(2,"22.05 kHz, stereo, 8-bit");
	if (f & WAVE_FORMAT_2S16)
		s_log(2,"22.05 kHz, stereo, 16-bit");
	if (f & WAVE_FORMAT_4M08)
		s_log(2,"44.1 kHz, mono, 8-bit");
	if (f & WAVE_FORMAT_4M16)
		s_log(2,"44.1 kHz, mono, 16-bit");
	if (f & WAVE_FORMAT_4S08)
		s_log(2,"44.1 kHz, stereo, 8-bit");
	if (f & WAVE_FORMAT_4S16)
		s_log(2,"44.1 kHz, stereo, 16-bit");

}

int info()
{
	int num_devs = waveOutGetNumDevs();
	int i;
	char buffer[1024];

	_snprintf(buffer, sizeof(buffer), "Number of devices: %i", num_devs);
	s_log(2, buffer);

	for (i = 0; i < num_devs; ++i)
	{
		MMRESULT r;
		WAVEOUTCAPS caps;

		r = waveOutGetDevCaps(i, &caps, sizeof(caps));
		
		if (r != MMSYSERR_NOERROR) {
			sprintf(buffer, "Error at id %i!", i);
			s_log(0, buffer);
		}
		else
			print_caps(i, &caps);
	}

	return num_devs;
}
*/
