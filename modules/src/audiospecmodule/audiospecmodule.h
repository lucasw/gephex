#ifndef INCLUDED_AUDIOSPECMODULE_H
#define INCLUDED_AUDIOSPECMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "audiotype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 AudioType* in_audio;
 AudioType* out_f;
} Instance, *InstancePtr;
enum Inputs { in_audio = 0 };
enum Outputs { out_f = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
