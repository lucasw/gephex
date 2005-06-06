#ifndef INCLUDED_MIDICCDECMODULE_H
#define INCLUDED_MIDICCDECMODULE_H

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
 NumberType* in_cc_nr;
 NumberType* in_defval;
 MidiType* in_midi;
 NumberType* out_value;
 NumberType* out_event;
} Instance, *InstancePtr;
enum Inputs { in_channel = 0, in_cc_nr = 1, in_defval = 2, in_midi = 3 };
enum Outputs { out_value = 0, out_event = 1 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
