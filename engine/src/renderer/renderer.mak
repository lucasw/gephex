# Microsoft Developer Studio Generated NMAKE File, Based on renderer.dsp
!IF "$(CFG)" == ""
CFG=renderer - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. renderer - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "renderer - Win32 Release" && "$(CFG)" != "renderer - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "renderer.mak" CFG="renderer - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "renderer - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "renderer - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "renderer - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\config.h" "$(OUTDIR)\renderer.lib"


CLEAN :
	-@erase "$(INTDIR)\modulefactory.obj"
	-@erase "$(INTDIR)\renderer.obj"
	-@erase "$(INTDIR)\runtimesystem.obj"
	-@erase "$(INTDIR)\typefactory.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\renderer.lib"
	-@erase "..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../" /I ".." /I "../../../base/src" /I "../../../" /D "_LIB" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\renderer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\renderer.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\renderer.lib" 
LIB32_OBJS= \
	"$(INTDIR)\modulefactory.obj" \
	"$(INTDIR)\renderer.obj" \
	"$(INTDIR)\runtimesystem.obj" \
	"$(INTDIR)\typefactory.obj"

"$(OUTDIR)\renderer.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "renderer - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\renderer.lib"


CLEAN :
	-@erase "$(INTDIR)\modulefactory.obj"
	-@erase "$(INTDIR)\renderer.obj"
	-@erase "$(INTDIR)\runtimesystem.obj"
	-@erase "$(INTDIR)\typefactory.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\renderer.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I ".." /I "../../../base/src" /I "../../../" /D "_LIB" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D ENGINE_VERBOSITY=0 /Fp"$(INTDIR)\renderer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\renderer.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\renderer.lib" 
LIB32_OBJS= \
	"$(INTDIR)\modulefactory.obj" \
	"$(INTDIR)\renderer.obj" \
	"$(INTDIR)\runtimesystem.obj" \
	"$(INTDIR)\typefactory.obj"

"$(OUTDIR)\renderer.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("renderer.dep")
!INCLUDE "renderer.dep"
!ELSE 
!MESSAGE Warning: cannot find "renderer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "renderer - Win32 Release" || "$(CFG)" == "renderer - Win32 Debug"
SOURCE=.\modulefactory.cpp

"$(INTDIR)\modulefactory.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\renderer.cpp

"$(INTDIR)\renderer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\runtimesystem.cpp

"$(INTDIR)\runtimesystem.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\typefactory.cpp

"$(INTDIR)\typefactory.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "renderer - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "renderer - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

