#ifndef INCLUDED_FUNPARSEMODULE_H
#define INCLUDED_FUNPARSEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_exp;
 NumberType* in_x1;
 NumberType* in_x2;
 NumberType* in_x3;
 NumberType* in_x4;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_exp = 0, in_x1 = 1, in_x2 = 2, in_x3 = 3, in_x4 = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
