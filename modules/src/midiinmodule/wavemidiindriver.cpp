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

#include "wavemidiindriver.h"

#include <stdexcept>

#include <windows.h>
#include "midiutil.h"

//-------------------------------------------------------------------------

static HMIDIIN s_midi_in;
static MIDIHDR s_midi_hdr;

//stores the long (system exclusive) messages
#define MIDI_LONG_BUF_SIZE 1024
static unsigned char s_midi_longbuf[MIDI_LONG_BUF_SIZE];

//stores received midi bytes
#define MIDI_BUF_SIZE 1024
static unsigned char s_midi_buf[MIDI_BUF_SIZE];
static int s_midi_buf_len;
static int s_init_finnished = 0;

static CRITICAL_SECTION s_critical_section;

#define snprintf _snprintf

//-------------------------------------------------------------------------

static void CALLBACK midiCallBack(HMIDIIN hMidiIn,
								  UINT wMsg,
								  DWORD dwInstance, 
								  DWORD dwParam1,
								  DWORD dwParam2);
static void midi_init(int device);
static void midi_shutdown();

static int read_buffer(unsigned char* data, int data_size);
//puts a byte into the static buffer
static void put_bytes(const unsigned char* bytes, int len);

//-------------------------------------------------------------------------

struct WaveMidiInDriver::Impl
{
	Impl() : open(false)
	{		
		++s_ref_count; 
	}
	
	~Impl()
	{ 
		--s_ref_count;	
	}
	
	bool open;
	
	static int s_ref_count;
};

int WaveMidiInDriver::Impl::s_ref_count = 0;

//-------------------------------------------------------------------------

WaveMidiInDriver::WaveMidiInDriver()
: m_impl(new Impl())
{
}

WaveMidiInDriver::~WaveMidiInDriver()
{
	if (this->is_open())
		close();
}

void WaveMidiInDriver::open(device_id_t device)
{
	if (this->is_open())
		throw std::logic_error("Device already open");
	
	if (m_impl->s_ref_count == 1)
	{
		// can throw
		midi_init(device);
	}
	
	m_impl->open = true;
}

void WaveMidiInDriver::close()
{
	if (!this->is_open())
		throw std::logic_error("Device not open");
	
	if (m_impl->s_ref_count == 1)
	{
		midi_shutdown();
	}
	
	m_impl->open = false;
}

int WaveMidiInDriver::read(unsigned char* data, int data_size)
{
	if (!this->is_open())
		throw std::logic_error("Device not open");
	
	return read_buffer(data, data_size);
}

bool WaveMidiInDriver::is_open() const
{
	return m_impl->open;
}

//------------------------------------------------------------------

