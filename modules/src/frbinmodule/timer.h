#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include <windows.h>

struct timer_info;

class TimerCallback
{
public:
	virtual void operator()() = 0;
};

class Timer
{
public:
	Timer(unsigned long period_ms, TimerCallback* cb);
	~Timer();

private:
	timer_info* m_info;
	HANDLE m_thread;

};


#endif
