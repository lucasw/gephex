#ifndef INCLUDED_SIGNALGENMODULE_H
#define INCLUDED_SIGNALGENMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "stringtype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_Amplitude;
 NumberType* in_Frequenz;
 NumberType* in_Phase;
 NumberType* in_Position;
 StringType* in_Signal;
 NumberType* out_Signal;
} Instance, *InstancePtr;
enum Inputs { in_Amplitude = 0, in_Frequenz = 1, in_Phase = 2, in_Position = 3, in_Signal = 4 };
enum Outputs { out_Signal = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
