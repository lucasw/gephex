#ifndef INCLUDED_PONGMODULE_H
#define INCLUDED_PONGMODULE_H

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
 NumberType* in_p1;
 NumberType* in_p2;
 NumberType* in_ball_x;
 NumberType* in_ball_y;
 NumberType* in_speed_x;
 NumberType* in_speed_y;
 NumberType* in_start;
 FrameBufferType* out_screen;
 NumberType* out_speed_x;
 NumberType* out_speed_y;
 NumberType* out_ball_x;
 NumberType* out_ball_y;
 NumberType* out_status;
} Instance, *InstancePtr;
enum Inputs { in_p1 = 0, in_p2 = 1, in_ball_x = 2, in_ball_y = 3, in_speed_x = 4, in_speed_y = 5, in_start = 6 };
enum Outputs { out_screen = 0, out_speed_x = 1, out_speed_y = 2, out_ball_x = 3, out_ball_y = 4, out_status = 5 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
