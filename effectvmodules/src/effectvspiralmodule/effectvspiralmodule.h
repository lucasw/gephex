#ifndef INCLUDED_EFFECTVSPIRALMODULE_H
#define INCLUDED_EFFECTVSPIRALMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "framebuffertype.h"
#include "positiontype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 FrameBufferType* in_b;
 NumberType* in_animate_focus;
 NumberType* in_toggle_xor;
 NumberType* in_focus_interval;
 NumberType* in_focus_increment;
 NumberType* in_depth_shift;
 StringType* in_wave_names;
 PositionType* in_focus;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_animate_focus = 1, in_toggle_xor = 2, in_focus_interval = 3, in_focus_increment = 4, in_depth_shift = 5, in_wave_names = 6, in_focus = 7 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
