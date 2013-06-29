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

#ifndef INCLUDED_CPUINFO_H
#define INCLUDED_CPUINFO_H

#if defined(__cplusplus)
extern "C"
{
#endif

  /**
   * C-interface for TheMadmans CpuInfo class.
   * Note: less comfortable than the original class:
   * you first have to check whether the cpu supports cpuid
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

