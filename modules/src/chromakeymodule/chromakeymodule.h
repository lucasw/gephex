#ifndef INCLUDED_CHROMAKEYMODULE_H
#define INCLUDED_CHROMAKEYMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "rgbtype.h"
#include "stringtype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 RGBType* in_color;
 NumberType* in_tolerance;
 StringType* in_mode;
 FrameBufferType* in_fg;
 FrameBufferType* in_bg;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_color = 0, in_tolerance = 1, in_mode = 2, in_fg = 3, in_bg = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
void patchLayout(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
