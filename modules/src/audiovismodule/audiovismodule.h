#ifndef INCLUDED_AUDIOVISMODULE_H
#define INCLUDED_AUDIOVISMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "framebuffertype.h"
#include "audiotype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 AudioType* in_audio;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_audio = 0 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
