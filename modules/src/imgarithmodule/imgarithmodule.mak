# Microsoft Developer Studio Generated NMAKE File, Based on imgarithmodule.dsp
!IF "$(CFG)" == ""
CFG=imgarithmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. imgarithmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "imgarithmodule - Win32 Release" && "$(CFG)" != "imgarithmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "imgarithmodule.mak" CFG="imgarithmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "imgarithmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "imgarithmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\imgarithmodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Release" "$(OUTDIR)\imgarithmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\imgarithmodule.obj"
	-@erase "$(INTDIR)\imgarithmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\imgarithmodule.dll"
	-@erase "$(OUTDIR)\imgarithmodule.exp"
	-@erase "$(OUTDIR)\imgarithmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "imgarithmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imgarithmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\imgarithmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\imgarithmodule.pdb" /machine:I386 /def:".\imgarithmodule.def" /out:"$(OUTDIR)\imgarithmodule.dll" /implib:"$(OUTDIR)\imgarithmodule.lib" 
DEF_FILE= \
	".\imgarithmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\imgarithmodule.obj" \
	"$(INTDIR)\imgarithmodule_auto.obj" \
	"$(INTDIR)\imgarithmodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Release\cpuinfo.lib"

"$(OUTDIR)\imgarithmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\imgarithmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Release" "$(OUTDIR)\imgarithmodule.dll"
   copy .\Release\imgarithmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\imgarithmodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Debug" "$(OUTDIR)\imgarithmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\imgarithmodule.obj"
	-@erase "$(INTDIR)\imgarithmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\imgarithmodule.dll"
	-@erase "$(OUTDIR)\imgarithmodule.exp"
	-@erase "$(OUTDIR)\imgarithmodule.ilk"
	-@erase "$(OUTDIR)\imgarithmodule.lib"
	-@erase "$(OUTDIR)\imgarithmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "imgarithmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imgarithmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\imgarithmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\imgarithmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\imgarithmodule.def" /out:"$(OUTDIR)\imgarithmodule.dll" /implib:"$(OUTDIR)\imgarithmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\imgarithmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\imgarithmodule.obj" \
	"$(INTDIR)\imgarithmodule_auto.obj" \
	"$(INTDIR)\imgarithmodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Debug\cpuinfo.lib"

"$(OUTDIR)\imgarithmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\imgarithmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Debug" "$(OUTDIR)\imgarithmodule.dll"
   copy .\Debug\imgarithmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("imgarithmodule.dep")
!INCLUDE "imgarithmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "imgarithmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "imgarithmodule - Win32 Release" || "$(CFG)" == "imgarithmodule - Win32 Debug"
SOURCE=.\imgarithmodule.c

!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "imgarithmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imgarithmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\imgarithmodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\imgarithmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "imgarithmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imgarithmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\imgarithmodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\imgarithmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\imgarithmodule_auto.c

"$(INTDIR)\imgarithmodule_auto.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\imgarithmodule.h"


!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

"cpuinfo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" 
   cd "..\..\..\modules\src\imgarithmodule"

"cpuinfo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\imgarithmodule"

!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

"cpuinfo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" 
   cd "..\..\..\modules\src\imgarithmodule"

"cpuinfo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\imgarithmodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\imgarithmodule.spec

!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

InputPath=.\imgarithmodule.spec

".\imgarithmodule.h"	".\imgarithmodule_auto.c"	".\imgarithmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c imgarithmodule.spec 
	python ../../pluc.py h imgarithmodule.spec 
	python ../../pluc.py def imgarithmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

InputPath=.\imgarithmodule.spec

".\imgarithmodule.h"	".\imgarithmodule_auto.c"	".\imgarithmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c imgarithmodule.spec 
	python ../../pluc.py h imgarithmodule.spec 
	python ../../pluc.py def imgarithmodule.spec
<< 
	

!ENDIF 

SOURCE=.\imgarithmodule_x86.asm

!IF  "$(CFG)" == "imgarithmodule - Win32 Release"

OutDir=.\Release
InputPath=.\imgarithmodule_x86.asm
InputName=imgarithmodule_x86

"$(INTDIR)\imgarithmodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ELSEIF  "$(CFG)" == "imgarithmodule - Win32 Debug"

OutDir=.\Debug
InputPath=.\imgarithmodule_x86.asm
InputName=imgarithmodule_x86

"$(INTDIR)\imgarithmodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ENDIF 


!ENDIF 

