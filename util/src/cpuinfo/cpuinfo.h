#ifndef INCLUDED_CPUINFO_H
#define INCLUDED_CPUINFO_H

#if defined(__cplusplus)
extern "C"
{
#endif

  /**
   * C-interface for TheMadmans CpuInfo class.
   * Note: less comfortable than the original class:
   * you first have to check wether the cpu supports cpuid
   * before calling any of the other checks.
   */

int cpuinfo_has_cpuid();

int cpuinfo_has_mmx();

  //int cpuinfo_has_mmxp();

void cpuinfo_get_vendor(char vendor[13]);

void cpuinfo_get_cpu_name(char name[49]);

int cpuinfo_has_3dnow();

int cpuinfo_has_e3dnow();

int cpuinfo_has_sse();

int cpuinfo_has_sse2();

#if defined(__cplusplus)
}
#endif

#endif