static void midi_init(int device_num)
{
	InitializeCriticalSection(&s_critical_section);		
	EnterCriticalSection(&s_critical_section);	
	
	s_midi_buf_len = 0;
	
	int numDevs = midiInGetNumDevs();
	
	if (numDevs == 0)
	{		  
		throw std::runtime_error("No Midi Devices found");		
	}
	if (device_num >= numDevs || device_num < 0)
	{
		throw std::runtime_error("Invalid device number");
	}
	
	// to protect ourselves from midi-messages while init is not done yet
	s_init_finnished = 0;
	
	MMRESULT res = midiInOpen(&s_midi_in,
		device_num,
		(DWORD) midiCallBack,
		(DWORD) 0,
		CALLBACK_FUNCTION);
	
	if (MMSYSERR_NOERROR != res)
	{
		char buffer[256];
		TCHAR errorText[256];
		midiInGetErrorText(res,errorText,255);
		snprintf(buffer, sizeof(buffer),
			"Failed to open MIDI input device: %s", errorText);
		
		throw std::runtime_error(buffer);
	}  		
	
	s_midi_hdr.lpData         = (char*)s_midi_longbuf;
	s_midi_hdr.dwBufferLength = MIDI_LONG_BUF_SIZE;
	s_midi_hdr.dwFlags        = 0;
	
	res = midiInPrepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
	if (MMSYSERR_NOERROR != res)
	{				
		midiInReset(s_midi_in);
		midiInClose(s_midi_in);
		
		char buffer[256];
		TCHAR errorText[256];
		midiInGetErrorText(res,errorText,255);
		snprintf(buffer, sizeof(buffer),
			"Failed to prepare MIDI header: %s", errorText);		
		throw std::runtime_error(buffer);
	}  
	
	
	res = midiInAddBuffer(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
	if (MMSYSERR_NOERROR != res)
	{						
		midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
		midiInReset(s_midi_in);
		midiInClose(s_midi_in);
		
		char buffer[256];
		TCHAR errorText[256];
		midiInGetErrorText(res,errorText,255);
		snprintf(buffer, sizeof(buffer),
			"Failed to add MIDI buffer: %s", errorText);		
		throw std::runtime_error(buffer);
	}  
	
	res = midiInStart(s_midi_in);
	if (MMSYSERR_NOERROR != res)
	{				
		midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
		midiInReset(s_midi_in);
		midiInClose(s_midi_in);
		
		char buffer[128];
		TCHAR errorText[256];
		midiInGetErrorText(res,errorText,255);
		snprintf(buffer, sizeof(buffer),
			"Failed to start MIDI input device: %s", errorText);		
		
		throw std::runtime_error(buffer);
	}  
	
	/*{
	char buffer[128];
	snprintf(buffer, sizeof(buffer),"Number of MIDI Devices: %d",
	numDevs);
	s_log(2, buffer);
	snprintf(buffer, sizeof(buffer),"Initialization ... Success!!");
	s_log(2, buffer);
}*/
	
	s_init_finnished = 1;
	LeaveCriticalSection(&s_critical_section);
}

//--------------------------------------------------------------------

static void midi_shutdown()
{	
	EnterCriticalSection(&s_critical_section);
	s_init_finnished = 0;
	
	midiInStop(s_midi_in);
	
	midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
	
	midiInReset(s_midi_in);
	midiInClose(s_midi_in);
	LeaveCriticalSection(&s_critical_section);
	
	DeleteCriticalSection(&s_critical_section);
}

//--------------------------------------------------------------------

static void CALLBACK midiCallBack(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
								  DWORD dwParam1, DWORD dwParam2)
{	
	unsigned char midiStat; /* MIDI_CMD_XXX */	
	unsigned char midiParam1; /* je nach commando andere bedeutung */
	unsigned char midiParam2; /* je nach commando andere bedeutung */
	unsigned char buf[3];
	
	//MidiType* buffer = (MidiType*) dwInstance;
	
	// don't do anything if init has not finnished yet!
	if (!s_init_finnished)
		return;
	
	midiStat   = (unsigned char) ((dwParam1 & 0x000000ff) >> 0);
	midiParam1 = (unsigned char) ((dwParam1 & 0x0000ff00) >> 8);
	midiParam2 = (unsigned char) ((dwParam1 & 0x00ff0000) >> 16);
	
	switch(wMsg)
	{
	case MIM_OPEN:
		break;
		
	case MIM_ERROR:
		{
			char buffer[64];
			snprintf(buffer, sizeof(buffer),
				"wMsg == MIM_ERROR at midiinmodule::midiCallBack!");
			printf("%s\n", buffer);
		} break;
		
	case MIM_DATA:
		{
			int len = midi_length_of_message(midiStat);
			if (len < 0)
			{
				char buffer[64];
				snprintf(buffer, sizeof(buffer),
					"midi: unknown: %i %i %i", midiStat,
					midiParam1, midiParam2);
				printf("%s\n", buffer);
				return;
			}
			switch (len)
			{
			case 0:
			  buf[0] = midiStat;
			  put_bytes(buf, 1);
			  break;
			case 1:
			  buf[0] = midiStat;
			  buf[1] = midiParam1;
			  put_bytes(buf, 2);
			  break;
			case 2:
			  buf[0] = midiStat;
			  buf[1] = midiParam1;
			  buf[2] = midiParam2;
			  put_bytes(buf, 3);
			  break;
			default:
				{
					char buffer[64];
					snprintf(buffer, sizeof(buffer),
						"unknown length at midiinmodule::midiCallBack: %i",
						len);
					printf("%s\n", buffer);
				}
			}		
		} break;
	case MIM_LONGDATA:
		{
			MIDIHDR* hdr = (MIDIHDR*) dwParam1;
			//TODO do we need to insert a status byte?
			put_bytes((unsigned char*) hdr->lpData, hdr->dwBytesRecorded);
			
			//TODO do we need to reinsert the buffer?
		}break;
		
	default:
		{
			char buffer[64];
			snprintf(buffer, sizeof(buffer),
				"Unknown wMsg at midiinmodule::midiCallBack: %i", wMsg);
			printf("%s\n", buffer);
		}
	}
}

//--------------------------------------------------------------------

static int read_buffer(unsigned char* data, int data_size)
{
	EnterCriticalSection(&s_critical_section);
	int len = 0;
	if (s_midi_buf_len <= data_size)
	{
		len = s_midi_buf_len;
		memcpy(data, s_midi_buf, len);				
	}
	else
	{
		len = data_size;
		memcpy(data, s_midi_buf, len);
		memmove(s_midi_buf, s_midi_buf+data_size, s_midi_buf_len - data_size);
	}
	
	s_midi_buf_len -= len;
	
	LeaveCriticalSection(&s_critical_section);
	return len;
}

static void put_bytes(const unsigned char* bytes, int len)
{
	EnterCriticalSection(&s_critical_section);
	
	if (s_midi_buf_len + len <= MIDI_BUF_SIZE)
	  {
	    memcpy(s_midi_buf+s_midi_buf_len, bytes, len);
	    s_midi_buf_len += len;
	  }
	else
	{
	/*char buffer[64];
	snprintf(buffer, sizeof(buffer),
	"Buffer overflow at midiinmodule::put_byte, ignoring %i", byte);
		s_log(0, buffer)*/;
	}
	LeaveCriticalSection(&s_critical_section);
}

//--------------------------------------------------------------------
