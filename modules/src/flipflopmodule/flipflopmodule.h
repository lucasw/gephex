#ifndef INCLUDED_FLIPFLOPMODULE_H
#define INCLUDED_FLIPFLOPMODULE_H

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
 NumberType* in_d;
 NumberType* in_clk;
 NumberType* in_tol;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_d = 0, in_clk = 1, in_tol = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
