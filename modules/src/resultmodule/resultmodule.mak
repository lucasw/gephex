# Microsoft Developer Studio Generated NMAKE File, Based on resultmodule.dsp
!IF "$(CFG)" == ""
CFG=resultmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. resultmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "resultmodule - Win32 Release" && "$(CFG)" != "resultmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "resultmodule.mak" CFG="resultmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "resultmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "resultmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "resultmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\resultmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\resultmodule.obj"
	-@erase "$(INTDIR)\resultmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\resultmodule.dll"
	-@erase "$(OUTDIR)\resultmodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "resultmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\resultmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\resultmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\resultmodule.pdb" /machine:I386 /def:".\resultmodule.def" /out:"$(OUTDIR)\resultmodule.dll" /implib:"$(OUTDIR)\resultmodule.lib" 
DEF_FILE= \
	".\resultmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\resultmodule.obj" \
	"$(INTDIR)\resultmodule_auto.obj"

"$(OUTDIR)\resultmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\resultmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\resultmodule.dll"
   copy .\Release\resultmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "resultmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\resultmodule_auto.c" ".\resultmodule.h" ".\resultmodule.def" "$(OUTDIR)\resultmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\resultmodule.obj"
	-@erase "$(INTDIR)\resultmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\resultmodule.dll"
	-@erase "$(OUTDIR)\resultmodule.exp"
	-@erase "$(OUTDIR)\resultmodule.ilk"
	-@erase "$(OUTDIR)\resultmodule.lib"
	-@erase "$(OUTDIR)\resultmodule.pdb"
	-@erase "resultmodule.def"
	-@erase "resultmodule.h"
	-@erase "resultmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "resultmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\resultmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\resultmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\resultmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\resultmodule.def" /out:"$(OUTDIR)\resultmodule.dll" /implib:"$(OUTDIR)\resultmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\resultmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\resultmodule.obj" \
	"$(INTDIR)\resultmodule_auto.obj"

"$(OUTDIR)\resultmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\resultmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\resultmodule_auto.c" ".\resultmodule.h" ".\resultmodule.def" "$(OUTDIR)\resultmodule.dll"
   copy .\Debug\resultmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("resultmodule.dep")
!INCLUDE "resultmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "resultmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "resultmodule - Win32 Release" || "$(CFG)" == "resultmodule - Win32 Debug"
SOURCE=.\resultmodule.c

!IF  "$(CFG)" == "resultmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "resultmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\resultmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\resultmodule.obj" : $(SOURCE) "$(INTDIR)" ".\resultmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "resultmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "resultmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\resultmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\resultmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\resultmodule_auto.c

"$(INTDIR)\resultmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\resultmodule.h"


SOURCE=.\resultmodule.spec

!IF  "$(CFG)" == "resultmodule - Win32 Release"

InputPath=.\resultmodule.spec

".\resultmodule.h"	".\resultmodule_auto.c"	".\resultmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c resultmodule.spec 
	python ../../pluc.py h resultmodule.spec 
	python ../../pluc.py def resultmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "resultmodule - Win32 Debug"

InputPath=.\resultmodule.spec

".\resultmodule.h"	".\resultmodule_auto.c"	".\resultmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c resultmodule.spec 
	python ../../pluc.py h resultmodule.spec 
	python ../../pluc.py def resultmodule.spec
<< 
	

!ENDIF 


!ENDIF 

