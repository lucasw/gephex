#ifndef INCLUDED_FLASHMODULE_H
#define INCLUDED_FLASHMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_trigger;
 FrameBufferType* in_src;
 NumberType* in_attack;
 NumberType* in_sustain;
 NumberType* in_decay;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_trigger = 0, in_src = 1, in_attack = 2, in_sustain = 3, in_decay = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void patchLayout(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
