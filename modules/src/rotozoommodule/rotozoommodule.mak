# Microsoft Developer Studio Generated NMAKE File, Based on rotozoommodule.dsp
!IF "$(CFG)" == ""
CFG=rotozoommodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. rotozoommodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "rotozoommodule - Win32 Release" && "$(CFG)" != "rotozoommodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "rotozoommodule.mak" CFG="rotozoommodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "rotozoommodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rotozoommodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "rotozoommodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\rotozoommodule.dll"

!ELSE 

ALL : "libgeo - Win32 Release" "$(OUTDIR)\rotozoommodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgeo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\rotozoommodule.obj"
	-@erase "$(INTDIR)\rotozoommodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\rotozoommodule.dll"
	-@erase "$(OUTDIR)\rotozoommodule.exp"
	-@erase "$(OUTDIR)\rotozoommodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../types/src/positiontype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/libgeo" /D "_WINDOWS" /D "_USRDLL" /D "rotozoommodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rotozoommodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rotozoommodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\rotozoommodule.pdb" /machine:I386 /def:".\rotozoommodule.def" /out:"$(OUTDIR)\rotozoommodule.dll" /implib:"$(OUTDIR)\rotozoommodule.lib" 
DEF_FILE= \
	".\rotozoommodule.def"
LINK32_OBJS= \
	"$(INTDIR)\rotozoommodule.obj" \
	"$(INTDIR)\rotozoommodule_auto.obj" \
	"..\..\..\util\src\libgeo\Release\libgeo.lib"

"$(OUTDIR)\rotozoommodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\rotozoommodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgeo - Win32 Release" "$(OUTDIR)\rotozoommodule.dll"
   copy .\Release\rotozoommodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "rotozoommodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\rotozoommodule_auto.c" ".\rotozoommodule.h" ".\rotozoommodule.def" "..\..\..\config.h" "$(OUTDIR)\rotozoommodule.dll"

!ELSE 

ALL : "libgeo - Win32 Debug" ".\rotozoommodule_auto.c" ".\rotozoommodule.h" ".\rotozoommodule.def" "..\..\..\config.h" "$(OUTDIR)\rotozoommodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgeo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\rotozoommodule.obj"
	-@erase "$(INTDIR)\rotozoommodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\rotozoommodule.dll"
	-@erase "$(OUTDIR)\rotozoommodule.exp"
	-@erase "$(OUTDIR)\rotozoommodule.ilk"
	-@erase "$(OUTDIR)\rotozoommodule.lib"
	-@erase "$(OUTDIR)\rotozoommodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "rotozoommodule.def"
	-@erase "rotozoommodule.h"
	-@erase "rotozoommodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../types/src/positiontype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/libgeo" /D "_WINDOWS" /D "_USRDLL" /D "rotozoommodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rotozoommodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rotozoommodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\rotozoommodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\rotozoommodule.def" /out:"$(OUTDIR)\rotozoommodule.dll" /implib:"$(OUTDIR)\rotozoommodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\rotozoommodule.def"
LINK32_OBJS= \
	"$(INTDIR)\rotozoommodule.obj" \
	"$(INTDIR)\rotozoommodule_auto.obj" \
	"..\..\..\util\src\libgeo\Debug\libgeo.lib"

"$(OUTDIR)\rotozoommodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\rotozoommodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libgeo - Win32 Debug" ".\rotozoommodule_auto.c" ".\rotozoommodule.h" ".\rotozoommodule.def" "..\..\..\config.h" "$(OUTDIR)\rotozoommodule.dll"
   copy .\Debug\rotozoommodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("rotozoommodule.dep")
!INCLUDE "rotozoommodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "rotozoommodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "rotozoommodule - Win32 Release" || "$(CFG)" == "rotozoommodule - Win32 Debug"
SOURCE=.\rotozoommodule.c

!IF  "$(CFG)" == "rotozoommodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../types/src/positiontype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/libgeo" /D "_WINDOWS" /D "_USRDLL" /D "rotozoommodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rotozoommodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rotozoommodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\rotozoommodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "rotozoommodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../types/src/positiontype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/libgeo" /D "_WINDOWS" /D "_USRDLL" /D "rotozoommodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rotozoommodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\rotozoommodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\rotozoommodule_auto.c

"$(INTDIR)\rotozoommodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\rotozoommodule.h" "..\..\..\config.h"


!IF  "$(CFG)" == "rotozoommodule - Win32 Release"

"libgeo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\libgeo"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgeo.mak" CFG="libgeo - Win32 Release" 
   cd "..\..\..\modules\src\rotozoommodule"

"libgeo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\libgeo"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgeo.mak" CFG="libgeo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\rotozoommodule"

!ELSEIF  "$(CFG)" == "rotozoommodule - Win32 Debug"

"libgeo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\libgeo"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgeo.mak" CFG="libgeo - Win32 Debug" 
   cd "..\..\..\modules\src\rotozoommodule"

"libgeo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\libgeo"
   $(MAKE) /$(MAKEFLAGS) /F ".\libgeo.mak" CFG="libgeo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\rotozoommodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "rotozoommodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "rotozoommodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\rotozoommodule.spec

!IF  "$(CFG)" == "rotozoommodule - Win32 Release"

InputPath=.\rotozoommodule.spec

".\rotozoommodule.h"	".\rotozoommodule_auto.c"	".\rotozoommodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c rotozoommodule.spec 
	python ../../pluc.py h rotozoommodule.spec 
	python ../../pluc.py def rotozoommodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "rotozoommodule - Win32 Debug"

InputPath=.\rotozoommodule.spec

".\rotozoommodule.h"	".\rotozoommodule_auto.c"	".\rotozoommodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c rotozoommodule.spec 
	python ../../pluc.py h rotozoommodule.spec 
	python ../../pluc.py def rotozoommodule.spec
<< 
	

!ENDIF 


!ENDIF 

