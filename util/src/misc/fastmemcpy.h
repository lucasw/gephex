#ifndef INCLUDED_FASTMEMCPY_H
#define INCLUDED_FASTMEMCPY_H

#include "cpuinfo.h"

class FastMemCpy
{
public:
	FastMemCpy();
	~FastMemCpy();
	//size always in bytes
	int copy(void *dst, void *src, int size);
	void detect_mode();
	void force_mode(int mode);
	int get_mode();
private:
	int mode;
	CpuInfo cinfo;
	int copy_32(void *dst, void *src, int size);
	int copy_mmx(void *dst, void *src, int size);
	int copy_3dnow(void *dst, void *src, int size);
	int copy_sse(void *dst, void *src, int size);
};

/* modes:
	0 = no extras, use copy_32
	1 = mmx
	2 = 3dnow
	3 = e3dnow
	4 = sse
	5 = sse2
*/

#endif
