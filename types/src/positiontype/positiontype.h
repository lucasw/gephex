#ifndef __INCLUDED_POSITION_TYPE_H__
#define __INCLUDED_POSITION_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

typedef struct PositionType_
{
	double x;
	double y;
} PositionType;

static __inline void pos_initInstance(PositionType* newType)
{
	newType->x = 0;
	newType->y = 0;
}

static __inline PositionType* pos_newInstance(void)
{
	PositionType* newType = (PositionType*) malloc(sizeof(PositionType));
	pos_initInstance(newType);
	return newType;
}
static __inline void pos_assign(PositionType* dst,const PositionType* src)
{
	dst->x = src->x;
	dst->y = src->y;
}

static __inline void pos_deleteInstance(PositionType* pos)
{
	free(pos);
}

static __inline int pos_serialize(const PositionType* pos, char* buffer, int bufferLen)
{
	if (buffer == 0 || bufferLen < 26)
		return 26;
	else
	{
		sprintf(buffer,"%g %g",pos->x, pos->y);
		return strlen(buffer)+1;	
	}
}

static __inline void pos_deSerialize(const char* buffer,int len, PositionType* pos)
{
	if (buffer[0] == 0)
	{
		pos_initInstance(pos);
	}
	else
	{
	  char* endptr;

	  pos->x = strtod(buffer, &endptr);
	  pos->y = strtod(endptr, 0);
	}
}

#endif
