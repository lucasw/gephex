# Microsoft Developer Studio Generated NMAKE File, Based on chromakeymodule.dsp
!IF "$(CFG)" == ""
CFG=chromakeymodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. chromakeymodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "chromakeymodule - Win32 Release" && "$(CFG)" != "chromakeymodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "chromakeymodule.mak" CFG="chromakeymodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "chromakeymodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "chromakeymodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\chromakeymodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Release" "$(OUTDIR)\chromakeymodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\chromakeymodule.obj"
	-@erase "$(INTDIR)\chromakeymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chromakeymodule.dll"
	-@erase "$(OUTDIR)\chromakeymodule.exp"
	-@erase "$(OUTDIR)\chromakeymodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\chromakeymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chromakeymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\chromakeymodule.pdb" /machine:I386 /def:".\chromakeymodule.def" /out:"$(OUTDIR)\chromakeymodule.dll" /implib:"$(OUTDIR)\chromakeymodule.lib" 
DEF_FILE= \
	".\chromakeymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\chromakeymodule.obj" \
	"$(INTDIR)\chromakeymodule_auto.obj" \
	"$(INTDIR)\chromakeymodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Release\cpuinfo.lib"

"$(OUTDIR)\chromakeymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\chromakeymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Release" "$(OUTDIR)\chromakeymodule.dll"
   copy .\Release\chromakeymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\chromakeymodule_auto.c" ".\chromakeymodule.h" ".\chromakeymodule.def" "$(OUTDIR)\chromakeymodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Debug" ".\chromakeymodule_auto.c" ".\chromakeymodule.h" ".\chromakeymodule.def" "$(OUTDIR)\chromakeymodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\chromakeymodule.obj"
	-@erase "$(INTDIR)\chromakeymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\chromakeymodule.dll"
	-@erase "$(OUTDIR)\chromakeymodule.exp"
	-@erase "$(OUTDIR)\chromakeymodule.ilk"
	-@erase "$(OUTDIR)\chromakeymodule.lib"
	-@erase "$(OUTDIR)\chromakeymodule.pdb"
	-@erase "chromakeymodule.def"
	-@erase "chromakeymodule.h"
	-@erase "chromakeymodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\chromakeymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chromakeymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\chromakeymodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\chromakeymodule.def" /out:"$(OUTDIR)\chromakeymodule.dll" /implib:"$(OUTDIR)\chromakeymodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\chromakeymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\chromakeymodule.obj" \
	"$(INTDIR)\chromakeymodule_auto.obj" \
	"$(INTDIR)\chromakeymodule_x86.obj" \
	"..\..\..\util\src\cpuinfo\Debug\cpuinfo.lib"

"$(OUTDIR)\chromakeymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\chromakeymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Debug" ".\chromakeymodule_auto.c" ".\chromakeymodule.h" ".\chromakeymodule.def" "$(OUTDIR)\chromakeymodule.dll"
   copy .\Debug\chromakeymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("chromakeymodule.dep")
!INCLUDE "chromakeymodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "chromakeymodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "chromakeymodule - Win32 Release" || "$(CFG)" == "chromakeymodule - Win32 Debug"
SOURCE=.\chromakeymodule.c

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\chromakeymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\chromakeymodule.obj" : $(SOURCE) "$(INTDIR)" ".\chromakeymodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\chromakeymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\chromakeymodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\chromakeymodule_auto.c

"$(INTDIR)\chromakeymodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\chromakeymodule.h"


!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

"cpuinfo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" 
   cd "..\..\..\modules\src\chromakeymodule"

"cpuinfo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\chromakeymodule"

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

"cpuinfo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" 
   cd "..\..\..\modules\src\chromakeymodule"

"cpuinfo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\chromakeymodule"

!ENDIF 

SOURCE=.\chromakeymodule.spec

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

InputPath=.\chromakeymodule.spec
InputName=chromakeymodule

".\chromakeymodule.h"	".\chromakeymodule_auto.c"	".\chromakeymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

InputPath=.\chromakeymodule.spec
InputName=chromakeymodule

".\chromakeymodule.h"	".\chromakeymodule_auto.c"	".\chromakeymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 

SOURCE=.\chromakeymodule_x86.asm

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

OutDir=.\Release
InputPath=.\chromakeymodule_x86.asm
InputName=chromakeymodule_x86

"$(INTDIR)\chromakeymodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

OutDir=.\Debug
InputPath=.\chromakeymodule_x86.asm
InputName=chromakeymodule_x86

"$(INTDIR)\chromakeymodule_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ENDIF 


!ENDIF 

