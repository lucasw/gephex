#include "midiinmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

static logT s_log;

#if defined(OS_POSIX)
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static int openDevice(const char* device_name, int* fd);
static void closeDevice(int *fd);
static void readData(int fd, MidiType* buffer);

typedef struct _MyInstance {

  StringType oldDevice;
  int fd;

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

  string_initInstance(&my->oldDevice);
  my->fd = -1;

  return my;
}

void destruct(MyInstance* my)
{
  string_destroyInstance(&my->oldDevice);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  if (strcmp(inst->in_device->text, my->oldDevice.text) != 0)
    {
      closeDevice(&my->fd);
      openDevice(inst->in_device->text, &my->fd);
      string_assign(&my->oldDevice, inst->in_device);
    }

  readData(my->fd, inst->out_r);
}

// helper functions

// returns 1 on success
static int openDevice(const char* device_name, int* fd)
{

  // open the OSS device for reading
  *fd = open(device_name, O_RDONLY, 0);
  if (*fd < 0)
    {
      char buffer[128];
      snprintf(buffer, sizeof(buffer),
               "Error: cannot open '%s' (midiinmodule)", device_name);
      s_log(0, buffer);
      return 0;
    }

  return 1;
}

static void closeDevice(int *fd)
{
  if (*fd != -1)
    {
      close(*fd);
      *fd = -1;
    }
}

static void readData(int fd, MidiType* buffer)
{
#define MAX_MSG_LEN 1024
  unsigned char buf[MAX_MSG_LEN];
  fd_set readfds;
  int len;

  if (fd < 0)
    return;

  {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_SET(fd,&readfds);
    select(fd+1,&readfds,0,0,&tv);
    //TODO: interrupted!
  }
  
  if (FD_ISSET(fd, &readfds))
    {
      errno = 0;
      //      do
	{
	  len = read(fd, buf, MAX_MSG_LEN);
	  if (len == -1 && errno != EINTR)
	    {
              char buffer[64];
	      snprintf(buffer, sizeof(buffer),
                       "Fehler bei midiinmodule::read -> errno = %i",
                       errno);
              s_log(0, buffer);
	    }
	  else
	    {
	      //TODO: convert the midi stream?
              midi_set_buffer(buffer, buf, len);
	    }
        }// while (errno != EINTR);
    }
  else
    {
      buffer->len = 0;
      return;
    }
}

#elif defined(OS_WIN32)

#include <windows.h>

#include "midiutil.h"

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

typedef struct _MyInstance {
	int dummy;
} MyInstance, *MyInstancePtr;


void CALLBACK midiCallBack(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
						   DWORD dwParam1, DWORD dwParam2);
	
	int init(logT log_function)
	{
		MMRESULT res;
        int numDevs;

		s_log = log_function;

		s_midi_buf_len = 0;

		numDevs = midiInGetNumDevs();

		if (numDevs == 0)
		{		  
		  s_log(0, "No Midi Devices found - aborting");
		  return 0;		  
		}		

		InitializeCriticalSection(&s_critical_section);		

		// to protect ourselves from midi-messages while init is not done yet
		s_init_finnished = 0;

		res = midiInOpen(&s_midi_in, 0, (DWORD) midiCallBack, (DWORD) 
			0, CALLBACK_FUNCTION);
		
		if (MMSYSERR_NOERROR != res)
		{
			char buffer[256];
			TCHAR errorText[256];
			midiInGetErrorText(res,errorText,255);
			snprintf(buffer, sizeof(buffer),
					 "Failed to open MIDI input device: %s", errorText);		
			s_log(0, buffer);
			return 0;
		}  		

		s_midi_hdr.lpData = s_midi_longbuf;
		s_midi_hdr.dwBufferLength = MIDI_LONG_BUF_SIZE;
		s_midi_hdr.dwFlags = 0;

		res = midiInPrepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
		if (MMSYSERR_NOERROR != res)
		{		
			char buffer[256];
			TCHAR errorText[256];
			midiInGetErrorText(res,errorText,255);
			snprintf(buffer, sizeof(buffer),
				     "Failed to prepare MIDI header: %s", errorText);		
			s_log(0, buffer);
			midiInReset(s_midi_in);
			midiInClose(s_midi_in);
			return 0;
		}  
  

		res = midiInAddBuffer(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
		if (MMSYSERR_NOERROR != res)
		{		
			char buffer[256];
			TCHAR errorText[256];
			midiInGetErrorText(res,errorText,255);
			snprintf(buffer, sizeof(buffer),
				     "Failed to add MIDI buffer: %s", errorText);		
			s_log(0, buffer);

			midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
			midiInReset(s_midi_in);
			midiInClose(s_midi_in);
			return 0;
		}  

		res = midiInStart(s_midi_in);
		if (MMSYSERR_NOERROR != res)
		{		
			char buffer[128];
			TCHAR errorText[256];
			midiInGetErrorText(res,errorText,255);
			snprintf(buffer, sizeof(buffer),
				     "Failed to start MIDI input device: %s", errorText);		

			s_log(0, buffer);
			
			midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));
			midiInReset(s_midi_in);
			midiInClose(s_midi_in);
			return 0;
		}  

		{
		  char buffer[128];
		  snprintf(buffer, sizeof(buffer),"Number of MIDI Devices: %d",
			       numDevs);
		  s_log(2, buffer);
		  snprintf(buffer, sizeof(buffer),"Initialization ... Success!!");
		  s_log(2, buffer);
		}

		s_init_finnished = 1;
				
		return 1;
	}
	
	void shutDown(void)
	{		
		midiInStop(s_midi_in);

		midiInUnprepareHeader(s_midi_in, &s_midi_hdr, sizeof(s_midi_hdr));

		midiInReset(s_midi_in);
		midiInClose(s_midi_in);

		DeleteCriticalSection(&s_critical_section);
	}
	
	MyInstance* construct()
	{
		MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));	
		
		
		return my;
	}
	
	void destruct(MyInstance* my)
	{  
		free(my);
	}


	static void consume_buffer(MidiType* t);
	
	void update(void* instance)
	{
		InstancePtr inst = (InstancePtr) instance;
		MyInstancePtr my = inst->my;

		consume_buffer(inst->out_r);
	}

