# Microsoft Developer Studio Generated NMAKE File, Based on bwmodule.dsp
!IF "$(CFG)" == ""
CFG=bwmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. bwmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "bwmodule - Win32 Release" && "$(CFG)" != "bwmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "bwmodule.mak" CFG="bwmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "bwmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bwmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "bwmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\bwmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\bwmodule.obj"
	-@erase "$(INTDIR)\bwmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\bwmodule.dll"
	-@erase "$(OUTDIR)\bwmodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "bwmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\bwmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bwmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib glu32.lib opengl32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\bwmodule.pdb" /machine:I386 /def:".\bwmodule.def" /out:"$(OUTDIR)\bwmodule.dll" /implib:"$(OUTDIR)\bwmodule.lib" 
DEF_FILE= \
	".\bwmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\bwmodule.obj" \
	"$(INTDIR)\bwmodule_auto.obj"

"$(OUTDIR)\bwmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\bwmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\bwmodule.dll"
   copy .\Release\bwmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "bwmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\bwmodule_auto.c" ".\bwmodule.h" ".\bwmodule.def" "$(OUTDIR)\bwmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\bwmodule.obj"
	-@erase "$(INTDIR)\bwmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\bwmodule.dll"
	-@erase "$(OUTDIR)\bwmodule.exp"
	-@erase "$(OUTDIR)\bwmodule.ilk"
	-@erase "$(OUTDIR)\bwmodule.lib"
	-@erase "$(OUTDIR)\bwmodule.pdb"
	-@erase "bwmodule.def"
	-@erase "bwmodule.h"
	-@erase "bwmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "bwmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\bwmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bwmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\bwmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\bwmodule.def" /out:"$(OUTDIR)\bwmodule.dll" /implib:"$(OUTDIR)\bwmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\bwmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\bwmodule.obj" \
	"$(INTDIR)\bwmodule_auto.obj"

"$(OUTDIR)\bwmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\bwmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\bwmodule_auto.c" ".\bwmodule.h" ".\bwmodule.def" "$(OUTDIR)\bwmodule.dll"
   copy .\Debug\bwmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("bwmodule.dep")
!INCLUDE "bwmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "bwmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "bwmodule - Win32 Release" || "$(CFG)" == "bwmodule - Win32 Debug"
SOURCE=.\bwmodule.c

!IF  "$(CFG)" == "bwmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "bwmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\bwmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\bwmodule.obj" : $(SOURCE) "$(INTDIR)" ".\bwmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bwmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "bwmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\bwmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\bwmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\bwmodule_auto.c

"$(INTDIR)\bwmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\bwmodule.h"


SOURCE=.\bwmodule.spec

!IF  "$(CFG)" == "bwmodule - Win32 Release"

InputPath=.\bwmodule.spec

".\bwmodule.h"	".\bwmodule_auto.c"	".\bwmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c bwmodule.spec 
	python ../../pluc.py h bwmodule.spec 
	python ../../pluc.py def bwmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "bwmodule - Win32 Debug"

InputPath=.\bwmodule.spec

".\bwmodule.h"	".\bwmodule_auto.c"	".\bwmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c bwmodule.spec 
	python ../../pluc.py h bwmodule.spec 
	python ../../pluc.py def bwmodule.spec
<< 
	

!ENDIF 


!ENDIF 

