#ifndef INCLUDED_AUDIOADDMODULE_H
#define INCLUDED_AUDIOADDMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "audiotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 AudioType* in_lhs;
 NumberType* in_w_lhs;
 AudioType* in_rhs;
 NumberType* in_w_rhs;
 NumberType* in_thr;
 NumberType* in_flush;
 AudioType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_lhs = 0, in_w_lhs = 1, in_rhs = 2, in_w_rhs = 3, in_thr = 4, in_flush = 5 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
