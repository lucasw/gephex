#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

class Timer
{
public:
	Timer();
	~Timer();
	void start();			//start timer-period
	void stop();			//stop timer-period
	void print();			//print fancy stats to console
	long get_avg_cycles();	//return avg. cycles per timer-period
	int get_runs();			//return numer of timer-periods
	double get_fps();		//avg. return runs per sec
	void reset();			//set back to zero
private:
	double getTime();
	double cycles;
	int runs;
	double start_cycles;
	double cpu_mhz;
};

#endif
