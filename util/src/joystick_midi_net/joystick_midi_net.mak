# Microsoft Developer Studio Generated NMAKE File, Based on joystick_midi_net.dsp
!IF "$(CFG)" == ""
CFG=joystick_midi_net - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. joystick_midi_net - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "joystick_midi_net - Win32 Release" && "$(CFG)" != "joystick_midi_net - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "joystick_midi_net.mak" CFG="joystick_midi_net - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "joystick_midi_net - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "joystick_midi_net - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "joystick_midi_net - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\joystick_midi_net.exe"

!ELSE 

ALL : "libjoystick - Win32 Release" "$(OUTDIR)\joystick_midi_net.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libjoystick - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\joystick_midi_net.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\joystick_midi_net.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /I "../libjoystick" /I "../../../" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\joystick_midi_net.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\joystick_midi_net.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\joystick_midi_net.pdb" /machine:I386 /out:"$(OUTDIR)\joystick_midi_net.exe" 
LINK32_OBJS= \
	"$(INTDIR)\joystick_midi_net.obj" \
	"..\libjoystick\Release\libjoystick.lib"

"$(OUTDIR)\joystick_midi_net.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
PostBuild_Desc=installing exe...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libjoystick - Win32 Release" "$(OUTDIR)\joystick_midi_net.exe"
   mkdir ..\..\..\bin
	copy Release\joystick_midi_net.exe ..\..\..\bin
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "joystick_midi_net - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\config.h" "$(OUTDIR)\joystick_midi_net.exe"

!ELSE 

ALL : "libjoystick - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\joystick_midi_net.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libjoystick - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\joystick_midi_net.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\joystick_midi_net.exe"
	-@erase "$(OUTDIR)\joystick_midi_net.ilk"
	-@erase "$(OUTDIR)\joystick_midi_net.pdb"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../libjoystick" /I "../../../" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\joystick_midi_net.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\joystick_midi_net.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\joystick_midi_net.pdb" /debug /machine:I386 /out:"$(OUTDIR)\joystick_midi_net.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\joystick_midi_net.obj" \
	"..\libjoystick\Debug\libjoystick.lib"

"$(OUTDIR)\joystick_midi_net.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
PostBuild_Desc=installing exe...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libjoystick - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\joystick_midi_net.exe"
   mkdir ..\..\..\bin
	copy Debug\joystick_midi_net.exe ..\..\..\bin
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("joystick_midi_net.dep")
!INCLUDE "joystick_midi_net.dep"
!ELSE 
!MESSAGE Warning: cannot find "joystick_midi_net.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "joystick_midi_net - Win32 Release" || "$(CFG)" == "joystick_midi_net - Win32 Debug"
SOURCE=.\joystick_midi_net.cpp

"$(INTDIR)\joystick_midi_net.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


!IF  "$(CFG)" == "joystick_midi_net - Win32 Release"

"libjoystick - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Release" 
   cd "..\joystick_midi_net"

"libjoystick - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Release" RECURSE=1 CLEAN 
   cd "..\joystick_midi_net"

!ELSEIF  "$(CFG)" == "joystick_midi_net - Win32 Debug"

"libjoystick - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Debug" 
   cd "..\joystick_midi_net"

"libjoystick - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\joystick_midi_net"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "joystick_midi_net - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "joystick_midi_net - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

