#ifndef INCLUDED_AUDIOBDMODULE_H
#define INCLUDED_AUDIOBDMODULE_H

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
 AudioType* in_audio;
 NumberType* in_thr;
 StringType* in_algo;
 NumberType* out_b;
} Instance, *InstancePtr;
enum Inputs { in_audio = 0, in_thr = 1, in_algo = 2 };
enum Outputs { out_b = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
