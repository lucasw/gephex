# Microsoft Developer Studio Generated NMAKE File, Based on guimodel.dsp
!IF "$(CFG)" == ""
CFG=guimodel - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. guimodel - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "guimodel - Win32 Release" && "$(CFG)" != "guimodel - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "guimodel.mak" CFG="guimodel - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "guimodel - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "guimodel - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "guimodel - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\guimodel.lib"

!ELSE 

ALL : "netinterfaces - Win32 Release" "interfaces - Win32 Release" "$(OUTDIR)\guimodel.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"interfaces - Win32 ReleaseCLEAN" "netinterfaces - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\controlmodel.obj"
	-@erase "$(INTDIR)\controlvaluedispatcher.obj"
	-@erase "$(INTDIR)\enginewrapper.obj"
	-@erase "$(INTDIR)\graphmodel.obj"
	-@erase "$(INTDIR)\moduleclassmodel.obj"
	-@erase "$(INTDIR)\moduledatadispatcher.obj"
	-@erase "$(INTDIR)\moduleinfo.obj"
	-@erase "$(INTDIR)\point.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xpm.obj"
	-@erase "$(OUTDIR)\guimodel.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_MBCS" /D "_LIB" /D "NDEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\guimodel.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\guimodel.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlmodel.obj" \
	"$(INTDIR)\controlvaluedispatcher.obj" \
	"$(INTDIR)\enginewrapper.obj" \
	"$(INTDIR)\graphmodel.obj" \
	"$(INTDIR)\moduleclassmodel.obj" \
	"$(INTDIR)\moduledatadispatcher.obj" \
	"$(INTDIR)\moduleinfo.obj" \
	"$(INTDIR)\point.obj" \
	"$(INTDIR)\xpm.obj" \
	"..\..\..\base\lib\netinterfaces.lib"

"$(OUTDIR)\guimodel.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "guimodel - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\config.h" "$(OUTDIR)\guimodel.lib"

!ELSE 

ALL : "netinterfaces - Win32 Debug" "interfaces - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\guimodel.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"interfaces - Win32 DebugCLEAN" "netinterfaces - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\controlmodel.obj"
	-@erase "$(INTDIR)\controlvaluedispatcher.obj"
	-@erase "$(INTDIR)\enginewrapper.obj"
	-@erase "$(INTDIR)\graphmodel.obj"
	-@erase "$(INTDIR)\moduleclassmodel.obj"
	-@erase "$(INTDIR)\moduledatadispatcher.obj"
	-@erase "$(INTDIR)\moduleinfo.obj"
	-@erase "$(INTDIR)\point.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xpm.obj"
	-@erase "$(OUTDIR)\guimodel.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_MBCS" /D "_LIB" /D "_DEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\guimodel.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\guimodel.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlmodel.obj" \
	"$(INTDIR)\controlvaluedispatcher.obj" \
	"$(INTDIR)\enginewrapper.obj" \
	"$(INTDIR)\graphmodel.obj" \
	"$(INTDIR)\moduleclassmodel.obj" \
	"$(INTDIR)\moduledatadispatcher.obj" \
	"$(INTDIR)\moduleinfo.obj" \
	"$(INTDIR)\point.obj" \
	"$(INTDIR)\xpm.obj" \
	"..\..\..\base\lib\netinterfaces.lib"

"$(OUTDIR)\guimodel.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("guimodel.dep")
!INCLUDE "guimodel.dep"
!ELSE 
!MESSAGE Warning: cannot find "guimodel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "guimodel - Win32 Release" || "$(CFG)" == "guimodel - Win32 Debug"
SOURCE=.\controlmodel.cpp

"$(INTDIR)\controlmodel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\controlvaluedispatcher.cpp

"$(INTDIR)\controlvaluedispatcher.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\enginewrapper.cpp

"$(INTDIR)\enginewrapper.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\graphmodel.cpp

"$(INTDIR)\graphmodel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassmodel.cpp

"$(INTDIR)\moduleclassmodel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduledatadispatcher.cpp

"$(INTDIR)\moduledatadispatcher.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleinfo.cpp

"$(INTDIR)\moduleinfo.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\point.cpp

"$(INTDIR)\point.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xpm.cpp

"$(INTDIR)\xpm.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "guimodel - Win32 Release"

"interfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" 
   cd "..\..\..\qtgui\src\guimodel"

"interfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\guimodel"

!ELSEIF  "$(CFG)" == "guimodel - Win32 Debug"

"interfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" 
   cd "..\..\..\qtgui\src\guimodel"

"interfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\guimodel"

!ENDIF 

!IF  "$(CFG)" == "guimodel - Win32 Release"

"netinterfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" 
   cd "..\..\..\qtgui\src\guimodel"

"netinterfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\guimodel"

!ELSEIF  "$(CFG)" == "guimodel - Win32 Debug"

"netinterfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" 
   cd "..\..\..\qtgui\src\guimodel"

"netinterfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\guimodel"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "guimodel - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "guimodel - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

