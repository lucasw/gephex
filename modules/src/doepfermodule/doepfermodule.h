#ifndef INCLUDED_DOEPFERMODULE_H
#define INCLUDED_DOEPFERMODULE_H

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
 NumberType* in_button_group;
 MidiType* in_midi;
 NumberType* out_signal_1;
 NumberType* out_signal_2;
 NumberType* out_signal_3;
 NumberType* out_signal_4;
} Instance, *InstancePtr;
enum Inputs { in_channel = 0, in_button_group = 1, in_midi = 2 };
enum Outputs { out_signal_1 = 0, out_signal_2 = 1, out_signal_3 = 2, out_signal_4 = 3 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
