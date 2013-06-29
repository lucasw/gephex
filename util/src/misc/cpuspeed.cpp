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

#include "cpuspeed.h"

#include "config.h"

#if defined(OS_POSIX)
#include <sys/io.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#ifdef OS_WIN32
#include <windows.h>
#endif


CpuSpeed::CpuSpeed()
{
	cpu_speed = -1;
}

CpuSpeed::~CpuSpeed()
{
}


double CpuSpeed::get_cpu_speed()
{
	if (cpu_speed < 0.0)
	{
		cpu_speed = calc_cpu_speed();
		return cpu_speed;
	}
	else return cpu_speed;
}


double CpuSpeed::calc_cpu_speed()
{
#if defined(COMP_VC) && defined(CPU_I386) && defined(OS_WIN32)
	LARGE_INTEGER   ulFreq, ulTicks, ulValue, ulStartCounter, ulEAX_EDX, ulResult;
	    
	QueryPerformanceFrequency(&ulFreq); 	   
	QueryPerformanceCounter(&ulTicks);   

	ulValue.QuadPart = ulTicks.QuadPart + ulFreq.QuadPart;    

	__asm RDTSC     
	__asm mov ulEAX_EDX.LowPart, EAX         
	__asm mov ulEAX_EDX.HighPart, EDX       

	ulStartCounter.QuadPart = ulEAX_EDX.QuadPart;                 

	do
	{	         
		QueryPerformanceCounter(&ulTicks); 
	}while( ulTicks.QuadPart <= ulValue.QuadPart) ;         

	__asm RDTSC       
	__asm mov ulEAX_EDX.LowPart, EAX        
	__asm mov ulEAX_EDX.HighPart,EDX       

	ulResult.QuadPart = ulEAX_EDX.QuadPart - ulStartCounter.QuadPart;  

	return ulResult.QuadPart/1000000.0;
#endif

#if defined(OS_POSIX) && defined(COMP_GNUC) && defined(CPU_I386)

	double cpu_speed = -1.0;

	if (getuid() == 0) 
	{

		int CLOCKHZ = 1193182;
		int COUNTER = 65536;

		double stamp0, stamp1, cpu_cycles;
		double cpu_hertz;

		ioperm(0x61, 1, 1);
		ioperm(0x42, 2, 1);

		outb(inb(0x61) | 1, 0x61); // enable channel 2 input
		outb(0xB0, 0x43); // chn-2, lsb/msb, oneshot, binary
		outb((COUNTER >> 0) & 0xFF, 0x42); // chn-2 latch-lsb
		outb((COUNTER >> 8) & 0xFF, 0x42); // chn-2 latch-msb

		stamp0 = read_tsc();

		while ((inb(0x61) & 0x20) == 0); // await countdown

		stamp1 = read_tsc();

		outb(inb(0x61) & ~(1), 0x61); // disable channel 2 input
		cpu_cycles = stamp1 - stamp0; // cycles during countdown

		cpu_hertz = cpu_cycles * CLOCKHZ / COUNTER;
		cpu_speed = cpu_hertz / 1000000; // convert Hz to MHz

	}
	else
	{
		FILE *f = fopen("/proc/cpuinfo", "rt");
		if (!f)	return -1.0;

		char *line = new char[256];

		while (!feof(f)){
			fgets(line, 256, f);
			if (strstr(line, "cpu MHz")) break;
		}
		char *pos = strstr(line, ":")+1;
		if (pos && !feof(f))
		{ 
			cpu_speed = strtod(pos, NULL);
		}

		delete line;
		fclose(f);
	}

	return cpu_speed;

#endif

}


double CpuSpeed::read_tsc()
{
	double t;
	void *t2 = &t;

#if defined(COMP_VC) && defined(CPU_I386)
	_asm{
		rdtsc
		mov edi, t2
		mov [edi], eax
		mov [edi+4], edx
		fild qword ptr [edi]
		fstp qword ptr [edi]           
	}
#endif


#if defined(COMP_GNUC) && defined(CPU_I386)
	unsigned int tmp1;
	unsigned int tmp2;
	__asm__ __volatile__
		("rdtsc\n"
		:"=a"(tmp1),"=d"(tmp2)
	);
	t = ((double)tmp1) + ((double)tmp2*4294967296.0);
#endif

	return t;
}
