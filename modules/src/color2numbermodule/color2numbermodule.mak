# Microsoft Developer Studio Generated NMAKE File, Based on color2numbermodule.dsp
!IF "$(CFG)" == ""
CFG=color2numbermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. color2numbermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "color2numbermodule - Win32 Release" && "$(CFG)" != "color2numbermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "color2numbermodule.mak" CFG="color2numbermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "color2numbermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "color2numbermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "color2numbermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\color2numbermodule.dll"

!ELSE 

ALL : "libscale - Win32 Release" "$(OUTDIR)\color2numbermodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\color2numbermodule.obj"
	-@erase "$(INTDIR)\color2numbermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\color2numbermodule.dll"
	-@erase "$(OUTDIR)\color2numbermodule.exp"
	-@erase "$(OUTDIR)\color2numbermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "color2numbermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\color2numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\color2numbermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\color2numbermodule.pdb" /machine:I386 /def:".\color2numbermodule.def" /out:"$(OUTDIR)\color2numbermodule.dll" /implib:"$(OUTDIR)\color2numbermodule.lib" 
DEF_FILE= \
	".\color2numbermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\color2numbermodule.obj" \
	"$(INTDIR)\color2numbermodule_auto.obj" \
	"..\libscale\Release\libscale.lib"

"$(OUTDIR)\color2numbermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\color2numbermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Release" "$(OUTDIR)\color2numbermodule.dll"
   copy .\Release\color2numbermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "color2numbermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\color2numbermodule_auto.c" ".\color2numbermodule.h" ".\color2numbermodule.def" "$(OUTDIR)\color2numbermodule.dll"

!ELSE 

ALL : "libscale - Win32 Debug" ".\color2numbermodule_auto.c" ".\color2numbermodule.h" ".\color2numbermodule.def" "$(OUTDIR)\color2numbermodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\color2numbermodule.obj"
	-@erase "$(INTDIR)\color2numbermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\color2numbermodule.dll"
	-@erase "$(OUTDIR)\color2numbermodule.exp"
	-@erase "$(OUTDIR)\color2numbermodule.ilk"
	-@erase "$(OUTDIR)\color2numbermodule.lib"
	-@erase "$(OUTDIR)\color2numbermodule.pdb"
	-@erase "color2numbermodule.def"
	-@erase "color2numbermodule.h"
	-@erase "color2numbermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "color2numbermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\color2numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\color2numbermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\color2numbermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\color2numbermodule.def" /out:"$(OUTDIR)\color2numbermodule.dll" /implib:"$(OUTDIR)\color2numbermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\color2numbermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\color2numbermodule.obj" \
	"$(INTDIR)\color2numbermodule_auto.obj" \
	"..\libscale\Debug\libscale.lib"

"$(OUTDIR)\color2numbermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\color2numbermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Debug" ".\color2numbermodule_auto.c" ".\color2numbermodule.h" ".\color2numbermodule.def" "$(OUTDIR)\color2numbermodule.dll"
   copy .\Debug\color2numbermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("color2numbermodule.dep")
!INCLUDE "color2numbermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "color2numbermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "color2numbermodule - Win32 Release" || "$(CFG)" == "color2numbermodule - Win32 Debug"
SOURCE=.\color2numbermodule.c

!IF  "$(CFG)" == "color2numbermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "color2numbermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\color2numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\color2numbermodule.obj" : $(SOURCE) "$(INTDIR)" ".\color2numbermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "color2numbermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "color2numbermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\color2numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\color2numbermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\color2numbermodule_auto.c

"$(INTDIR)\color2numbermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\color2numbermodule.h"


!IF  "$(CFG)" == "color2numbermodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\color2numbermodule"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\color2numbermodule"

!ELSEIF  "$(CFG)" == "color2numbermodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\color2numbermodule"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\color2numbermodule"

!ENDIF 

SOURCE=.\color2numbermodule.spec

!IF  "$(CFG)" == "color2numbermodule - Win32 Release"

InputPath=.\color2numbermodule.spec

".\color2numbermodule.h"	".\color2numbermodule_auto.c"	".\color2numbermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c color2numbermodule.spec 
	python ..\..\pluc.py h color2numbermodule.spec 
	python ..\..\pluc.py def color2numbermodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "color2numbermodule - Win32 Debug"

InputPath=.\color2numbermodule.spec

".\color2numbermodule.h"	".\color2numbermodule_auto.c"	".\color2numbermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c color2numbermodule.spec 
	python ..\..\pluc.py h color2numbermodule.spec 
	python ..\..\pluc.py def color2numbermodule.spec
<< 
	

!ENDIF 


!ENDIF 

