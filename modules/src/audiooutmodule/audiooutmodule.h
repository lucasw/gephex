#ifndef INCLUDED_AUDIOOUTMODULE_H
#define INCLUDED_AUDIOOUTMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "audiotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_device;
 AudioType* in_audio;
 NumberType* in_latency;
 StringType* in_driver;
} Instance, *InstancePtr;
enum Inputs { in_device = 0, in_audio = 1, in_latency = 2, in_driver = 3 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
