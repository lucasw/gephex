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
    tv.tv_sec = millis/1000;
    tv.tv_usec = (millis%1000)*1000;
    select(0,0,0,0,&tv);
#else
    timespec tspec;
    tspec.tv_sec = millis / 1000;
    tspec.tv_nsec = (millis%1000) *1000*1000;
    nanosleep(&tspec,0);
#endif
#elif defined(OS_WIN32)
    Sleep(millis);
#endif
  }
}
