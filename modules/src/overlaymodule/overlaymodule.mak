# Microsoft Developer Studio Generated NMAKE File, Based on overlaymodule.dsp
!IF "$(CFG)" == ""
CFG=overlaymodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. overlaymodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "overlaymodule - Win32 Release" && "$(CFG)" != "overlaymodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "overlaymodule.mak" CFG="overlaymodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "overlaymodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "overlaymodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "overlaymodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\overlaymodule.dll"


CLEAN :
	-@erase "$(INTDIR)\overlaymodule.obj"
	-@erase "$(INTDIR)\overlaymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\overlaymodule.dll"
	-@erase "$(OUTDIR)\overlaymodule.exp"
	-@erase "$(OUTDIR)\overlaymodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "overlaymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\overlaymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\overlaymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\overlaymodule.pdb" /machine:I386 /def:".\overlaymodule.def" /out:"$(OUTDIR)\overlaymodule.dll" /implib:"$(OUTDIR)\overlaymodule.lib" 
DEF_FILE= \
	".\overlaymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\overlaymodule.obj" \
	"$(INTDIR)\overlaymodule_auto.obj"

"$(OUTDIR)\overlaymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\overlaymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\overlaymodule.dll"
   copy .\Release\overlaymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "overlaymodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\overlaymodule_auto.c" ".\overlaymodule.h" ".\overlaymodule.def" "$(OUTDIR)\overlaymodule.dll"


CLEAN :
	-@erase "$(INTDIR)\overlaymodule.obj"
	-@erase "$(INTDIR)\overlaymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\overlaymodule.dll"
	-@erase "$(OUTDIR)\overlaymodule.exp"
	-@erase "$(OUTDIR)\overlaymodule.ilk"
	-@erase "$(OUTDIR)\overlaymodule.lib"
	-@erase "$(OUTDIR)\overlaymodule.pdb"
	-@erase "overlaymodule.def"
	-@erase "overlaymodule.h"
	-@erase "overlaymodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "overlaymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\overlaymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\overlaymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\overlaymodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\overlaymodule.def" /out:"$(OUTDIR)\overlaymodule.dll" /implib:"$(OUTDIR)\overlaymodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\overlaymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\overlaymodule.obj" \
	"$(INTDIR)\overlaymodule_auto.obj"

"$(OUTDIR)\overlaymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\overlaymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\overlaymodule_auto.c" ".\overlaymodule.h" ".\overlaymodule.def" "$(OUTDIR)\overlaymodule.dll"
   copy .\Debug\overlaymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("overlaymodule.dep")
!INCLUDE "overlaymodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "overlaymodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "overlaymodule - Win32 Release" || "$(CFG)" == "overlaymodule - Win32 Debug"
SOURCE=.\overlaymodule.cpp

"$(INTDIR)\overlaymodule.obj" : $(SOURCE) "$(INTDIR)" ".\overlaymodule.h"


SOURCE=.\overlaymodule_auto.c

"$(INTDIR)\overlaymodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\overlaymodule.h"


SOURCE=.\overlaymodule.spec

!IF  "$(CFG)" == "overlaymodule - Win32 Release"

InputPath=.\overlaymodule.spec
InputName=overlaymodule

".\overlaymodule.h"	".\overlaymodule_auto.c"	".\overlaymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "overlaymodule - Win32 Debug"

InputPath=.\overlaymodule.spec
InputName=overlaymodule

".\overlaymodule.h"	".\overlaymodule_auto.c"	".\overlaymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

