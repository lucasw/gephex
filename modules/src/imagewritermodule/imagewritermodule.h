#ifndef INCLUDED_IMAGEWRITERMODULE_H
#define INCLUDED_IMAGEWRITERMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "framebuffertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_prefix;
 FrameBufferType* in_in;
} Instance, *InstancePtr;
enum Inputs { in_prefix = 0, in_in = 1 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
