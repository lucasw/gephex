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

#include "midiccdecmodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

typedef struct _MyInstance
{
  bool initialized;
  bool event;
  unsigned char value;
  unsigned char channel;
  unsigned char cc_nr;

  struct MidiParser* parser;
  
} MyInstance, *MyInstancePtr;

void controlchange_callback(unsigned char channel,
			    unsigned char control,
			    unsigned char value,
			    void* self)
{
  MyInstance* my = static_cast<MyInstance*>(self);

  if (my->channel == channel && my->cc_nr == control)
    {
      my->value = value;
      my->event = true;
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

  my->initialized=false;

  my->parser = midi_create_parser(0,0,0,controlchange_callback,0,0,0,0,my);
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

  if( !my->initialized )
    {
      my->value = trim_double(inst->in_defval->number,0.0,1.0);
      my->initialized = true;
    }

  my->channel = trim_int(inst->in_channel->number,0,15);
  my->cc_nr = trim_int(inst->in_cc_nr->number,0,127);
  

  my->event=false;
  midi_parse_data(my->parser, inst->in_midi->data, inst->in_midi->len);
  
  if (my->event == false)
    inst->out_event->number = 0.0;
  else
    inst->out_event->number = 1.0;
  
  inst->out_value->number =  my->value / 127.;
}