// copies the content of the static midi buffer to t and empties the midi buffer
// t is overwritten
static void consume_buffer(MidiType* t)
{
	EnterCriticalSection(&s_critical_section);
	midi_set_buffer(t, s_midi_buf, s_midi_buf_len);
	s_midi_buf_len = 0;
	LeaveCriticalSection(&s_critical_section);
}

//puts a byte into the static buffer
static void put_byte(unsigned char byte)
{
	EnterCriticalSection(&s_critical_section);

	if (s_midi_buf_len < MIDI_BUF_SIZE)
		s_midi_buf[s_midi_buf_len++] = byte;
	else
	{
		/*char buffer[64];
		snprintf(buffer, sizeof(buffer),
			     "Buffer overflow at midiinmodule::put_byte, ignoring %i", byte);
		s_log(0, buffer)*/;
	}
	LeaveCriticalSection(&s_critical_section);
}

//puts a block of bytes into the static buffer
static void put_block(unsigned char* block, int len)
{
	EnterCriticalSection(&s_critical_section);

	if (s_midi_buf_len+len <= MIDI_BUF_SIZE)
	{
		memcpy(s_midi_buf + s_midi_buf_len, block, len);
		s_midi_buf_len += len;		
	}
	else
	{
		/*char buffer[64];
		snprintf(buffer, sizeof(buffer),
			     "Buffer overflow at midiinmodule::put_block, ignoring %i bytes",
				 len);
		s_log(0, buffer);*/
	}
	LeaveCriticalSection(&s_critical_section);
}

void CALLBACK midiCallBack(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
						   DWORD dwParam1, DWORD dwParam2)
{	
	unsigned char midiStat; /* MIDI_CMD_XXX */	
	unsigned char midiParam1; /* je nach commando andere bedeutung */
	unsigned char midiParam2; /* je nach commando andere bedeutung */

	MidiType* buffer = (MidiType*) dwInstance;

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
			s_log(0, buffer);
		} break;
		
	case MIM_DATA:
		{
		int len = midi_length_of_message(midiStat);
		if (len < 0)
		{
            char buffer[64];
			snprintf(buffer, sizeof(buffer),
				     "midi: unbekannt: %i %i %i", midiStat, midiParam1, midiParam2);
			s_log(0, buffer);
			return;
		}
		switch (len)
		{
		case 0:
			put_byte(midiStat);
			break;
		case 1:
			put_byte(midiStat);
			put_byte(midiParam1);
			break;
		case 2:
			put_byte(midiStat);
			put_byte(midiParam1);
			put_byte(midiParam2);
			break;
		default:
			{
			  char buffer[64];
			  snprintf(buffer, sizeof(buffer),
				       "unknown length at midiinmodule::midiCallBack: %i", len);
			  s_log(0, buffer);
			}
		}		
	} break;
	case MIM_LONGDATA:
		{
			MIDIHDR* hdr = (MIDIHDR*) dwParam1;
			//TODO do we need to insert a status byte?
			put_block(hdr->lpData, hdr->dwBytesRecorded);

			//TODO do we need to reinsert the buffer?
		}break;
		
	default:
		{
			char buffer[64];
			snprintf(buffer, sizeof(buffer),
					 "Unknown wMsg at midiinmodule::midiCallBack: %i", wMsg);
			s_log(0, buffer);
		}
	}
}

#endif
