#ifndef INCLUDED_NETCONTROLMODULE_H
#define INCLUDED_NETCONTROLMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "miditype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_port;
 MidiType* out_signal;
} Instance, *InstancePtr;
enum Inputs { in_port = 0 };
enum Outputs { out_signal = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
