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

#include "midicontrolmodule.h"

#include <limits.h>
#include <windows.h>

#define MIDI_CMD_NOTEOFF 128
#define MIDI_CMD_NOTEON	144
#define MIDI_CMD_CONTROLCHANGE 176
#define MIDI_CMD_PRGCH 192
#define MIDI_CMD_CHANPRESS 208
#define MIDI_CMD_PITCHBEND 224

static HMIDIIN midiIn;
static unsigned char pitchbend[16];
static unsigned char prgchange[16];
static unsigned char aftertouch[16];
static unsigned char ctrl[16][128];
static unsigned char note[16][128];

typedef struct _MyInstance {
	int dummy;
} MyInstance, *MyInstancePtr;


void CALLBACK doepferCallBack(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
						 DWORD dwParam1, DWORD dwParam2)
{	
	unsigned char midiCmd; /* MIDI_CMD_XXX */
	unsigned char midiChan; /* 0 bis 15 */
	unsigned char midiParam1; /* je nach commando andere bedeutung */
	unsigned char midiParam2; /* je nach commando andere bedeutung */

	midiCmd = (dwParam1 & 0x000000f0) >> 0;
	midiChan = (dwParam1 & 0x0000000f) >> 0;
	midiParam1 = (dwParam1 & 0x0000ff00) >> 8;
	midiParam2 = (dwParam1 & 0x00ff0000) >> 16;

	switch (midiCmd)
	{
		case MIDI_CMD_CONTROLCHANGE:
		{	
			ctrl[midiChan][midiParam1]=midiParam2;
			printf("midi[%i]:ControlChange Controll[%i]=%i\n", midiChan,midiParam1,midiParam2);
			break;
		}
		case MIDI_CMD_NOTEON:
		{
			note[midiChan][midiParam1]=midiParam2;

			printf("midi[%i]:NoteOn key %i velocity %i\n", midiChan,midiParam1,midiParam2);
			break;
		}
		case MIDI_CMD_NOTEOFF:
		{
			note[midiChan][midiParam1]=0;
			printf("midi[%i]:NoteOff key %i velocity %i\n", midiChan,midiParam1,midiParam2);
			break;
		}
		case MIDI_CMD_PRGCH:
		{
			prgchange[midiChan]=midiParam1;

			printf("midi[%i]:ProgramChange to %i\n", midiChan,midiParam1);
			break;
		}
		case MIDI_CMD_CHANPRESS:
		{
			aftertouch[midiChan]=midiParam1;

			printf("midi[%i]:ChanPress is %i\n", midiChan,midiParam1);
			break;
		}
		case MIDI_CMD_PITCHBEND:
		{
			pitchbend[midiChan]=midiParam2;
			printf("midi[%i]:PitchBend %i\n", midiChan,(int)midiParam2-64);
			break;
		}

		default:
		{
			printf("midi: unbekannt: %i %i %i \n", midiCmd,midiParam1,midiParam2);
		}
	}
}

int init(logT log_function)
{
	MMRESULT res;

	res = midiInOpen(&midiIn, 0, (DWORD) doepferCallBack, (DWORD) 
				     0, CALLBACK_FUNCTION);

	if(MMSYSERR_NOERROR != res)
	{
	  TCHAR errorText[256];
	  midiInGetErrorText(res,errorText,255);
      printf("Failed to open MIDI input device: %s\n", errorText);		
	  return 0;
	}  
	
	
	res = midiInStart(midiIn);
    if (MMSYSERR_NOERROR != res)
	{		
	  TCHAR errorText[256];
	  midiInGetErrorText(res,errorText,255);
      printf("Failed to start MIDI input device: %s\n", errorText);		

	  midiInReset(midiIn);
	  midiInClose(midiIn);
	  return 0;
	}  
	

	printf("NumDevs: %d\n", midiInGetNumDevs());  	
	printf("Success!!\n");

	
	return 1;
}

void shutDown(void)
{
  midiInStop(midiIn);
  midiInReset(midiIn);
  midiInClose(midiIn);
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

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;

	unsigned char chan;
	
	unsigned char type;
	unsigned char param[4];	


	unsigned char value[4];
	unsigned char outnr;

	chan = inst->in_chan->number-1;
	if (chan<0||chan>15)
		chan=0;


	type=inst->in_midi_mode->number ;

	param[0]=inst->in_midi1_param->number ;
	param[1]=inst->in_midi2_param->number ;
	param[2]=inst->in_midi3_param->number ;
	param[3]=inst->in_midi4_param->number ;

	for(outnr=0;outnr!=4;++outnr)
	{
		switch (type)
		{

			case 1: // aftertouch
			{
				value[outnr]=aftertouch[chan];	
				break;
			}
			case 2: // prg
			{
				value[outnr]=prgchange[chan];	
				break;
			}
			case 3: // note
			{
				value[outnr]=note[chan][param[outnr]];	
				break;
			}
			case 4: // ctrl
			{
				value[outnr]=ctrl[chan][param[outnr]];	
				break;
			}
			case 5: // pitch
			{
				value[outnr]=pitchbend[chan];	
				break;
			}

			default: /* doepfer mode */
			{
				
				int group = (param[outnr]-1) % 4; //absolute!! :)		
				int ctrlnr= group*4+outnr;
				if (ctrlnr<0||ctrlnr>127)
					value[outnr]=0;
				else
					value[outnr]=ctrl[chan][ctrlnr];
				
					
			}
		}
	}
	
	inst->out_signal_1->number = (uint_32) (UINT32_MAX * ((double) value[0] / 127.));
	inst->out_signal_2->number = (uint_32) (UINT32_MAX * ((double) value[1] / 127.));
	inst->out_signal_3->number = (uint_32) (UINT32_MAX * ((double) value[2] / 127.));
	inst->out_signal_4->number = (uint_32) (UINT32_MAX * ((double) value[3] / 127.));
}

