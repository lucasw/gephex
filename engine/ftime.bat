PREP /OM /FT /EXC nafxcwd.lib %1
if errorlevel == 1 goto done 
PROFILE %1 %2 %3 %4 %5 %6 %7 %8 %9
if errorlevel == 1 goto done 
PREP /M %1
if errorlevel == 1 goto done 
PLIST /SC %1 >%1.lst
:done

