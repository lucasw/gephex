# Microsoft Developer Studio Generated NMAKE File, Based on joystickmodule.dsp
!IF "$(CFG)" == ""
CFG=joystickmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. joystickmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "joystickmodule - Win32 Release" && "$(CFG)" != "joystickmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "joystickmodule.mak" CFG="joystickmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "joystickmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "joystickmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "joystickmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\joystickmodule.dll"

!ELSE 

ALL : "libjoystick - Win32 Release" "$(OUTDIR)\joystickmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libjoystick - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\joystickmodule.obj"
	-@erase "$(INTDIR)\joystickmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\joystickmodule.dll"
	-@erase "$(OUTDIR)\joystickmodule.exp"
	-@erase "$(OUTDIR)\joystickmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../" /I "../../../types/src/stringtype" /I "../../../types/src/miditype" /I "../libmidi" /I "../../../util/src/libjoystick" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "joystickmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\joystickmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\joystickmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\joystickmodule.pdb" /machine:I386 /def:".\joystickmodule.def" /out:"$(OUTDIR)\joystickmodule.dll" /implib:"$(OUTDIR)\joystickmodule.lib" /libpath:"$(SDL_DIR)/lib" 
DEF_FILE= \
	".\joystickmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\joystickmodule.obj" \
	"$(INTDIR)\joystickmodule_auto.obj" \
	"..\..\..\util\src\libjoystick\Release\libjoystick.lib"

"$(OUTDIR)\joystickmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\joystickmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libjoystick - Win32 Release" "$(OUTDIR)\joystickmodule.dll"
   copy .\Release\joystickmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "joystickmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\joystickmodule.dll"

!ELSE 

ALL : "libjoystick - Win32 Debug" "$(OUTDIR)\joystickmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libjoystick - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\joystickmodule.obj"
	-@erase "$(INTDIR)\joystickmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\joystickmodule.dll"
	-@erase "$(OUTDIR)\joystickmodule.exp"
	-@erase "$(OUTDIR)\joystickmodule.ilk"
	-@erase "$(OUTDIR)\joystickmodule.lib"
	-@erase "$(OUTDIR)\joystickmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/miditype" /I "../libmidi" /I "../../../util/src/libjoystick" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "joystickmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\joystickmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\joystickmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\joystickmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\joystickmodule.def" /out:"$(OUTDIR)\joystickmodule.dll" /implib:"$(OUTDIR)\joystickmodule.lib" /pdbtype:sept /libpath:"$(SDL_DIR)/lib" 
DEF_FILE= \
	".\joystickmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\joystickmodule.obj" \
	"$(INTDIR)\joystickmodule_auto.obj" \
	"..\..\..\util\src\libjoystick\Debug\libjoystick.lib"

"$(OUTDIR)\joystickmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\joystickmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libjoystick - Win32 Debug" "$(OUTDIR)\joystickmodule.dll"
   copy .\Debug\joystickmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("joystickmodule.dep")
!INCLUDE "joystickmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "joystickmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "joystickmodule - Win32 Release" || "$(CFG)" == "joystickmodule - Win32 Debug"
SOURCE=.\joystickmodule.cpp

"$(INTDIR)\joystickmodule.obj" : $(SOURCE) "$(INTDIR)" ".\joystickmodule.h" "..\..\..\config.h"


SOURCE=.\joystickmodule_auto.c

"$(INTDIR)\joystickmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\joystickmodule.h"


!IF  "$(CFG)" == "joystickmodule - Win32 Release"

"libjoystick - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Release" 
   cd "..\..\..\modules\src\joystickmodule"

"libjoystick - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\joystickmodule"

!ELSEIF  "$(CFG)" == "joystickmodule - Win32 Debug"

"libjoystick - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Debug" 
   cd "..\..\..\modules\src\joystickmodule"

"libjoystick - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\libjoystick"
   $(MAKE) /$(MAKEFLAGS) /F ".\libjoystick.mak" CFG="libjoystick - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\joystickmodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "joystickmodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "joystickmodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\joystickmodule.spec

!IF  "$(CFG)" == "joystickmodule - Win32 Release"

InputPath=.\joystickmodule.spec
InputName=joystickmodule

".\joystickmodule.h"	".\joystickmodule_auto.c"	".\joystickmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "joystickmodule - Win32 Debug"

InputPath=.\joystickmodule.spec
InputName=joystickmodule

".\joystickmodule.h"	".\joystickmodule_auto.c"	".\joystickmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

