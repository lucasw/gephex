#ifndef __INCLUDED_IFS_TYPE_H__
#define __INCLUDED_IFS_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

#define IFS_MAX_FUN 32

typedef struct IfsType_
{
  double ifs[IFS_MAX_FUN][6];
  int numfun;
} IfsType;


static __inline void ifs_initInstance(IfsType* newType)
{
	newType->numfun = 0;
}


static __inline IfsType* ifs_newInstance(void)
{
	IfsType* newType = (IfsType*) malloc(sizeof(IfsType));
	ifs_initInstance(newType);
	return newType;
}


static __inline void ifs_assign(IfsType* dst,const IfsType* src)
{
  memcpy(dst->ifs,src->ifs,sizeof(IfsType));
}


static __inline void ifs_deleteInstance(IfsType* num)
{
	free(num);
}

#endif
