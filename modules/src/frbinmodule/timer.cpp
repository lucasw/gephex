#include "timer.h"

#include <stdexcept>

struct timer_info
{
	timer_info(unsigned long p, TimerCallback* c)
		: period(p), cb(c) {}

	unsigned long period;
	TimerCallback* cb;
};

static DWORD WINAPI ThreadFunc( LPVOID param ) 
{ 
	timer_info* ti = (timer_info*) param;

	while (true)
	{
		Sleep(ti->period);
		ti->cb->operator()();
	}
    

    return 0; 
} 

Timer::Timer(unsigned long period_ms, TimerCallback* cb)
  : m_info(new timer_info(period_ms, cb))
{
    DWORD dwThreadId;    
    m_thread = CreateThread( 
        NULL,                        // no security attributes 
        0,                           // use default stack size  
        ThreadFunc,                  // thread function 
        m_info,                      // argument to thread function 
        0,                           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
 
   // Check the return value for success. 
 
   if (m_thread == 0) 
   {
	   throw std::runtime_error("CreateThread() failed");       
   }
}

Timer::~Timer()
{
	TerminateThread(m_thread, 1);
	CloseHandle( m_thread );
	
	delete m_info->cb;
	delete m_info;
}