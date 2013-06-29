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

#include "cpuinfo.h"

#include "config.h"


CpuInfo::CpuInfo()
{
	has_cpuid = check_cpuid();
	if (!has_cpuid)
		return;

	vendor = new char[13];
	for (int i = 0; i < 13; i++) vendor[i] = 0;

	cpu_name = new char[255];

	check_cpu_name(cpu_name);

	check_vendor(vendor);

	has_mmx = check_mmx();
	//has_mmxp = check_mmxp();		// fix this!
	has_3dnow = check_3dnow();
	has_e3dnow = check_e3dnow();
	has_sse = check_sse();
	has_sse2 = check_sse2();
}

CpuInfo::~CpuInfo()
{
}

bool CpuInfo::check_cpuid()
{
	long t = 0;

#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
		pushfd				// Save EFLAGS to stack
		pop eax				// Store EFLAGS in EAX
		mov ebx, eax		// Save in EBX for testing later
		xor eax, 00200000h	// Switch bit 21
		push eax			// Copy changed value to stack
		popfd				// Save changed EAX to EFLAGS
		pushfd				// Push EFLAGS to top of stack
		pop eax				// Store EFLAGS in EAX
		cmp eax, ebx		// See if bit 21 has changed
		jz END				// Quit if no CPUID found
        mov eax, 1			// Else set t to 1
        mov t, eax
        END:
	}
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
		("
			pushfl;
			popl %%eax;
			movl %%eax, %%ebx;
			xorl $0x00200000, %%eax;
			pushl %%eax;
			popfl;
			pushfl;
			popl %%eax;
			cmpl %%eax, %%ebx;
			jz 0f;
			mov $1, %%eax;
			mov %%eax, %0;
			0:;"
			:"=g"(t)::"eax","ebx","memory"
		);
#endif

	if (t) return true;
	else return false;
}

bool CpuInfo::check_mmx()
{
    long a;
    
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
        mov eax, 1
        CPUID
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	(
		"cpuid"
		:	"=d" (a)
		:	"a" (1)
	);
#endif

    if (a & 0x800000) return true;
    else return false;
}

// fix this! wrong results in intel pIII
// removed from public access
bool CpuInfo::check_mmxp(){
    long a;
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
        mov eax, 0x80000001
        CPUID
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("CPUID"
		:	"=d"(a)
		:	"a"(0x80000001)
	);
#endif

    //if (a & 0x400000) return true;
	if (a & 0x1000000) return true;
    else return false;
}


void CpuInfo::check_vendor(char *c)
{
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
		mov eax, 0
		cpuid
		mov eax, c
		mov [eax], ebx
		mov [eax]+4, edx
		mov [eax]+8, ecx
	}
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("
		cpuid;
		movl %1, %%eax;
		movl %%ebx, (%%eax);
		movl %%edx, 4(%%eax);
		movl %%ecx, 8(%%eax);
		"
		:
		:	"a"(0),"g"(c)
		:	"ebx","ecx","edx"
	);

#endif
}

void CpuInfo::check_cpu_name(char *c)
{
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
		mov eax, 0x80000002
		cpuid
		mov edi, c
		mov [edi], eax
		mov [edi]+4, ebx
		mov [edi]+8, ecx
		mov [edi]+12, edx
		mov eax, 0x80000003
		cpuid
		add edi, 16
		mov [edi], eax
		mov [edi]+4, ebx
		mov [edi]+8, ecx
		mov [edi]+12, edx
		mov eax, 0x80000004
		cpuid
		add edi, 32
		mov [edi], eax
		mov [edi]+4, ebx
		mov [edi]+8, ecx
		mov [edi]+12, edx
	}
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("
		movl $0x80000002, %%eax;
		cpuid;
		movl %1, %%edi;
		movl %%eax, (%%edi);
		movl %%ebx, 4(%%edi);
		movl %%ecx, 8(%%edi);
		movl %%edx, 12(%%edi);
		movl $0x80000003, %%eax;
		cpuid;
		addl $16, %%edi
		movl %%eax, (%%edi);
		movl %%ebx, 4(%%edi);
		movl %%ecx, 8(%%edi);
		movl %%edx, 12(%%edi);
		movl $0x80000004, %%eax;
		cpuid;
		addl $32, %%edi
		movl %%eax, (%%edi);
		movl %%ebx, 4(%%edi);
		movl %%ecx, 8(%%edi);
		movl %%edx, 12(%%edi);
		"
		:"=g"(c)
		:"g"(c)
		:"eax","ebx","ecx","edx","edi"
	);
#endif

}

bool CpuInfo::check_3dnow(){
    long a;
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
        mov eax, 0x80000001
        CPUID
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("CPUID"
		:	"=d"(a)
		:	"a"(0x80000001)
	);
#endif

    if (a & 0x80000000) return true;
    else return false;
}

bool CpuInfo::check_e3dnow(){
    long a;
#if defined(COMP_VC) && defined(CPU_I386)
	_asm
	{
        mov eax, 0x80000001
        CPUID
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("CPUID"
		:	"=d"(a)
		:	"a"(0x80000001)
	);
#endif

    if (a & 0x40000000) return true;
    else return false;
}


bool CpuInfo::check_sse(){
	long a;

#if defined(COMP_VC) && defined(CPU_I386)
    _asm
	{
    	mov	eax, 1
        cpuid
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("CPUID"
		:"=d"(a)
		:"a"(1)
	);
#endif
    if (a & 0x2000000) return true;
    return false;
}


bool CpuInfo::check_sse2(){
	long a;

#if defined(COMP_VC) && defined(CPU_I386)
    _asm
	{
    	mov	eax, 1
        cpuid
        mov a, edx
    }
#endif

#if defined(COMP_GNUC) && defined(CPU_I386)
	asm
	("CPUID"
		:"=d"(a)
		:"a"(1)
	);
#endif
    if (a & 0x4000000) return true;
    return false;
}

int CpuInfo::get_cpuid()
{
	if (!has_cpuid) return 0;
	return 1;
}

char *CpuInfo::get_vendor()
{
	return vendor;
}

char *CpuInfo::get_cpu_name()
{
	return cpu_name;
}

int CpuInfo::get_mmx()
{
	if (!has_cpuid) return -1;
	return has_mmx;
}
/*
int CpuInfo::get_mmxp()
{
	if (!has_cpuid) return -1;
	return has_mmxp;
}
*/
int CpuInfo::get_3dnow()
{
	if (!has_cpuid) return -1;
	return has_3dnow;
}
int CpuInfo::get_e3dnow()
{
	if (!has_cpuid) return -1;
	return has_e3dnow;
}
int CpuInfo::get_sse()
{
	if (!has_cpuid) return -1;
	return has_sse;
}
int CpuInfo::get_sse2()
{
	if (!has_cpuid) return -1;
	return has_sse2;
}
