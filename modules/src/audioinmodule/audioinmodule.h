#ifndef INCLUDED_AUDIOINMODULE_H
#define INCLUDED_AUDIOINMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "audiotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_device;
 StringType* in_driver;
 AudioType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_device = 0, in_driver = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
