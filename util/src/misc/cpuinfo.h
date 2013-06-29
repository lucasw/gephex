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

class CpuInfo
{
public:
	CpuInfo();		// Constructor reads cpu-flags
	~CpuInfo();

	char *get_vendor();
	char *get_cpu_name();

	int get_cpuid();	// 1 == true
	int get_mmx();
	//int get_mmxp();
	int get_3dnow();
	int get_e3dnow();
	int get_sse();
	int get_sse2();


private:
	bool check_cpuid();
	bool check_mmx();
	bool check_mmxp();
	void check_vendor(char *c);
	void check_cpu_name(char *c);
	bool check_3dnow();
	bool check_e3dnow();
	bool check_sse();
	bool check_sse2();

	char *vendor;
	char *cpu_name;

	bool has_cpuid;
	bool has_mmx;
	bool has_mmxp;
	bool has_3dnow;
	bool has_e3dnow;
	bool has_sse;
	bool has_sse2;


};

#endif

