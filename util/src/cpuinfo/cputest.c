#include "cpuinfo.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
  const char* answer;
  char vendor[13];
  char cpu_name[49];

  if (!cpuinfo_has_cpuid())
    {
      fprintf(stderr, "Cpu does not support CPUID, aborting.\n");
      return 0;
    }

  cpuinfo_get_vendor(vendor);
  cpuinfo_get_cpu_name(cpu_name);

  printf("Cpu vendor:\t\t%s\n", vendor);
  printf("Cpu name:\t\t%s\n", cpu_name);

  if (cpuinfo_has_mmx()) answer = "yes"; else answer = "no";
  printf("MMX support:\t\t%s\n", answer);

  if (cpuinfo_has_sse()) answer = "yes"; else answer = "no";
  printf("SSE support:\t\t%s\n", answer);

  if (cpuinfo_has_sse2()) answer = "yes"; else answer = "no";
  printf("SSE2 support:\t\t%s\n", answer);

  if (cpuinfo_has_3dnow()) answer = "yes"; else answer = "no";
  printf("3dnow support:\t\t%s\n", answer);

  if (cpuinfo_has_e3dnow()) answer = "yes"; else answer = "no";
  printf("e3dnow support:\t\t%s\n", answer);

  return 0;
}
