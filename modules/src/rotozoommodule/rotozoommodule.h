#ifndef INCLUDED_ROTOZOOMMODULE_H
#define INCLUDED_ROTOZOOMMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "positiontype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_zoom;
 NumberType* in_rot;
 PositionType* in_disp;
 FrameBufferType* in_texture;
 FrameBufferType* in_background;
 NumberType* in_copy_background;
 StringType* in_routine;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_zoom = 0, in_rot = 1, in_disp = 2, in_texture = 3, in_background = 4, in_copy_background = 5, in_routine = 6 };
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
