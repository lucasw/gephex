#ifndef INCLUDED_JOYSTICKMODULE_H
#define INCLUDED_JOYSTICKMODULE_H

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
 NumberType* in_joy_id;
 NumberType* out_signal_x;
 NumberType* out_signal_y;
 NumberType* out_button_1;
 NumberType* out_button_2;
 MidiType* out_midi;
} Instance, *InstancePtr;
enum Inputs { in_joy_id = 0 };
enum Outputs { out_signal_x = 0, out_signal_y = 1, out_button_1 = 2, out_button_2 = 3, out_midi = 4 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
