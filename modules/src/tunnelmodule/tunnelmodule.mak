# Microsoft Developer Studio Generated NMAKE File, Based on tunnelmodule.dsp
!IF "$(CFG)" == ""
CFG=tunnelmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. tunnelmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "tunnelmodule - Win32 Release" && "$(CFG)" != "tunnelmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "tunnelmodule.mak" CFG="tunnelmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "tunnelmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tunnelmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "tunnelmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"

!ELSE 

ALL : "libgrid - Win32 Release" ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\tunnelmodule.obj"
	-@erase "$(INTDIR)\tunnelmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\tunnelmodule.dll"
	-@erase "$(OUTDIR)\tunnelmodule.exp"
	-@erase "tunnelmodule.def"
	-@erase "tunnelmodule.h"
	-@erase "tunnelmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/positiontype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "tunnelmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\tunnelmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tunnelmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\tunnelmodule.pdb" /machine:I386 /def:".\tunnelmodule.def" /out:"$(OUTDIR)\tunnelmodule.dll" /implib:"$(OUTDIR)\tunnelmodule.lib" 
DEF_FILE= \
	".\tunnelmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\tunnelmodule.obj" \
	"$(INTDIR)\tunnelmodule_auto.obj" \
	"..\libgrid\Release\libgrid.lib"

"$(OUTDIR)\tunnelmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\tunnelmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Release" ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"
   copy .\Release\tunnelmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "tunnelmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"

!ELSE 

ALL : "libgrid - Win32 Debug" ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgrid - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\tunnelmodule.obj"
	-@erase "$(INTDIR)\tunnelmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\tunnelmodule.dll"
	-@erase "$(OUTDIR)\tunnelmodule.exp"
	-@erase "$(OUTDIR)\tunnelmodule.ilk"
	-@erase "$(OUTDIR)\tunnelmodule.lib"
	-@erase "$(OUTDIR)\tunnelmodule.pdb"
	-@erase "tunnelmodule.def"
	-@erase "tunnelmodule.h"
	-@erase "tunnelmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/positiontype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "tunnelmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\tunnelmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tunnelmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\tunnelmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\tunnelmodule.def" /out:"$(OUTDIR)\tunnelmodule.dll" /implib:"$(OUTDIR)\tunnelmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\tunnelmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\tunnelmodule.obj" \
	"$(INTDIR)\tunnelmodule_auto.obj" \
	"..\libgrid\Debug\libgrid.lib"

"$(OUTDIR)\tunnelmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\tunnelmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgrid - Win32 Debug" ".\tunnelmodule_auto.c" ".\tunnelmodule.h" ".\tunnelmodule.def" "$(OUTDIR)\tunnelmodule.dll"
   copy .\Debug\tunnelmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("tunnelmodule.dep")
!INCLUDE "tunnelmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "tunnelmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tunnelmodule - Win32 Release" || "$(CFG)" == "tunnelmodule - Win32 Debug"
SOURCE=.\tunnelmodule.c

!IF  "$(CFG)" == "tunnelmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/positiontype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "tunnelmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\tunnelmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\tunnelmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tunnelmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/positiontype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "tunnelmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\tunnelmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\tunnelmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tunnelmodule_auto.c

"$(INTDIR)\tunnelmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "tunnelmodule - Win32 Release"

"libgrid - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" 
   cd "..\tunnelmodule"

"libgrid - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Release" RECURSE=1 CLEAN 
   cd "..\tunnelmodule"

!ELSEIF  "$(CFG)" == "tunnelmodule - Win32 Debug"

"libgrid - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" 
   cd "..\tunnelmodule"

"libgrid - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libgrid"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgrid.mak" CFG="libgrid - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\tunnelmodule"

!ENDIF 

SOURCE=.\tunnelmodule.spec

!IF  "$(CFG)" == "tunnelmodule - Win32 Release"

InputPath=.\tunnelmodule.spec

".\tunnelmodule.h"	".\tunnelmodule_auto.c"	".\tunnelmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c tunnelmodule.spec 
	python ../../pluc.py h tunnelmodule.spec 
	python ../../pluc.py def tunnelmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "tunnelmodule - Win32 Debug"

InputPath=.\tunnelmodule.spec

".\tunnelmodule.h"	".\tunnelmodule_auto.c"	".\tunnelmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c tunnelmodule.spec 
	python ../../pluc.py h tunnelmodule.spec 
	python ../../pluc.py def tunnelmodule.spec
<< 
	

!ENDIF 


!ENDIF 

