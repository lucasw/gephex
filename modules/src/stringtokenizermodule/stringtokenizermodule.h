#ifndef INCLUDED_STRINGTOKENIZERMODULE_H
#define INCLUDED_STRINGTOKENIZERMODULE_H

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
 StringType* in_string;
 NumberType* in_entry;
 StringType* out_token;
} Instance, *InstancePtr;
enum Inputs { in_string = 0, in_entry = 1 };
enum Outputs { out_token = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
