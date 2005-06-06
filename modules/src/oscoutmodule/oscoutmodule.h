#ifndef INCLUDED_OSCOUTMODULE_H
#define INCLUDED_OSCOUTMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "osctype.h"
#include "stringtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 OscType* in_r;
 StringType* in_dest;
 NumberType* in_port;
} Instance, *InstancePtr;
enum Inputs { in_r = 0, in_dest = 1, in_port = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
