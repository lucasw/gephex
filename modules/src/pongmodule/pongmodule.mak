# Microsoft Developer Studio Generated NMAKE File, Based on pongmodule.dsp
!IF "$(CFG)" == ""
CFG=pongmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. pongmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "pongmodule - Win32 Release" && "$(CFG)" != "pongmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "pongmodule.mak" CFG="pongmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "pongmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pongmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "pongmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\pongmodule_auto.c" ".\pongmodule.h" ".\pongmodule.def" "$(OUTDIR)\pongmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\pongmodule.obj"
	-@erase "$(INTDIR)\pongmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\pongmodule.dll"
	-@erase "$(OUTDIR)\pongmodule.exp"
	-@erase "$(OUTDIR)\pongmodule.lib"
	-@erase "pongmodule.def"
	-@erase "pongmodule.h"
	-@erase "pongmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "pongmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\pongmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pongmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\pongmodule.pdb" /machine:I386 /def:".\pongmodule.def" /out:"$(OUTDIR)\pongmodule.dll" /implib:"$(OUTDIR)\pongmodule.lib" 
DEF_FILE= \
	".\pongmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\pongmodule_auto.obj" \
	"$(INTDIR)\pongmodule.obj"

"$(OUTDIR)\pongmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\pongmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\pongmodule_auto.c" ".\pongmodule.h" ".\pongmodule.def" "$(OUTDIR)\pongmodule.dll"
   copy .\Release\pongmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "pongmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\pongmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\pongmodule.obj"
	-@erase "$(INTDIR)\pongmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\pongmodule.dll"
	-@erase "$(OUTDIR)\pongmodule.exp"
	-@erase "$(OUTDIR)\pongmodule.ilk"
	-@erase "$(OUTDIR)\pongmodule.lib"
	-@erase "$(OUTDIR)\pongmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "pongmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\pongmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pongmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\pongmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\pongmodule.def" /out:"$(OUTDIR)\pongmodule.dll" /implib:"$(OUTDIR)\pongmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\pongmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\pongmodule_auto.obj" \
	"$(INTDIR)\pongmodule.obj"

"$(OUTDIR)\pongmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\pongmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\pongmodule.dll"
   copy .\Debug\pongmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("pongmodule.dep")
!INCLUDE "pongmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "pongmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "pongmodule - Win32 Release" || "$(CFG)" == "pongmodule - Win32 Debug"
SOURCE=.\pongmodule.cpp

"$(INTDIR)\pongmodule.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pongmodule_auto.c

"$(INTDIR)\pongmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pongmodule.spec

!IF  "$(CFG)" == "pongmodule - Win32 Release"

InputPath=.\pongmodule.spec
InputName=pongmodule

".\pongmodule.h"	".\pongmodule_auto.c"	".\pongmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "pongmodule - Win32 Debug"

InputPath=.\pongmodule.spec
InputName=pongmodule

".\pongmodule.h"	".\pongmodule_auto.c"	".\pongmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

