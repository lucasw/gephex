#include "dualmonitor.h"

#include <stdio.h>

#define COMPILE_MULTIMON_STUBS
#include <multimon.h>

typedef struct MonitorList_
{
	int size;
	HMONITOR hmon[10];	
	
} MonitorList;

BOOL CALLBACK monitorEnumProc(
  HMONITOR hMonitor,  // handle to display monitor
  HDC hdcMonitor,     // handle to monitor DC
  LPRECT lprcMonitor, // monitor intersection rectangle
  LPARAM dwData       // data
)
{
	MonitorList* ml = (MonitorList*) dwData;
	ml->hmon[ml->size] = hMonitor;
	++ml->size;

	return TRUE;
}


//  
// Returns the rectangle of a monitor
//
void GetMonitorRect(LPRECT prc, HMONITOR hMonitor)
{    
    MONITORINFO mi;
    //
    // get the work area or entire monitor rect.
    //
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);

    *prc = mi.rcMonitor;	
}

BOOL MaximizeWindowOnMonitor(HWND hwnd, int monitor)
{
	RECT rc;
	MonitorList ml;
	ml.size = 0;
	if (!EnumDisplayMonitors( 0,0,monitorEnumProc,(long) &ml ))
	{
		//MessageBox(NULL,"Keine Monitor Info gekriegt!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		fprintf(stderr,"Keine Monitor Info gekriegt!");
		return FALSE;
	}
	if (monitor >= ml.size)
	{
		//MessageBox(NULL,"Den Monitor gibts nicht!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		fprintf(stderr,"Den Monitor gibts nicht!");
		return FALSE;
	}
	
	GetMonitorRect(&rc,ml.hmon[monitor]);
	SetWindowPos(hwnd, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	return TRUE;
}

