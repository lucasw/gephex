#ifndef INCLUDED_V4LMODULE_H
#define INCLUDED_V4LMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_devicefile;
 NumberType* in_x_size;
 NumberType* in_y_size;
 NumberType* in_brightness;
 NumberType* in_hue;
 NumberType* in_colour;
 NumberType* in_contrast;
 NumberType* in_whiteness;
 NumberType* in_drops;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_devicefile = 0, in_x_size = 1, in_y_size = 2, in_brightness = 3, in_hue = 4, in_colour = 5, in_contrast = 6, in_whiteness = 7, in_drops = 8 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
