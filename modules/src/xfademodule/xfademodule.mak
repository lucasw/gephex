# Microsoft Developer Studio Generated NMAKE File, Based on xfademodule.dsp
!IF "$(CFG)" == ""
CFG=xfademodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. xfademodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "xfademodule - Win32 Release" && "$(CFG)" != "xfademodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "xfademodule.mak" CFG="xfademodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "xfademodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xfademodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "xfademodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\xfademodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Release" "$(OUTDIR)\xfademodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xfademodule.obj"
	-@erase "$(INTDIR)\xfademodule_auto.obj"
	-@erase "$(OUTDIR)\xfademodule.dll"
	-@erase "$(OUTDIR)\xfademodule.exp"
	-@erase "$(OUTDIR)\xfademodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "xfademodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\xfademodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xfademodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\xfademodule.pdb" /machine:I386 /def:".\xfademodule.def" /out:"$(OUTDIR)\xfademodule.dll" /implib:"$(OUTDIR)\xfademodule.lib" 
DEF_FILE= \
	".\xfademodule.def"
LINK32_OBJS= \
	"$(INTDIR)\xfademodule.obj" \
	"$(INTDIR)\xfademodule_auto.obj" \
	"$(INTDIR)\xfademodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Release\cpuinfo.lib"

"$(OUTDIR)\xfademodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\xfademodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Release" "$(OUTDIR)\xfademodule.dll"
   copy .\Release\xfademodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\xfademodule_auto.c" ".\xfademodule.h" ".\xfademodule.def" "..\..\..\config.h" "$(OUTDIR)\xfademodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Debug" ".\xfademodule_auto.c" ".\xfademodule.h" ".\xfademodule.def" "..\..\..\config.h" "$(OUTDIR)\xfademodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xfademodule.obj"
	-@erase "$(INTDIR)\xfademodule_auto.obj"
	-@erase "$(OUTDIR)\xfademodule.dll"
	-@erase "$(OUTDIR)\xfademodule.exp"
	-@erase "$(OUTDIR)\xfademodule.ilk"
	-@erase "$(OUTDIR)\xfademodule.lib"
	-@erase "$(OUTDIR)\xfademodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "xfademodule.def"
	-@erase "xfademodule.h"
	-@erase "xfademodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "xfademodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\xfademodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xfademodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\xfademodule.pdb" /debug /machine:I386 /nodefaultlib:"libcd" /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\xfademodule.def" /out:"$(OUTDIR)\xfademodule.dll" /implib:"$(OUTDIR)\xfademodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\xfademodule.def"
LINK32_OBJS= \
	"$(INTDIR)\xfademodule.obj" \
	"$(INTDIR)\xfademodule_auto.obj" \
	"$(INTDIR)\xfademodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Debug\cpuinfo.lib"

"$(OUTDIR)\xfademodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\xfademodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Debug" ".\xfademodule_auto.c" ".\xfademodule.h" ".\xfademodule.def" "..\..\..\config.h" "$(OUTDIR)\xfademodule.dll"
   copy .\Debug\xfademodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("xfademodule.dep")
!INCLUDE "xfademodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "xfademodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "xfademodule - Win32 Release" || "$(CFG)" == "xfademodule - Win32 Debug"
SOURCE=.\xfademodule.c

!IF  "$(CFG)" == "xfademodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "xfademodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\xfademodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\xfademodule.obj" : $(SOURCE) "$(INTDIR)" ".\xfademodule.h" "..\..\..\config.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "xfademodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\xfademodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\xfademodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\xfademodule_auto.c

"$(INTDIR)\xfademodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\xfademodule.h" "..\..\..\config.h"


!IF  "$(CFG)" == "xfademodule - Win32 Release"

"cpuinfo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" 
   cd "..\..\..\modules\src\xfademodule"

"cpuinfo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\xfademodule"

!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

"cpuinfo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" 
   cd "..\..\..\modules\src\xfademodule"

"cpuinfo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\xfademodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "xfademodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\xfademodule.spec

!IF  "$(CFG)" == "xfademodule - Win32 Release"

InputPath=.\xfademodule.spec

".\xfademodule.h"	".\xfademodule_auto.c"	".\xfademodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c xfademodule.spec 
	python ../../pluc.py h xfademodule.spec 
	python ../../pluc.py def xfademodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

InputPath=.\xfademodule.spec

".\xfademodule.h"	".\xfademodule_auto.c"	".\xfademodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c xfademodule.spec 
	python ../../pluc.py h xfademodule.spec 
	python ../../pluc.py def xfademodule.spec
<< 
	

!ENDIF 

SOURCE=.\xfademodule_x86.asm

!IF  "$(CFG)" == "xfademodule - Win32 Release"

OutDir=.\Release
InputPath=.\xfademodule_x86.asm
InputName=xfademodule_x86

"$(INTDIR)\xfademodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ELSEIF  "$(CFG)" == "xfademodule - Win32 Debug"

OutDir=.\Debug
InputPath=.\xfademodule_x86.asm
InputName=xfademodule_x86

"$(INTDIR)\xfademodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ENDIF 


!ENDIF 

