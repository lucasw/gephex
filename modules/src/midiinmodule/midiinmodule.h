#ifndef INCLUDED_MIDIINMODULE_H
#define INCLUDED_MIDIINMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "miditype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_device;
 MidiType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_device = 0 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
