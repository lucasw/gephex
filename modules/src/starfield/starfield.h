#ifndef INCLUDED_STARFIELD_H
#define INCLUDED_STARFIELD_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "framebuffertype.h"
#include "rgbtype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 RGBType* in_colorStars;
 RGBType* in_colorBG;
 NumberType* in_speed;
 NumberType* in_currentNumStars;
 FrameBufferType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_colorStars = 0, in_colorBG = 1, in_speed = 2, in_currentNumStars = 3 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
