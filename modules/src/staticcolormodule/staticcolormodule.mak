# Microsoft Developer Studio Generated NMAKE File, Based on staticcolormodule.dsp
!IF "$(CFG)" == ""
CFG=staticcolormodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. staticcolormodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "staticcolormodule - Win32 Release" && "$(CFG)" != "staticcolormodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "staticcolormodule.mak" CFG="staticcolormodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "staticcolormodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "staticcolormodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\staticcolormodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Release" "$(OUTDIR)\staticcolormodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\staticcolormodule.obj"
	-@erase "$(INTDIR)\staticcolormodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\staticcolormodule.dll"
	-@erase "$(OUTDIR)\staticcolormodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "staticcolormodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\staticcolormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\staticcolormodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\staticcolormodule.pdb" /machine:I386 /def:".\staticcolormodule.def" /out:"$(OUTDIR)\staticcolormodule.dll" /implib:"$(OUTDIR)\staticcolormodule.lib" 
DEF_FILE= \
	".\staticcolormodule.def"
LINK32_OBJS= \
	"$(INTDIR)\staticcolormodule.obj" \
	"$(INTDIR)\staticcolormodule_auto.obj" \
	"$(INTDIR)\staticcolormodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Release\cpuinfo.lib"

"$(OUTDIR)\staticcolormodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\staticcolormodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Release" "$(OUTDIR)\staticcolormodule.dll"
   copy .\Release\staticcolormodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\staticcolormodule_auto.c" ".\staticcolormodule.h" ".\staticcolormodule.def" "..\..\..\config.h" "$(OUTDIR)\staticcolormodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Debug" ".\staticcolormodule_auto.c" ".\staticcolormodule.h" ".\staticcolormodule.def" "..\..\..\config.h" "$(OUTDIR)\staticcolormodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\staticcolormodule.obj"
	-@erase "$(INTDIR)\staticcolormodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\staticcolormodule.dll"
	-@erase "$(OUTDIR)\staticcolormodule.exp"
	-@erase "$(OUTDIR)\staticcolormodule.ilk"
	-@erase "$(OUTDIR)\staticcolormodule.lib"
	-@erase "$(OUTDIR)\staticcolormodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "staticcolormodule.def"
	-@erase "staticcolormodule.h"
	-@erase "staticcolormodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "staticcolormodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\staticcolormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\staticcolormodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\staticcolormodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\staticcolormodule.def" /out:"$(OUTDIR)\staticcolormodule.dll" /implib:"$(OUTDIR)\staticcolormodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\staticcolormodule.def"
LINK32_OBJS= \
	"$(INTDIR)\staticcolormodule.obj" \
	"$(INTDIR)\staticcolormodule_auto.obj" \
	"$(INTDIR)\staticcolormodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Debug\cpuinfo.lib"

"$(OUTDIR)\staticcolormodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\staticcolormodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Debug" ".\staticcolormodule_auto.c" ".\staticcolormodule.h" ".\staticcolormodule.def" "..\..\..\config.h" "$(OUTDIR)\staticcolormodule.dll"
   copy .\Debug\staticcolormodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("staticcolormodule.dep")
!INCLUDE "staticcolormodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "staticcolormodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "staticcolormodule - Win32 Release" || "$(CFG)" == "staticcolormodule - Win32 Debug"
SOURCE=.\staticcolormodule.c

!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "staticcolormodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\staticcolormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\staticcolormodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\staticcolormodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_USRDLL" /D "staticcolormodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\staticcolormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\staticcolormodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\staticcolormodule_auto.c

"$(INTDIR)\staticcolormodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\staticcolormodule.h" "..\..\..\config.h"


!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

"cpuinfo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" 
   cd "..\..\..\modules\src\staticcolormodule"

"cpuinfo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\staticcolormodule"

!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

"cpuinfo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" 
   cd "..\..\..\modules\src\staticcolormodule"

"cpuinfo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\staticcolormodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\staticcolormodule.spec

!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

InputPath=.\staticcolormodule.spec

".\staticcolormodule.h"	".\staticcolormodule_auto.c"	".\staticcolormodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c staticcolormodule.spec 
	python ../../pluc.py h staticcolormodule.spec 
	python ../../pluc.py def staticcolormodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

InputPath=.\staticcolormodule.spec

".\staticcolormodule.h"	".\staticcolormodule_auto.c"	".\staticcolormodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c staticcolormodule.spec 
	python ../../pluc.py h staticcolormodule.spec 
	python ../../pluc.py def staticcolormodule.spec
<< 
	

!ENDIF 

SOURCE=.\staticcolormodule_x86.asm

!IF  "$(CFG)" == "staticcolormodule - Win32 Release"

OutDir=.\Release
InputPath=.\staticcolormodule_x86.asm
InputName=staticcolormodule_x86

"$(INTDIR)\staticcolormodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ELSEIF  "$(CFG)" == "staticcolormodule - Win32 Debug"

OutDir=.\Debug
InputPath=.\staticcolormodule_x86.asm
InputName=staticcolormodule_x86

"$(INTDIR)\staticcolormodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ENDIF 


!ENDIF 

