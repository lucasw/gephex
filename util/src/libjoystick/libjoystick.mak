# Microsoft Developer Studio Generated NMAKE File, Based on libjoystick.dsp
!IF "$(CFG)" == ""
CFG=libjoystick - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. libjoystick - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "libjoystick - Win32 Release" && "$(CFG)" != "libjoystick - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "libjoystick.mak" CFG="libjoystick - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "libjoystick - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "libjoystick - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libjoystick - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\libjoystick.lib"


CLEAN :
	-@erase "$(INTDIR)\libjoystick.obj"
	-@erase "$(INTDIR)\sdljoystickdriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32joystickdriver.obj"
	-@erase "$(OUTDIR)\libjoystick.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /I "../../../" /I "$(SDL_DIR)/include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\libjoystick.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libjoystick.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libjoystick.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libjoystick.obj" \
	"$(INTDIR)\sdljoystickdriver.obj" \
	"$(INTDIR)\win32joystickdriver.obj"

"$(OUTDIR)\libjoystick.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libjoystick - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\libjoystick.lib"


CLEAN :
	-@erase "$(INTDIR)\libjoystick.obj"
	-@erase "$(INTDIR)\sdljoystickdriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32joystickdriver.obj"
	-@erase "$(OUTDIR)\libjoystick.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../../../" /I "$(SDL_DIR)/include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\libjoystick.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libjoystick.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libjoystick.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libjoystick.obj" \
	"$(INTDIR)\sdljoystickdriver.obj" \
	"$(INTDIR)\win32joystickdriver.obj"

"$(OUTDIR)\libjoystick.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("libjoystick.dep")
!INCLUDE "libjoystick.dep"
!ELSE 
!MESSAGE Warning: cannot find "libjoystick.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "libjoystick - Win32 Release" || "$(CFG)" == "libjoystick - Win32 Debug"
SOURCE=.\libjoystick.cpp

"$(INTDIR)\libjoystick.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\sdljoystickdriver.cpp

"$(INTDIR)\sdljoystickdriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\win32joystickdriver.cpp

"$(INTDIR)\win32joystickdriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "libjoystick - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "libjoystick - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

