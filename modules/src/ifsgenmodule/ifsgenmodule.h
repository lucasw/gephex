#ifndef INCLUDED_IFSGENMODULE_H
#define INCLUDED_IFSGENMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "ifstype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_num_fun;
 IfsType* out_ifs;
} Instance, *InstancePtr;
enum Inputs { in_num_fun = 0 };
enum Outputs { out_ifs = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
