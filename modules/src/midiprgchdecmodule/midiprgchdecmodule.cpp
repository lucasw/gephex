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

#include "midiprgchdecmodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

typedef struct _MyInstance
{
  unsigned char prg;
  unsigned char channel;

  struct MidiParser* parser;
  
} MyInstance, *MyInstancePtr;


void prg_ch_callback (uint8_t channel, uint8_t prg, void* user_data)
{
  MyInstance* my = static_cast<MyInstance*>(user_data);
  
  if (my->channel == channel)
    {
      my->prg = prg;
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

  my->prg = 0;
  my->parser = midi_create_parser(0,0,0,0,prg_ch_callback,0,0,0,my);
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
  
  inst->out_prg->number = my->prg;
}

