# Microsoft Developer Studio Generated NMAKE File, Based on flashmodule.dsp
!IF "$(CFG)" == ""
CFG=flashmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. flashmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "flashmodule - Win32 Release" && "$(CFG)" != "flashmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "flashmodule.mak" CFG="flashmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "flashmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flashmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "flashmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\flashmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\flashmodule.obj"
	-@erase "$(INTDIR)\flashmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\flashmodule.dll"
	-@erase "$(OUTDIR)\flashmodule.exp"
	-@erase "$(OUTDIR)\flashmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "flashmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flashmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\flashmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\flashmodule.pdb" /machine:I386 /def:".\flashmodule.def" /out:"$(OUTDIR)\flashmodule.dll" /implib:"$(OUTDIR)\flashmodule.lib" 
DEF_FILE= \
	".\flashmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\flashmodule.obj" \
	"$(INTDIR)\flashmodule_auto.obj"

"$(OUTDIR)\flashmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\flashmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\flashmodule.dll"
   copy .\Release\flashmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "flashmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\flashmodule_auto.c" ".\flashmodule.h" ".\flashmodule.def" "$(OUTDIR)\flashmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\flashmodule.obj"
	-@erase "$(INTDIR)\flashmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\flashmodule.dll"
	-@erase "$(OUTDIR)\flashmodule.exp"
	-@erase "$(OUTDIR)\flashmodule.ilk"
	-@erase "$(OUTDIR)\flashmodule.lib"
	-@erase "$(OUTDIR)\flashmodule.pdb"
	-@erase "flashmodule.def"
	-@erase "flashmodule.h"
	-@erase "flashmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "flashmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flashmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\flashmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\flashmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\flashmodule.def" /out:"$(OUTDIR)\flashmodule.dll" /implib:"$(OUTDIR)\flashmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\flashmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\flashmodule.obj" \
	"$(INTDIR)\flashmodule_auto.obj"

"$(OUTDIR)\flashmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\flashmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\flashmodule_auto.c" ".\flashmodule.h" ".\flashmodule.def" "$(OUTDIR)\flashmodule.dll"
   copy .\Debug\flashmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("flashmodule.dep")
!INCLUDE "flashmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "flashmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "flashmodule - Win32 Release" || "$(CFG)" == "flashmodule - Win32 Debug"
SOURCE=.\flashmodule.c

!IF  "$(CFG)" == "flashmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "flashmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flashmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\flashmodule.obj" : $(SOURCE) "$(INTDIR)" ".\flashmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "flashmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "flashmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flashmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\flashmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\flashmodule_auto.c

"$(INTDIR)\flashmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\flashmodule.h"


SOURCE=.\flashmodule.spec

!IF  "$(CFG)" == "flashmodule - Win32 Release"

InputPath=.\flashmodule.spec

".\flashmodule.h"	".\flashmodule_auto.c"	".\flashmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c flashmodule.spec 
	python ..\..\pluc.py h flashmodule.spec 
	python ..\..\pluc.py def flashmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "flashmodule - Win32 Debug"

InputPath=.\flashmodule.spec

".\flashmodule.h"	".\flashmodule_auto.c"	".\flashmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c flashmodule.spec 
	python ..\..\pluc.py h flashmodule.spec 
	python ..\..\pluc.py def flashmodule.spec
<< 
	

!ENDIF 


!ENDIF 

