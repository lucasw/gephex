#ifndef INCLUDED_AUDIOENERGYMODULE_H
#define INCLUDED_AUDIOENERGYMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "audiotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 AudioType* in_audio;
 NumberType* in_amp;
 NumberType* out_e1;
 NumberType* out_e2;
 NumberType* out_e3;
 NumberType* out_e4;
} Instance, *InstancePtr;
enum Inputs { in_audio = 0, in_amp = 1 };
enum Outputs { out_e1 = 0, out_e2 = 1, out_e3 = 2, out_e4 = 3 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
