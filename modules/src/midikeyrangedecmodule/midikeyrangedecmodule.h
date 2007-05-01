#ifndef INCLUDED_MIDIKEYRANGEDECMODULE_H
#define INCLUDED_MIDIKEYRANGEDECMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "miditype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 MidiType* in_midi;
 NumberType* in_channel;
 NumberType* in_note_nr_min;
 NumberType* in_note_nr_max;
 NumberType* in_default;
 NumberType* out_pos;
 NumberType* out_event;
 NumberType* out_pressed;
} Instance, *InstancePtr;
enum Inputs { in_midi = 0, in_channel = 1, in_note_nr_min = 2, in_note_nr_max = 3, in_default = 4 };
enum Outputs { out_pos = 0, out_event = 1, out_pressed = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
