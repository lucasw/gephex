#ifndef INCLUDED_AUDIOWAVEGENMODULE_H
#define INCLUDED_AUDIOWAVEGENMODULE_H

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
 NumberType* in_freq;
 NumberType* in_sample_rate;
 NumberType* in_amplitude;
 AudioType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_freq = 0, in_sample_rate = 1, in_amplitude = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
