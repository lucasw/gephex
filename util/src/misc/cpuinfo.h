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

