/*=============================================================================
simple timer class

usage:
	timer tm;
	loop{
		tm.start()
		{test-code goes here}
		tm.stop()
	}
	int average_cycles_per_run = tm.get_avg_cycles();

have phun

the.madman
=============================================================================*/

#include <iostream>
#include <iomanip>
#include "timer.h"
#include "cpuspeed.h"
#include "config.h"

using namespace std;

Timer::Timer()
{
	CpuSpeed s;
	cpu_mhz = s.get_cpu_speed();
	cycles = 0;
	runs = 0;
	return;
}

Timer::~Timer()
{
}

void Timer::reset()
{
	cycles = 0;
	runs = 0;
}

void Timer::start()
{
	start_cycles = getTime();
}

void Timer::stop()
{
	cycles += getTime() - start_cycles;
	runs++;
}


void Timer::print()
{
	cout << "done " << runs << " runs with " << cycles << " cycles at " << get_avg_cycles() << " cycles per run (" << get_fps() << " fps)\n";
}


long Timer::get_avg_cycles()
{
	return (long)(cycles/runs);
}

double Timer::get_fps()
{
	return (double)(cpu_mhz*1000000)/(cycles/runs);
}

int Timer::get_runs()
{
	return runs;
}

double Timer::getTime()
{
	double *t = new double();


#if defined(CPU_I386) && defined(COMP_VC)
	_asm{
		rdtsc
		mov edi, t
		mov [edi], eax
		mov [edi+4], edx
		fild qword ptr [edi]
		fstp qword ptr [edi]           
	}
#elif defined(CPU_I386) && defined(COMP_GNUC)
	unsigned int tmp1;
	unsigned int tmp2;
	__asm__ __volatile__
		("rdtsc\n"
		:"=a"(tmp1),"=d"(tmp2)
	);
	t[0] = ((double)tmp1) + ((double)tmp2*4294967296.0);
#else
#warning "Not implemented yet!"
#endif

	return t[0];
}
