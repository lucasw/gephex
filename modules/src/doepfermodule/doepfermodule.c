#include "doepfermodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

typedef struct _MyInstance {

 unsigned char controls[16][128];
 struct MidiParser* parser;

} MyInstance, *MyInstancePtr;

void controlchange_callback(unsigned char channel,
			    unsigned char control,
			    unsigned char value,
			    void* self)
{
  MyInstance* my = (MyInstance*) self;
  my->controls[channel][control] = value;

//  printf("received midi controlchange, channel = %i, control = %i, "
  //    "value = %i, my = %i\n", channel, control, value, my);
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

  memset(my->controls, 0, sizeof(my->controls));

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

  unsigned char channel = trim_int(inst->in_channel->number,0,15);
  unsigned char group_offset = trim_int(inst->in_button_group->number,0,3) * 4;

  midi_parse_data(my->parser, inst->in_midi->data, inst->in_midi->len);

  inst->out_signal_1->number =  my->controls[channel][group_offset] / 127.;

  inst->out_signal_2->number =  my->controls[channel][group_offset+1] / 127.;

  inst->out_signal_3->number = my->controls[channel][group_offset+2] / 127.;

  inst->out_signal_4->number = my->controls[channel][group_offset+3] / 127.;
}

