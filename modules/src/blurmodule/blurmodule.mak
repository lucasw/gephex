# Microsoft Developer Studio Generated NMAKE File, Based on blurmodule.dsp
!IF "$(CFG)" == ""
CFG=blurmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. blurmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "blurmodule - Win32 Release" && "$(CFG)" != "blurmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "blurmodule.mak" CFG="blurmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "blurmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "blurmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "blurmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\blurmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\blurmodule.obj"
	-@erase "$(INTDIR)\blurmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\blurmodule.dll"
	-@erase "$(OUTDIR)\blurmodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "blurmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\blurmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\blurmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\blurmodule.pdb" /machine:I386 /def:".\blurmodule.def" /out:"$(OUTDIR)\blurmodule.dll" /implib:"$(OUTDIR)\blurmodule.lib" 
DEF_FILE= \
	".\blurmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\blurmodule.obj" \
	"$(INTDIR)\blurmodule_auto.obj"

"$(OUTDIR)\blurmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\blurmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\blurmodule.dll"
   copy .\Release\blurmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "blurmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\blurmodule_auto.c" ".\blurmodule.h" ".\blurmodule.def" "$(OUTDIR)\blurmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\blurmodule.obj"
	-@erase "$(INTDIR)\blurmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\blurmodule.dll"
	-@erase "$(OUTDIR)\blurmodule.exp"
	-@erase "$(OUTDIR)\blurmodule.ilk"
	-@erase "$(OUTDIR)\blurmodule.lib"
	-@erase "$(OUTDIR)\blurmodule.pdb"
	-@erase "blurmodule.def"
	-@erase "blurmodule.h"
	-@erase "blurmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "blurmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\blurmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\blurmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\blurmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\blurmodule.def" /out:"$(OUTDIR)\blurmodule.dll" /implib:"$(OUTDIR)\blurmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\blurmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\blurmodule.obj" \
	"$(INTDIR)\blurmodule_auto.obj"

"$(OUTDIR)\blurmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\blurmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\blurmodule_auto.c" ".\blurmodule.h" ".\blurmodule.def" "$(OUTDIR)\blurmodule.dll"
   copy .\Debug\blurmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("blurmodule.dep")
!INCLUDE "blurmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "blurmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "blurmodule - Win32 Release" || "$(CFG)" == "blurmodule - Win32 Debug"
SOURCE=.\blurmodule.c

!IF  "$(CFG)" == "blurmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "blurmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\blurmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\blurmodule.obj" : $(SOURCE) "$(INTDIR)" ".\blurmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "blurmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "blurmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\blurmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\blurmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\blurmodule_auto.c

"$(INTDIR)\blurmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\blurmodule.h"


SOURCE=.\blurmodule.spec

!IF  "$(CFG)" == "blurmodule - Win32 Release"

InputPath=.\blurmodule.spec

".\blurmodule.h"	".\blurmodule_auto.c"	".\blurmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c blurmodule.spec 
	python ../../pluc.py h blurmodule.spec 
	python ../../pluc.py def blurmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "blurmodule - Win32 Debug"

InputPath=.\blurmodule.spec

".\blurmodule.h"	".\blurmodule_auto.c"	".\blurmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c blurmodule.spec 
	python ../../pluc.py h blurmodule.spec 
	python ../../pluc.py def blurmodule.spec
<< 
	

!ENDIF 


!ENDIF 

