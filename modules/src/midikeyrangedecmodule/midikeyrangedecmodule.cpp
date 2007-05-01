/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#include "midikeyrangedecmodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

typedef struct _MyInstance
{
  bool initialized;
  bool pressed;
  bool event;
  unsigned char velo;
  unsigned char offset;
  unsigned char rvelo;
  unsigned char channel;
  unsigned char note_nr_min;
  unsigned char note_nr_max;

  struct MidiParser* parser;
  
} MyInstance, *MyInstancePtr;


void noteoff_callback (uint8_t channel, uint8_t key,
		       uint8_t velocity,
		       void* user_data)
{
  MyInstance* my = static_cast<MyInstance*>(user_data);
  
  if (my->channel == channel &&
      my->note_nr_min <= key &&
      my->note_nr_max >= key)
    {
      my->pressed = false;
      my->event = true;      
      my->rvelo   = velocity;
      //      my->offset = key - my->note_nr_min;
    }
}


void noteon_callback (uint8_t channel, uint8_t key,
		       uint8_t velocity,
		       void* user_data)
{
  MyInstance* my = static_cast<MyInstance*>(user_data);

  if (my->channel == channel &&
      my->note_nr_min <= key &&
      my->note_nr_max >= key)
    {
      my->pressed = true;
      my->event = true;      
      my->velo   = velocity;
      my->offset = key - my->note_nr_min;
    }
}

int init(logT log_function)
{
  //fprintf(stderr,"<doepfermodule> Init called\n");
  //fflush(stderr);
  
  return 1;
}

void shutDown(void)
{  
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->pressed = false;
  my->event = false;      
  my->velo   = 0;
  my->rvelo   = 0;
  my->offset = 0;
  
  my->parser = midi_create_parser(noteoff_callback,noteon_callback,0,0,0,0,0,0,my);
  return my;
}

void destruct(MyInstance* my)
{
  midi_destroy_parser(my->parser);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  my->channel = trim_int(inst->in_channel->number,0,15);
  my->note_nr_min = trim_int(inst->in_note_nr_min->number,0,127);
  my->note_nr_max = trim_int(inst->in_note_nr_max->number,0,127);

  my->event=false;
  midi_parse_data(my->parser, inst->in_midi->data, inst->in_midi->len);
  
  if (my->event == false)
    inst->out_event->number = 0.0;
  else
    inst->out_event->number = 1.0;

    if (my->pressed == false)
    inst->out_pressed->number = 0.0;
  else
    inst->out_pressed->number = 1.0;


    inst->out_pos->number = my->offset;
}

