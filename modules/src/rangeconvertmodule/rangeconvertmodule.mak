# Microsoft Developer Studio Generated NMAKE File, Based on rangeconvertmodule.dsp
!IF "$(CFG)" == ""
CFG=rangeconvertmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. rangeconvertmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "rangeconvertmodule - Win32 Release" && "$(CFG)" != "rangeconvertmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "rangeconvertmodule.mak" CFG="rangeconvertmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "rangeconvertmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rangeconvertmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "rangeconvertmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\rangeconvertmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\rangeconvertmodule.obj"
	-@erase "$(INTDIR)\rangeconvertmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\rangeconvertmodule.dll"
	-@erase "$(OUTDIR)\rangeconvertmodule.exp"
	-@erase "$(OUTDIR)\rangeconvertmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /D "_WINDOWS" /D "_USRDLL" /D "rangeconvertmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rangeconvertmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rangeconvertmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\rangeconvertmodule.pdb" /machine:I386 /def:".\rangeconvertmodule.def" /out:"$(OUTDIR)\rangeconvertmodule.dll" /implib:"$(OUTDIR)\rangeconvertmodule.lib" 
DEF_FILE= \
	".\rangeconvertmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\rangeconvertmodule.obj" \
	"$(INTDIR)\rangeconvertmodule_auto.obj"

"$(OUTDIR)\rangeconvertmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\rangeconvertmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\rangeconvertmodule.dll"
   copy .\Release\rangeconvertmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "rangeconvertmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\rangeconvertmodule_auto.c" ".\rangeconvertmodule.h" ".\rangeconvertmodule.def" "$(OUTDIR)\rangeconvertmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\rangeconvertmodule.obj"
	-@erase "$(INTDIR)\rangeconvertmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\rangeconvertmodule.dll"
	-@erase "$(OUTDIR)\rangeconvertmodule.exp"
	-@erase "$(OUTDIR)\rangeconvertmodule.ilk"
	-@erase "$(OUTDIR)\rangeconvertmodule.lib"
	-@erase "$(OUTDIR)\rangeconvertmodule.pdb"
	-@erase "rangeconvertmodule.def"
	-@erase "rangeconvertmodule.h"
	-@erase "rangeconvertmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_USRDLL" /D "rangeconvertmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\rangeconvertmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rangeconvertmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\rangeconvertmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\rangeconvertmodule.def" /out:"$(OUTDIR)\rangeconvertmodule.dll" /implib:"$(OUTDIR)\rangeconvertmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\rangeconvertmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\rangeconvertmodule.obj" \
	"$(INTDIR)\rangeconvertmodule_auto.obj"

"$(OUTDIR)\rangeconvertmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\rangeconvertmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\rangeconvertmodule_auto.c" ".\rangeconvertmodule.h" ".\rangeconvertmodule.def" "$(OUTDIR)\rangeconvertmodule.dll"
   copy .\Debug\rangeconvertmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("rangeconvertmodule.dep")
!INCLUDE "rangeconvertmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "rangeconvertmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "rangeconvertmodule - Win32 Release" || "$(CFG)" == "rangeconvertmodule - Win32 Debug"
SOURCE=.\rangeconvertmodule.c

!IF  "$(CFG)" == "rangeconvertmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /D "_WINDOWS" /D "_USRDLL" /D "rangeconvertmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\rangeconvertmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rangeconvertmodule.obj" : $(SOURCE) "$(INTDIR)" ".\rangeconvertmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "rangeconvertmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_USRDLL" /D "rangeconvertmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\rangeconvertmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\rangeconvertmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\rangeconvertmodule_auto.c

"$(INTDIR)\rangeconvertmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\rangeconvertmodule.h"


SOURCE=.\rangeconvertmodule.spec

!IF  "$(CFG)" == "rangeconvertmodule - Win32 Release"

InputPath=.\rangeconvertmodule.spec
InputName=rangeconvertmodule

".\rangeconvertmodule.h"	".\rangeconvertmodule_auto.c"	".\rangeconvertmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "rangeconvertmodule - Win32 Debug"

InputPath=.\rangeconvertmodule.spec
InputName=rangeconvertmodule

".\rangeconvertmodule.h"	".\rangeconvertmodule_auto.c"	".\rangeconvertmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

