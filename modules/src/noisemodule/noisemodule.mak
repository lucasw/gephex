# Microsoft Developer Studio Generated NMAKE File, Based on noisemodule.dsp
!IF "$(CFG)" == ""
CFG=noisemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. noisemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "noisemodule - Win32 Release" && "$(CFG)" != "noisemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "noisemodule.mak" CFG="noisemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "noisemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "noisemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "noisemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\noisemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\noisemodule.obj"
	-@erase "$(INTDIR)\noisemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\noisemodule.dll"
	-@erase "$(OUTDIR)\noisemodule.exp"
	-@erase "$(OUTDIR)\noisemodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "noisemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\noisemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\noisemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\noisemodule.pdb" /machine:I386 /def:".\noisemodule.def" /out:"$(OUTDIR)\noisemodule.dll" /implib:"$(OUTDIR)\noisemodule.lib" 
DEF_FILE= \
	".\noisemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\noisemodule.obj" \
	"$(INTDIR)\noisemodule_auto.obj"

"$(OUTDIR)\noisemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\noisemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\noisemodule.dll"
   copy .\Release\noisemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "noisemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\noisemodule_auto.c" ".\noisemodule.h" ".\noisemodule.def" "$(OUTDIR)\noisemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\noisemodule.obj"
	-@erase "$(INTDIR)\noisemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\noisemodule.dll"
	-@erase "$(OUTDIR)\noisemodule.exp"
	-@erase "$(OUTDIR)\noisemodule.ilk"
	-@erase "$(OUTDIR)\noisemodule.lib"
	-@erase "$(OUTDIR)\noisemodule.pdb"
	-@erase "noisemodule.def"
	-@erase "noisemodule.h"
	-@erase "noisemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "noisemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\noisemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\noisemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\noisemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\noisemodule.def" /out:"$(OUTDIR)\noisemodule.dll" /implib:"$(OUTDIR)\noisemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\noisemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\noisemodule.obj" \
	"$(INTDIR)\noisemodule_auto.obj"

"$(OUTDIR)\noisemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\noisemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\noisemodule_auto.c" ".\noisemodule.h" ".\noisemodule.def" "$(OUTDIR)\noisemodule.dll"
   copy .\Debug\noisemodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("noisemodule.dep")
!INCLUDE "noisemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "noisemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "noisemodule - Win32 Release" || "$(CFG)" == "noisemodule - Win32 Debug"
SOURCE=.\noisemodule.cpp

"$(INTDIR)\noisemodule.obj" : $(SOURCE) "$(INTDIR)" ".\noisemodule.h"


SOURCE=.\noisemodule_auto.c

"$(INTDIR)\noisemodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\noisemodule.spec

!IF  "$(CFG)" == "noisemodule - Win32 Release"

InputPath=.\noisemodule.spec
InputName=noisemodule

".\noisemodule.h"	".\noisemodule_auto.c"	".\noisemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "noisemodule - Win32 Debug"

InputPath=.\noisemodule.spec
InputName=noisemodule

".\noisemodule.h"	".\noisemodule_auto.c"	".\noisemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

