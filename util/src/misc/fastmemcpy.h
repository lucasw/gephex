/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
