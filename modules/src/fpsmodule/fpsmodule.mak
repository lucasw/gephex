# Microsoft Developer Studio Generated NMAKE File, Based on fpsmodule.dsp
!IF "$(CFG)" == ""
CFG=fpsmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. fpsmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "fpsmodule - Win32 Release" && "$(CFG)" != "fpsmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "fpsmodule.mak" CFG="fpsmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "fpsmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fpsmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "fpsmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\fpsmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\fpsmodule.obj"
	-@erase "$(INTDIR)\fpsmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fpsmodule.dll"
	-@erase "$(OUTDIR)\fpsmodule.exp"
	-@erase "$(OUTDIR)\fpsmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../.." /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "fpsmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\fpsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fpsmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\fpsmodule.pdb" /machine:I386 /def:".\fpsmodule.def" /out:"$(OUTDIR)\fpsmodule.dll" /implib:"$(OUTDIR)\fpsmodule.lib" 
DEF_FILE= \
	".\fpsmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\fpsmodule.obj" \
	"$(INTDIR)\fpsmodule_auto.obj"

"$(OUTDIR)\fpsmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\fpsmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\fpsmodule.dll"
   copy .\Release\fpsmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "fpsmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\fpsmodule_auto.c" ".\fpsmodule.h" ".\fpsmodule.def" "$(OUTDIR)\fpsmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\fpsmodule.obj"
	-@erase "$(INTDIR)\fpsmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fpsmodule.dll"
	-@erase "$(OUTDIR)\fpsmodule.exp"
	-@erase "$(OUTDIR)\fpsmodule.ilk"
	-@erase "$(OUTDIR)\fpsmodule.lib"
	-@erase "$(OUTDIR)\fpsmodule.pdb"
	-@erase "fpsmodule.def"
	-@erase "fpsmodule.h"
	-@erase "fpsmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "fpsmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\fpsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fpsmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\fpsmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\fpsmodule.def" /out:"$(OUTDIR)\fpsmodule.dll" /implib:"$(OUTDIR)\fpsmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\fpsmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\fpsmodule.obj" \
	"$(INTDIR)\fpsmodule_auto.obj"

"$(OUTDIR)\fpsmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\fpsmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\fpsmodule_auto.c" ".\fpsmodule.h" ".\fpsmodule.def" "$(OUTDIR)\fpsmodule.dll"
   copy .\Debug\fpsmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("fpsmodule.dep")
!INCLUDE "fpsmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "fpsmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "fpsmodule - Win32 Release" || "$(CFG)" == "fpsmodule - Win32 Debug"
SOURCE=.\fpsmodule.c

!IF  "$(CFG)" == "fpsmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../.." /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "fpsmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\fpsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fpsmodule.obj" : $(SOURCE) "$(INTDIR)" ".\fpsmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fpsmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "fpsmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\fpsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\fpsmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\fpsmodule_auto.c

"$(INTDIR)\fpsmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\fpsmodule.h"


SOURCE=.\fpsmodule.spec

!IF  "$(CFG)" == "fpsmodule - Win32 Release"

InputPath=.\fpsmodule.spec
InputName=fpsmodule

".\fpsmodule.h"	".\fpsmodule_auto.c"	".\fpsmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "fpsmodule - Win32 Debug"

InputPath=.\fpsmodule.spec
InputName=fpsmodule

".\fpsmodule.h"	".\fpsmodule_auto.c"	".\fpsmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

