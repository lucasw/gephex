# Microsoft Developer Studio Generated NMAKE File, Based on plasmamodule.dsp
!IF "$(CFG)" == ""
CFG=plasmamodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. plasmamodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "plasmamodule - Win32 Release" && "$(CFG)" != "plasmamodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "plasmamodule.mak" CFG="plasmamodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "plasmamodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "plasmamodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "plasmamodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\plasmamodule.dll"

!ELSE 

ALL : "libgrid - Win32 Release" "$(OUTDIR)\plasmamodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\plasmamodule.obj"
	-@erase "$(INTDIR)\plasmamodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\plasmamodule.dll"
	-@erase "$(OUTDIR)\plasmamodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "plasmamodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\plasmamodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\plasmamodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\plasmamodule.pdb" /machine:I386 /def:".\plasmamodule.def" /out:"$(OUTDIR)\plasmamodule.dll" /implib:"$(OUTDIR)\plasmamodule.lib" 
DEF_FILE= \
	".\plasmamodule.def"
LINK32_OBJS= \
	"$(INTDIR)\plasmamodule.obj" \
	"$(INTDIR)\plasmamodule_auto.obj" \
	"..\libgrid\Release\libgrid.lib"

"$(OUTDIR)\plasmamodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\plasmamodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Release" "$(OUTDIR)\plasmamodule.dll"
   copy .\Release\plasmamodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "plasmamodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\plasmamodule_auto.c" ".\plasmamodule.h" ".\plasmamodule.def" "$(OUTDIR)\plasmamodule.dll"

!ELSE 

ALL : "libgrid - Win32 Debug" ".\plasmamodule_auto.c" ".\plasmamodule.h" ".\plasmamodule.def" "$(OUTDIR)\plasmamodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\plasmamodule.obj"
	-@erase "$(INTDIR)\plasmamodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\plasmamodule.dll"
	-@erase "$(OUTDIR)\plasmamodule.exp"
	-@erase "$(OUTDIR)\plasmamodule.ilk"
	-@erase "$(OUTDIR)\plasmamodule.lib"
	-@erase "$(OUTDIR)\plasmamodule.pdb"
	-@erase "plasmamodule.def"
	-@erase "plasmamodule.h"
	-@erase "plasmamodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "plasmamodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\plasmamodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\plasmamodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\plasmamodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\plasmamodule.def" /out:"$(OUTDIR)\plasmamodule.dll" /implib:"$(OUTDIR)\plasmamodule.lib" /pdbtype:sept /libpath:"../libgrid" 
DEF_FILE= \
	".\plasmamodule.def"
LINK32_OBJS= \
	"$(INTDIR)\plasmamodule.obj" \
	"$(INTDIR)\plasmamodule_auto.obj" \
	"..\libgrid\Debug\libgrid.lib"

"$(OUTDIR)\plasmamodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\plasmamodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Debug" ".\plasmamodule_auto.c" ".\plasmamodule.h" ".\plasmamodule.def" "$(OUTDIR)\plasmamodule.dll"
   copy .\Debug\plasmamodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("plasmamodule.dep")
!INCLUDE "plasmamodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "plasmamodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "plasmamodule - Win32 Release" || "$(CFG)" == "plasmamodule - Win32 Debug"
SOURCE=.\plasmamodule.c

!IF  "$(CFG)" == "plasmamodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "plasmamodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\plasmamodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\plasmamodule.obj" : $(SOURCE) "$(INTDIR)" ".\plasmamodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "plasmamodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "plasmamodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\plasmamodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\plasmamodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\plasmamodule_auto.c

"$(INTDIR)\plasmamodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\plasmamodule.h"


!IF  "$(CFG)" == "plasmamodule - Win32 Release"

"libgrid - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" 
   cd "..\plasmamodule"

"libgrid - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" RECURSE=1 CLEAN 
   cd "..\plasmamodule"

!ELSEIF  "$(CFG)" == "plasmamodule - Win32 Debug"

"libgrid - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" 
   cd "..\plasmamodule"

"libgrid - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\plasmamodule"

!ENDIF 

SOURCE=.\plasmamodule.spec

!IF  "$(CFG)" == "plasmamodule - Win32 Release"

InputPath=.\plasmamodule.spec

".\plasmamodule.h"	".\plasmamodule_auto.c"	".\plasmamodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c plasmamodule.spec 
	python ../../pluc.py h plasmamodule.spec 
	python ../../pluc.py def plasmamodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "plasmamodule - Win32 Debug"

InputPath=.\plasmamodule.spec

".\plasmamodule.h"	".\plasmamodule_auto.c"	".\plasmamodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c plasmamodule.spec 
	python ../../pluc.py h plasmamodule.spec 
	python ../../pluc.py def plasmamodule.spec
<< 
	

!ENDIF 


!ENDIF 

