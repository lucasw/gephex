#ifndef INCLUDED_SDLFONTMODULE_H
#define INCLUDED_SDLFONTMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "rgbtype.h"
#include "framebuffertype.h"
#include "stringtype.h"
#include "positiontype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_scroll;
 NumberType* in_effect_time;
 NumberType* in_options;
 NumberType* in_point_size;
 PositionType* in_pos;
 StringType* in_font;
 RGBType* in_color;
 FrameBufferType* in_b;
 StringType* in_text_;
 NumberType* in_patch;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_scroll = 0, in_effect_time = 1, in_options = 2, in_point_size = 3, in_pos = 4, in_font = 5, in_color = 6, in_b = 7, in_text_ = 8, in_patch = 9 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void patchLayout(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
