#ifndef INCLUDED_IFSXFADERMODULE_H
#define INCLUDED_IFSXFADERMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "ifstype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_x;
 IfsType* in_1;
 IfsType* in_2;
 IfsType* out_r;
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
