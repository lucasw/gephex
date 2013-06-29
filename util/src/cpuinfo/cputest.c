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
