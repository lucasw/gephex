# Microsoft Developer Studio Generated NMAKE File, Based on signalgenmodule.dsp
!IF "$(CFG)" == ""
CFG=signalgenmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. signalgenmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "signalgenmodule - Win32 Release" && "$(CFG)" != "signalgenmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "signalgenmodule.mak" CFG="signalgenmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "signalgenmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "signalgenmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "signalgenmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\signalgenmodule_auto.c" ".\signalgenmodule.h" ".\signalgenmodule.def" "$(OUTDIR)\signalgenmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\signalgenmodule.obj"
	-@erase "$(INTDIR)\signalgenmodule_auto.obj"
	-@erase "$(INTDIR)\signals.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\signalgenmodule.dll"
	-@erase "$(OUTDIR)\signalgenmodule.exp"
	-@erase "signalgenmodule.def"
	-@erase "signalgenmodule.h"
	-@erase "signalgenmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "signalgenmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\signalgenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\signalgenmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\signalgenmodule.pdb" /machine:I386 /def:".\signalgenmodule.def" /out:"$(OUTDIR)\signalgenmodule.dll" /implib:"$(OUTDIR)\signalgenmodule.lib" 
DEF_FILE= \
	".\signalgenmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\signalgenmodule_auto.obj" \
	"$(INTDIR)\signalgenmodule.obj" \
	"$(INTDIR)\signals.obj"

"$(OUTDIR)\signalgenmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\signalgenmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\signalgenmodule_auto.c" ".\signalgenmodule.h" ".\signalgenmodule.def" "$(OUTDIR)\signalgenmodule.dll"
   copy .\Release\signalgenmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "signalgenmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\signalgenmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\signalgenmodule.obj"
	-@erase "$(INTDIR)\signalgenmodule_auto.obj"
	-@erase "$(INTDIR)\signals.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\signalgenmodule.dll"
	-@erase "$(OUTDIR)\signalgenmodule.exp"
	-@erase "$(OUTDIR)\signalgenmodule.ilk"
	-@erase "$(OUTDIR)\signalgenmodule.lib"
	-@erase "$(OUTDIR)\signalgenmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "signalgenmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\signalgenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\signalgenmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\signalgenmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\signalgenmodule.def" /out:"$(OUTDIR)\signalgenmodule.dll" /implib:"$(OUTDIR)\signalgenmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\signalgenmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\signalgenmodule_auto.obj" \
	"$(INTDIR)\signalgenmodule.obj" \
	"$(INTDIR)\signals.obj"

"$(OUTDIR)\signalgenmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\signalgenmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\signalgenmodule.dll"
   copy .\Debug\signalgenmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("signalgenmodule.dep")
!INCLUDE "signalgenmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "signalgenmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "signalgenmodule - Win32 Release" || "$(CFG)" == "signalgenmodule - Win32 Debug"
SOURCE=.\signalgenmodule.cpp

"$(INTDIR)\signalgenmodule.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\signalgenmodule_auto.c

"$(INTDIR)\signalgenmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\signals.cpp

"$(INTDIR)\signals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\signalgenmodule.spec

!IF  "$(CFG)" == "signalgenmodule - Win32 Release"

InputPath=.\signalgenmodule.spec

".\signalgenmodule.h"	".\signalgenmodule_auto.c"	".\signalgenmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c signalgenmodule.spec 
	python ../../pluc.py h signalgenmodule.spec 
	python ../../pluc.py def signalgenmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "signalgenmodule - Win32 Debug"

InputPath=.\signalgenmodule.spec

".\signalgenmodule.h"	".\signalgenmodule_auto.c"	".\signalgenmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c signalgenmodule.spec 
	python ../../pluc.py h signalgenmodule.spec 
	python ../../pluc.py def signalgenmodule.spec
<< 
	

!ENDIF 


!ENDIF 

