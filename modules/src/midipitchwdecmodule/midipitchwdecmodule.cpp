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

#include "midipitchwdecmodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

typedef struct _MyInstance
{
  unsigned char channel;
  double wheel;

  struct MidiParser* parser;
  
} MyInstance, *MyInstancePtr;


void pitchw_callback (uint8_t channel, int wheel,void* user_data)
{
  MyInstance* my = static_cast<MyInstance*>(user_data);
  
  if (my->channel == channel)
    {
      my->wheel = static_cast<double>(wheel) / 16384.;
    }
}

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{  
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->wheel = 0.5;
  my->parser = midi_create_parser(0,0,0,0,0,0,pitchw_callback,0,my);
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
  midi_parse_data(my->parser, inst->in_midi->data, inst->in_midi->len);
  
  inst->out_wheel->number =  my->wheel;
}

