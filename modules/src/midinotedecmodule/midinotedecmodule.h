#ifndef INCLUDED_MIDINOTEDECMODULE_H
#define INCLUDED_MIDINOTEDECMODULE_H

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
 NumberType* in_channel;
 NumberType* in_note_nr;
 MidiType* in_midi;
 NumberType* out_pressed;
 NumberType* out_toggle;
 NumberType* out_velo;
} Instance, *InstancePtr;
enum Inputs { in_channel = 0, in_note_nr = 1, in_midi = 2 };
enum Outputs { out_pressed = 0, out_toggle = 1, out_velo = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
