#ifndef INCLUDED_DLL_UTILS_H
#define INCLUDED_DLL_UTILS_H

#include <stdio.h>
#include <string.h>

static __inline int getNumberOfStringsXPM(char* xpm[])
{
	int height;
	int width;
	int paletteEntries;
	sscanf(xpm[0],"%i %i %i",&width,&height,&paletteEntries);
	return 1 + paletteEntries + height;
}


static __inline int getSizeOfXPM(char* xpm[])
{
	int i;
	int size = 0;
	int length = getNumberOfStringsXPM(xpm);
	for (i = 0; i < length; ++i)
	{
	  size += strlen(xpm[i]) + 1;
	}

	return size;
}

#endif
