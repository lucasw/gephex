#include <stdlib.h>
#include <stdio.h>

//#include "numbertype.h"

typedef struct RGBType_
{
	float r;
	float g;
	float b;
} RGBType;

static __inline void rgb_initInstance(RGBType* newType)
{
	newType->r = 0.f;
	newType->g = 0.f;
	newType->b = 0.f;
}

static __inline RGBType* rgb_newInstance(void)
{
	RGBType* newType = (RGBType*) malloc(sizeof(RGBType));
	rgb_initInstance(newType);
	return newType;
}
static __inline void rgb_assign(RGBType* dst,const RGBType* src)
{
	dst->r = src->r;
	dst->g = src->g;
	dst->b = src->b;
}

static __inline void rgb_deleteInstance(RGBType* rgb)
{
	free(rgb);
}

static __inline int rgb_serialize(const RGBType* rgb, char* buffer,
				  int bufferLen)
{
	int reqLen = 5*3 + 2 + 1;

	if (bufferLen >= reqLen && buffer != 0)
	{
	  sprintf(buffer,"%.3f %.3f %.3f", rgb->r, rgb->g, rgb->b);
	}

	return reqLen;
}

static __inline void rgb_deSerialize(const char* buffer, int len, RGBType* rgb)
{
	if (buffer[0] == 0)
	{
		rgb_initInstance(rgb);
	}
	else
	{
		sscanf(buffer,"%f %f %f",&rgb->r, &rgb->g, &rgb->b);
	}
}
