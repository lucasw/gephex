#include "doepfermodule.h"

#include <stdio.h>

#include <assert.h>
#include "libmidi.h"

static unsigned char s_controls[16][128];
static struct MidiParser* s_parser;

static void controlchange_callback(unsigned char channel,
				   unsigned char control,
				   unsigned char value,
				   void* self)
{
  s_controls[channel][control] = value;
}

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  fprintf(stderr,"<doepfermodule> Init called\n");
  fflush(stderr);
  s_parser = midi_create_parser(0,0,0,controlchange_callback,0,0,0,0,0);
  return 1;
}

void shutDown(void)
{
  midi_destroy_parser(s_parser);
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

  unsigned char channel = inst->in_channel->number % 16;
  unsigned char group_offset = (inst->in_button_group->number % 4) * 4;

  midi_parse_data(s_parser, inst->in_midi->data, inst->in_midi->len);

  inst->out_signal_1->number 
    = (uint_32) (UINT32_MAX * ((double) s_controls[channel][group_offset]
			       / 127.));

  inst->out_signal_2->number 
    = (uint_32) (UINT32_MAX * ((double) s_controls[channel][group_offset+1]
			       / 127.));

  inst->out_signal_3->number 
    = (uint_32) (UINT32_MAX * ((double) s_controls[channel][group_offset+2]
			       / 127.));

  inst->out_signal_4->number 
    = (uint_32) (UINT32_MAX * ((double) s_controls[channel][group_offset+3]
			       / 127.));
}

