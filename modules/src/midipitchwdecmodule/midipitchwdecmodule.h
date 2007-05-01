#ifndef INCLUDED_MIDIPITCHWDECMODULE_H
#define INCLUDED_MIDIPITCHWDECMODULE_H

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
 MidiType* in_midi;
 NumberType* out_wheel;
} Instance, *InstancePtr;
enum Inputs { in_channel = 0, in_midi = 1 };
enum Outputs { out_wheel = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
