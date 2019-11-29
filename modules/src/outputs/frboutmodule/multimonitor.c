/* Multimonitor support functions.
   Copyright (C) 2003 Georg Seidel
   This file is part of GePhex.

   GePhex is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   GePhex is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with GePhex; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  
 
   You can reach me via email: georg.seidel@web.de
 */

#include "multimonitor.h"

#include <stdio.h>


#define COMPILE_MULTIMON_STUBS
#if defined (__GNUC__)
// mingw does not have the multimon.h header
#include <windows.h>
#else
#include <multimon.h>
#endif

static void get_error_text(char* buffer, int len);

//-------------------------------------------------------------------------------------

struct MonitorList
{
	int size;
	HMONITOR hmon[10];	
};

static struct MonitorList s_ml;
static int                s_init_called = 0;

//-------------------------------------------------------------------------------------

static BOOL CALLBACK monitorEnumProc(
									 HMONITOR hMonitor,  // handle to display monitor
									 HDC hdcMonitor,     // handle to monitor DC
									 LPRECT lprcMonitor, // monitor intersection rectangle
									 LPARAM dwData       // data
									 )
{
	struct MonitorList* ml = (struct MonitorList*) dwData;
	ml->hmon[ml->size]     = hMonitor;
	++ml->size;
	
	return TRUE;
}

//-------------------------------------------------------------------------------------

int mm_init(char* error_text, int text_len)
{
	if (s_init_called)
		return 1;
	
	s_ml.size = 0;
	
	if (!EnumDisplayMonitors( 0,0, monitorEnumProc, (long) &s_ml ))
	{		
		get_error_text(error_text, text_len);		
		return 0;
	}
	
	s_init_called = 1;
	return 1;
}

int mm_num_monitors(char* error_text, int text_len)
{
	if (s_init_called == 0)
	{
		_snprintf(error_text, text_len, "mm_init not called!");
		return 0;
	}
	
	return s_ml.size;
}

// returns 1 on success
int mm_move_to_monitor(HWND hwnd, int monitor, char* error_text, int text_len)
{
	RECT rc;	
	int res;	
	
	res = mm_get_monitor_rect(&rc, monitor, error_text, text_len);
	if (res != 1) {
		return 0;
	}
	
	SetWindowPos(hwnd, NULL, rc.left, rc.top, 0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	return 1;	
	
}

// returns 1 on success
int mm_get_monitor_rect(LPRECT prc, int monitor, char* error_text, int text_len)
{
	MONITORINFO mi;
	HMONITOR hMonitor;
	
    if (s_init_called == 0)
	{
		_snprintf(error_text, text_len, "mm_init not called!");
		return 0;
	}
	
	if (monitor >= s_ml.size)
	{		
		_snprintf(error_text, text_len,"Monitor #%i does not exist!", monitor);
		return 0;
	}
	
	hMonitor  = s_ml.hmon[monitor];
    mi.cbSize = sizeof(mi);
	
    GetMonitorInfo(hMonitor, &mi);
	
    *prc = mi.rcMonitor;
	return 1;
}


//-------------------------------------------------------------------------------------

static void get_error_text(char* buffer, int len)
{
    LPVOID lpMsgBuf;
    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL 
        );
    _snprintf(buffer, len, "%s", (LPCTSTR) lpMsgBuf);
    LocalFree( lpMsgBuf );
}
