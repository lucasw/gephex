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


#include <memory.h>

#include "fastmemcpy.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

//#define OPT_INCLUDE_SSE
//#define OPT_INCLUDE_3DNOW

FastMemCpy::FastMemCpy()
{
	detect_mode();
}

FastMemCpy::~FastMemCpy()
{
}

void FastMemCpy::detect_mode()
{
	mode = -1;
	if (cinfo.get_cpuid())
	{
		if (cinfo.get_sse2()) mode = 5;
		else if (cinfo.get_sse()) mode = 4;
		else if (cinfo.get_e3dnow()) mode = 3;
		else if (cinfo.get_3dnow()) mode = 2;
		else if (cinfo.get_mmx()) mode = 1;
		else mode = 0;
	}
}

void FastMemCpy::force_mode(int m)
{
	mode = m;
}

int FastMemCpy::get_mode()
{
	return mode;
}

int FastMemCpy::copy(void *dst, void *src, int size)
{
	switch (mode)
	{
	case 4:
		return copy_sse(dst, src, size);
	case 2:
		return copy_3dnow(dst, src, size);
	case 1:
		return copy_mmx(dst, src, size);
	case 0:
		return copy_32(dst, src, size);
	default:
		{
			memcpy(dst, src, size);
			return 1;
		}
	}
	return 0;
}

int FastMemCpy::copy_32(void *dst, void *src, int size)
{
	unsigned int _size = size;
	unsigned int _size2 = size / 12;

#if defined(COMP_VC) && defined(CPU_I386)
	_asm{
		mov esi, src
		mov edi, dst
		mov eax, _size2
		jz part2
		my_loop:
			mov ebx, [esi]
			mov ecx, [esi+4]
			mov edx, [esi+8]
			mov [edi], ebx
			mov [edi+4], ecx
			mov [edi+8], ecx
			add esi, 12
			add edi, 12
			dec eax
		jnz my_loop
		part2:
			mov eax, _size
			shl eax, 24
			shr eax, 24
			jz end
		loop2:
			mov bl, [esi]
			mov [edi], bl
			inc esi
			inc edi
			dec eax
		jnz loop2
		end:

	}
#else
#error "Not implemented yet!"
#endif
	return 1;
}

__inline int FastMemCpy::copy_mmx(void *dst, void *src, int size)
{
	unsigned int _size = size;

#if defined(COMP_VC) && defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
	_asm{
		mov esi, src
		mov edi, dst
		mov eax, _size
		shr eax, 5
		jz part2
		my_loop:
			movq mm0, [esi]
			add esi, 8
			movq mm1, [esi]
			add esi, 8
			movq mm2, [esi]
			add esi, 8
			movq mm3, [esi]
			add esi, 8
			movq [edi], mm0
			add edi, 8
			movq [edi], mm1
			add edi, 8
			movq [edi], mm2
			add edi, 8
			movq [edi], mm3
			add edi, 8
			dec eax
		jnz my_loop
		emms
		part2:
			mov eax, _size
			shl eax, 24
			shr eax, 24
			jz end
		loop2:
			mov bl, [esi]
			mov [edi], bl
			inc esi
			inc edi
			dec eax
		jnz loop2
		end:
	}
#else
#warning "Not implemented yet!"
#endif
	return 1;
}

__inline int FastMemCpy::copy_3dnow(void *dst, void *src, int size)
{
	unsigned int _size = size;

#if defined(COMP_VC) && /*(_MSC_VER >= 1200) &&*/ defined(CPU_I386) && defined(OPT_INCLUDE_3DNOW)
	_asm{
		mov esi, src
		mov edi, dst
		mov eax, _size
		shr eax, 6
		jz part2
		my_loop:
			prefetch [esi]
			prefetch [edi]

			movq mm0, [esi]
			add esi, 8
			movq mm1, [esi]
			add esi, 8
			movq mm2, [esi]
			add esi, 8
			movq mm3, [esi]
			add esi, 8

			prefetch [esi]
			movq mm4, [esi]
			add esi, 8
			movq mm5, [esi]
			add esi, 8
			movq mm6, [esi]
			add esi, 8
			movq mm7, [esi]
			add esi, 8

			movq [edi], mm0
			add edi, 8
			movq [edi], mm1
			add edi, 8
			movq [edi], mm2
			add edi, 8
			movq [edi], mm3
			add edi, 8

			prefetch [edi]
			movq [edi], mm4
			add edi, 8
			movq [edi], mm5
			add edi, 8
			movq [edi], mm6
			add edi, 8
			movq [edi], mm7
			add edi, 8

			dec eax
		jnz my_loop
		femms
		part2:
			mov eax, _size
			shl eax, 24
			shr eax, 24
			jz end
		loop2:
			mov bl, [esi]
			mov [edi], bl
			inc esi
			inc edi
			dec eax
		jnz loop2
		end:
	}
#endif
	return 1;
}

int FastMemCpy::copy_sse(void *dst, void *src, int size)
{
	unsigned int _size = size;

	// does only compile with vc >= 7?
#if defined(COMP_VC) /*&& (_MSC_VER >= 1200)*/ && defined(CPU_I386) && defined(OPT_INCLUDE_SSE)
	_asm{
		mov esi, src
		mov edi, dst
		mov eax, _size
		shr eax, 8
		jz part2
		my_loop:
			prefetchnta [esi]
			movaps xmm0, [esi]
			add esi, 16
			movaps xmm1, [esi]
			add esi, 16

			prefetchnta [esi]
			movaps xmm2, [esi]
			add esi, 16
			movaps xmm3, [esi]
			add esi, 16

			prefetchnta [esi]
			prefetch [esi]
			movaps xmm4, [esi]
			add esi, 16
			movaps xmm5, [esi]
			add esi, 16

			prefetchnta [esi]
			movaps xmm6, [esi]
			add esi, 16
			movaps xmm7, [esi]
			add esi, 16

			movaps [edi], xmm0
			add edi, 16
			movaps [edi], xmm1
			add edi, 16

			prefetchnta [edi]
			movaps [edi], xmm2
			add edi, 16
			movaps [edi], xmm3
			add edi, 16

			prefetchnta [edi]
			movaps [edi], xmm4
			add edi, 16
			movaps [edi], xmm5
			add edi, 16

			prefetchnta [edi]
			movaps [edi], xmm6
			add edi, 16
			movaps [edi], xmm7
			add edi, 16

			dec eax
		jnz my_loop
		part2:
			mov eax, _size
			shl eax, 24
			shr eax, 24
			jz end
		loop2:
			mov bl, [esi]
			mov [edi], bl
			inc esi
			inc edi
			dec eax
		jnz loop2
		end:
	}
#else
//#error "Not implemented yet!"
#endif
	return 1;
}
