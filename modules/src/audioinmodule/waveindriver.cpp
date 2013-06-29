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

#include "waveindriver.h"

#include <sstream>
#include <stdexcept>

#include <windows.h>

#include "audiobuffer.h"

#define CHUNK_SIZE 64
#define NUM_CHUNKS 128

struct WaveInDriver::Impl
{
  Impl()
    : handle(0), buf(0) {}

  HWAVEIN handle;
  struct audio_buffer* buf;
};

//--------------------------------------------------------------------------

WaveInDriver::WaveInDriver()
  : m_impl(new Impl())
{
}

WaveInDriver::~WaveInDriver()
{
  if (this->is_open())
    this->close();
}

void WaveInDriver::open(logT /*logger*/,
			device_id_t device,
			int sample_rate,
			sample_format form,
			int channels)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  WAVEFORMATEX format;
  MMRESULT res;

  int bytes_per_sample;
  if (form == SF_16LE)
    bytes_per_sample = 2;
  else
    throw std::invalid_argument("Unknown sample format");

  format.wFormatTag     = WAVE_FORMAT_PCM;
  format.nChannels      = channels;
  format.nSamplesPerSec = sample_rate;
  format.wBitsPerSample = bytes_per_sample*8;
  format.nBlockAlign    = format.nChannels*(format.wBitsPerSample / 8);
  
  res = waveInOpen(&m_impl->handle, device, &format, 0, 0, CALLBACK_NULL);
  if (res != MMSYSERR_NOERROR)
  {
    char error_msg[128];
    char buffer[256];
    waveInGetErrorText(res, error_msg, sizeof(error_msg));
    _snprintf(buffer, sizeof(buffer), "waveInOpen failed: %s!", error_msg);

    throw std::runtime_error(buffer);
  }
  //s_log(2,"Opened Device");

  m_impl->buf = ab_create(m_impl->handle, CHUNK_SIZE*bytes_per_sample, NUM_CHUNKS);
  
  waveInStart(m_impl->handle);
}


void WaveInDriver::close()
{
  if (!this->is_open())
    return;

  waveInReset(m_impl->handle);
  ab_destroy(m_impl->buf);
  waveInClose(m_impl->handle);
  
  m_impl->handle = 0;
  m_impl->buf    = 0;  
}

int WaveInDriver::read(unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");
  int samples_read = 0;
  while (ab_block_ready(m_impl->buf) &&
	 samples_read < num_samples - CHUNK_SIZE)
    {
      samples_read += ab_get_block(m_impl->buf,
								   data + samples_read*2, 
								   num_samples*2 - samples_read*2) / 2;
    }
  return samples_read;
}

bool WaveInDriver::is_open() const
{
  return m_impl->handle != 0;
}

//--------------------------------------------------------------------------
/*
void print_caps(int id, WAVEINCAPS* caps)
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
	int num_devs = waveInGetNumDevs();
	int i;
	char buffer[1024];

	_snprintf(buffer, sizeof(buffer), "Number of devices: %i", num_devs);
	s_log(2, buffer);

	for (i = 0; i < num_devs; ++i)
	{
		MMRESULT r;
		WAVEINCAPS caps;

		r = waveInGetDevCaps(i, &caps, sizeof(caps));
		
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
