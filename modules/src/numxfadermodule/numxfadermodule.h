#ifndef INCLUDED_NUMXFADERMODULE_H
#define INCLUDED_NUMXFADERMODULE_H

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
 NumberType* in_x;
 NumberType* in_1;
 NumberType* in_2;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_x = 0, in_1 = 1, in_2 = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
