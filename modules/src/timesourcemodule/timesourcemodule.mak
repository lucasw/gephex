# Microsoft Developer Studio Generated NMAKE File, Based on timesourcemodule.dsp
!IF "$(CFG)" == ""
CFG=timesourcemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. timesourcemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "timesourcemodule - Win32 Release" && "$(CFG)" != "timesourcemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "timesourcemodule.mak" CFG="timesourcemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "timesourcemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "timesourcemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "timesourcemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\timesourcemodule_auto.c" ".\timesourcemodule.h" ".\timesourcemodule.def" "$(OUTDIR)\timesourcemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\timesourcemodule.obj"
	-@erase "$(INTDIR)\timesourcemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\timesourcemodule.dll"
	-@erase "$(OUTDIR)\timesourcemodule.exp"
	-@erase "$(OUTDIR)\timesourcemodule.lib"
	-@erase "timesourcemodule.def"
	-@erase "timesourcemodule.h"
	-@erase "timesourcemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "timesourcemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\timesourcemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\timesourcemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\timesourcemodule.pdb" /machine:I386 /def:".\timesourcemodule.def" /out:"$(OUTDIR)\timesourcemodule.dll" /implib:"$(OUTDIR)\timesourcemodule.lib" 
DEF_FILE= \
	".\timesourcemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\timesourcemodule_auto.obj" \
	"$(INTDIR)\timesourcemodule.obj"

"$(OUTDIR)\timesourcemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\timesourcemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\timesourcemodule_auto.c" ".\timesourcemodule.h" ".\timesourcemodule.def" "$(OUTDIR)\timesourcemodule.dll"
   copy .\Release\timesourcemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "timesourcemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\timesourcemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\timesourcemodule.obj"
	-@erase "$(INTDIR)\timesourcemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\timesourcemodule.dll"
	-@erase "$(OUTDIR)\timesourcemodule.exp"
	-@erase "$(OUTDIR)\timesourcemodule.ilk"
	-@erase "$(OUTDIR)\timesourcemodule.lib"
	-@erase "$(OUTDIR)\timesourcemodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "timesourcemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\timesourcemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\timesourcemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\timesourcemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\timesourcemodule.def" /out:"$(OUTDIR)\timesourcemodule.dll" /implib:"$(OUTDIR)\timesourcemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\timesourcemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\timesourcemodule_auto.obj" \
	"$(INTDIR)\timesourcemodule.obj"

"$(OUTDIR)\timesourcemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\timesourcemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\timesourcemodule.dll"
   copy .\Debug\timesourcemodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("timesourcemodule.dep")
!INCLUDE "timesourcemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "timesourcemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "timesourcemodule - Win32 Release" || "$(CFG)" == "timesourcemodule - Win32 Debug"
SOURCE=.\timesourcemodule.cpp

"$(INTDIR)\timesourcemodule.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\timesourcemodule_auto.c

"$(INTDIR)\timesourcemodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\timesourcemodule.spec

!IF  "$(CFG)" == "timesourcemodule - Win32 Release"

InputPath=.\timesourcemodule.spec
InputName=timesourcemodule

".\timesourcemodule.h"	".\timesourcemodule_auto.c"	".\timesourcemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "timesourcemodule - Win32 Debug"

InputPath=.\timesourcemodule.spec
InputName=timesourcemodule

".\timesourcemodule.h"	".\timesourcemodule_auto.c"	".\timesourcemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

