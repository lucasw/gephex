#include "timing.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/time.h>
#elif defined(OS_WIN32)
#include <windows.h>
#include <sys/timeb.h>
#endif

#include <ctime>

namespace utils {

  unsigned long Timing::getTimeInMillis()
  {
#if defined(OS_POSIX)
    struct timeval tv;
    gettimeofday(&tv, 0);
    unsigned long time = tv.tv_sec*1000 + tv.tv_usec/1000;
#elif defined(OS_WIN32)
	struct _timeb timebuffer;

	_ftime( &timebuffer );

	unsigned long time = timebuffer.time*1000 + timebuffer.millitm;
#endif

    return time;
  }

  void Timing::sleep(unsigned long millis)
  {
#if defined(OS_POSIX)
#if defined(OS_CYGWIN)
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = millis*1000;
    select(0,0,0,0,&tv);
#else
    timespec tspec;
    tspec.tv_sec = 0;
    tspec.tv_nsec = millis*1000*1000;
    nanosleep(&tspec,0);
#endif
#elif defined(OS_WIN32)
    Sleep(millis);
#endif
  }
}
