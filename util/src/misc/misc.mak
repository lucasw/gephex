# Microsoft Developer Studio Generated NMAKE File, Based on misc.dsp
!IF "$(CFG)" == ""
CFG=misc - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. misc - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "misc - Win32 Release" && "$(CFG)" != "misc - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "misc - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "$(OUTDIR)\misc.lib"


CLEAN :
	-@erase "$(INTDIR)\cpuinfo.obj"
	-@erase "$(INTDIR)\cpuspeed.obj"
	-@erase "$(INTDIR)\fastmemcpy.obj"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\misc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /I "../../../" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\misc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cpuinfo.obj" \
	"$(INTDIR)\cpuspeed.obj" \
	"$(INTDIR)\fastmemcpy.obj" \
	"$(INTDIR)\timer.obj"

"$(OUTDIR)\misc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\misc.lib"


CLEAN :
	-@erase "$(INTDIR)\cpuinfo.obj"
	-@erase "$(INTDIR)\cpuspeed.obj"
	-@erase "$(INTDIR)\fastmemcpy.obj"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\misc.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../../../" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\misc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cpuinfo.obj" \
	"$(INTDIR)\cpuspeed.obj" \
	"$(INTDIR)\fastmemcpy.obj" \
	"$(INTDIR)\timer.obj"

"$(OUTDIR)\misc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("misc.dep")
!INCLUDE "misc.dep"
!ELSE 
!MESSAGE Warning: cannot find "misc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "misc - Win32 Release" || "$(CFG)" == "misc - Win32 Debug"
SOURCE=.\cpuinfo.cpp

"$(INTDIR)\cpuinfo.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\cpuspeed.cpp

"$(INTDIR)\cpuspeed.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\fastmemcpy.cpp

"$(INTDIR)\fastmemcpy.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\timer.cpp

"$(INTDIR)\timer.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "misc - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

