#ifndef INCLUDED_RANGECONVERTMODULE_H
#define INCLUDED_RANGECONVERTMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_n;
 NumberType* in_min_in;
 NumberType* in_max_in;
 NumberType* in_min_out;
 NumberType* in_max_out;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_n = 0, in_min_in = 1, in_max_in = 2, in_min_out = 3, in_max_out = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
