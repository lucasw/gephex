# Microsoft Developer Studio Generated NMAKE File, Based on planemodule.dsp
!IF "$(CFG)" == ""
CFG=planemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. planemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "planemodule - Win32 Release" && "$(CFG)" != "planemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "planemodule.mak" CFG="planemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "planemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "planemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "planemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\planemodule.dll"

!ELSE 

ALL : "libgrid - Win32 Release" "$(OUTDIR)\planemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\planemodule.obj"
	-@erase "$(INTDIR)\planemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\planemodule.dll"
	-@erase "$(OUTDIR)\planemodule.exp"
	-@erase "$(OUTDIR)\planemodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "planemodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\planemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\planemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\planemodule.pdb" /machine:I386 /def:".\planemodule.def" /out:"$(OUTDIR)\planemodule.dll" /implib:"$(OUTDIR)\planemodule.lib" 
DEF_FILE= \
	".\planemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\planemodule.obj" \
	"$(INTDIR)\planemodule_auto.obj" \
	"..\libgrid\Release\libgrid.lib"

"$(OUTDIR)\planemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\planemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Release" "$(OUTDIR)\planemodule.dll"
   copy .\Release\planemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "planemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\planemodule_auto.c" ".\planemodule.h" ".\planemodule.def" "$(OUTDIR)\planemodule.dll"

!ELSE 

ALL : "libgrid - Win32 Debug" ".\planemodule_auto.c" ".\planemodule.h" ".\planemodule.def" "$(OUTDIR)\planemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\planemodule.obj"
	-@erase "$(INTDIR)\planemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\planemodule.dll"
	-@erase "$(OUTDIR)\planemodule.exp"
	-@erase "$(OUTDIR)\planemodule.ilk"
	-@erase "$(OUTDIR)\planemodule.lib"
	-@erase "$(OUTDIR)\planemodule.pdb"
	-@erase "planemodule.def"
	-@erase "planemodule.h"
	-@erase "planemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "planemodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\planemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\planemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\planemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\planemodule.def" /out:"$(OUTDIR)\planemodule.dll" /implib:"$(OUTDIR)\planemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\planemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\planemodule.obj" \
	"$(INTDIR)\planemodule_auto.obj" \
	"..\libgrid\Debug\libgrid.lib"

"$(OUTDIR)\planemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\planemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Debug" ".\planemodule_auto.c" ".\planemodule.h" ".\planemodule.def" "$(OUTDIR)\planemodule.dll"
   copy .\Debug\planemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("planemodule.dep")
!INCLUDE "planemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "planemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "planemodule - Win32 Release" || "$(CFG)" == "planemodule - Win32 Debug"
SOURCE=.\planemodule.c

!IF  "$(CFG)" == "planemodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "planemodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\planemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\planemodule.obj" : $(SOURCE) "$(INTDIR)" ".\planemodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "planemodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "planemodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\planemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\planemodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\planemodule_auto.c

"$(INTDIR)\planemodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\planemodule.h"


!IF  "$(CFG)" == "planemodule - Win32 Release"

"libgrid - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" 
   cd "..\planemodule"

"libgrid - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" RECURSE=1 CLEAN 
   cd "..\planemodule"

!ELSEIF  "$(CFG)" == "planemodule - Win32 Debug"

"libgrid - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" 
   cd "..\planemodule"

"libgrid - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\planemodule"

!ENDIF 

SOURCE=.\planemodule.spec

!IF  "$(CFG)" == "planemodule - Win32 Release"

InputPath=.\planemodule.spec

".\planemodule.h"	".\planemodule_auto.c"	".\planemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c planemodule.spec 
	python ..\..\pluc.py h planemodule.spec 
	python ..\..\pluc.py def planemodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "planemodule - Win32 Debug"

InputPath=.\planemodule.spec

".\planemodule.h"	".\planemodule_auto.c"	".\planemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c planemodule.spec 
	python ..\..\pluc.py h planemodule.spec 
	python ..\..\pluc.py def planemodule.spec
<< 
	

!ENDIF 


!ENDIF 

