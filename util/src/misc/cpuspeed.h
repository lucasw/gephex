class CpuSpeed
{
public:
	CpuSpeed();
	~CpuSpeed();
	double get_cpu_speed();		// detect only if not already done
	double calc_cpu_speed();	// force detection of cpu-speed
private:
	double read_tsc();

	double cpu_speed;
};