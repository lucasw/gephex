# Microsoft Developer Studio Generated NMAKE File, Based on font3Dmodule.dsp
!IF "$(CFG)" == ""
CFG=font3Dmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. font3Dmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "font3Dmodule - Win32 Release" && "$(CFG)" != "font3Dmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "font3Dmodule.mak" CFG="font3Dmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "font3Dmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "font3Dmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "font3Dmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\font3Dmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\font3Dmodule.obj"
	-@erase "$(INTDIR)\font3Dmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\font3Dmodule.dll"
	-@erase "$(OUTDIR)\font3Dmodule.exp"
	-@erase "$(OUTDIR)\font3Dmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/rgbtype" /I "../../../types/src/positiontype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../types/src/fonttype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "font3Dmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "VERBOSE_ENGINE" /Fp"$(INTDIR)\font3Dmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\font3Dmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\font3Dmodule.pdb" /machine:I386 /def:".\font3Dmodule.def" /out:"$(OUTDIR)\font3Dmodule.dll" /implib:"$(OUTDIR)\font3Dmodule.lib" 
DEF_FILE= \
	".\font3Dmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\font3Dmodule.obj" \
	"$(INTDIR)\font3Dmodule_auto.obj"

"$(OUTDIR)\font3Dmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\font3Dmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\font3Dmodule.dll"
   copy .\Release\font3Dmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "font3Dmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\font3Dmodule_auto.c" ".\font3Dmodule.h" ".\font3Dmodule.def" "$(OUTDIR)\font3Dmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\font3Dmodule.obj"
	-@erase "$(INTDIR)\font3Dmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\font3Dmodule.dll"
	-@erase "$(OUTDIR)\font3Dmodule.exp"
	-@erase "$(OUTDIR)\font3Dmodule.ilk"
	-@erase "$(OUTDIR)\font3Dmodule.lib"
	-@erase "$(OUTDIR)\font3Dmodule.pdb"
	-@erase "font3Dmodule.def"
	-@erase "font3Dmodule.h"
	-@erase "font3Dmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/positiontype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../types/src/fonttype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "font3Dmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\font3Dmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\font3Dmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\font3Dmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\font3Dmodule.def" /out:"$(OUTDIR)\font3Dmodule.dll" /implib:"$(OUTDIR)\font3Dmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\font3Dmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\font3Dmodule.obj" \
	"$(INTDIR)\font3Dmodule_auto.obj"

"$(OUTDIR)\font3Dmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\font3Dmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\font3Dmodule_auto.c" ".\font3Dmodule.h" ".\font3Dmodule.def" "$(OUTDIR)\font3Dmodule.dll"
   copy .\Debug\font3Dmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("font3Dmodule.dep")
!INCLUDE "font3Dmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "font3Dmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "font3Dmodule - Win32 Release" || "$(CFG)" == "font3Dmodule - Win32 Debug"
SOURCE=.\font3Dmodule.c

!IF  "$(CFG)" == "font3Dmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/rgbtype" /I "../../../types/src/positiontype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../types/src/fonttype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "font3Dmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "VERBOSE_ENGINE" /Fp"$(INTDIR)\font3Dmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\font3Dmodule.obj" : $(SOURCE) "$(INTDIR)" ".\font3Dmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "font3Dmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/positiontype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../types/src/fonttype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "font3Dmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\font3Dmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\font3Dmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\font3Dmodule_auto.c

"$(INTDIR)\font3Dmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\font3Dmodule.h"


SOURCE=.\font3Dmodule.spec

!IF  "$(CFG)" == "font3Dmodule - Win32 Release"

InputPath=.\font3Dmodule.spec

".\font3Dmodule.h"	".\font3Dmodule_auto.c"	".\font3Dmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c font3Dmodule.spec 
	python ../../pluc.py h font3Dmodule.spec 
	python ../../pluc.py def font3Dmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "font3Dmodule - Win32 Debug"

InputPath=.\font3Dmodule.spec

".\font3Dmodule.h"	".\font3Dmodule_auto.c"	".\font3Dmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c font3Dmodule.spec 
	python ../../pluc.py h font3Dmodule.spec 
	python ../../pluc.py def font3Dmodule.spec
<< 
	

!ENDIF 


!ENDIF 

