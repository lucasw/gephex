#ifndef INCLUDED_CAPTUREMODULE_H
#define INCLUDED_CAPTUREMODULE_H

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
 NumberType* in_device;
 NumberType* in_x_size;
 NumberType* in_y_size;
 FrameBufferType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_device = 0, in_x_size = 1, in_y_size = 2 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
