# Microsoft Developer Studio Generated NMAKE File, Based on jumpmodule.dsp
!IF "$(CFG)" == ""
CFG=jumpmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. jumpmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "jumpmodule - Win32 Release" && "$(CFG)" != "jumpmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "jumpmodule.mak" CFG="jumpmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "jumpmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "jumpmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "jumpmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\jumpmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\jumpmodule.obj"
	-@erase "$(INTDIR)\jumpmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\jumpmodule.dll"
	-@erase "$(OUTDIR)\jumpmodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "..\..\..\util\include" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "jumpmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\jumpmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\jumpmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\jumpmodule.pdb" /machine:I386 /def:".\jumpmodule.def" /out:"$(OUTDIR)\jumpmodule.dll" /implib:"$(OUTDIR)\jumpmodule.lib" 
DEF_FILE= \
	".\jumpmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\jumpmodule.obj" \
	"$(INTDIR)\jumpmodule_auto.obj"

"$(OUTDIR)\jumpmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\jumpmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\jumpmodule.dll"
   copy .\Release\jumpmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "jumpmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\jumpmodule_auto.c" ".\jumpmodule.h" ".\jumpmodule.def" "$(OUTDIR)\jumpmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\jumpmodule.obj"
	-@erase "$(INTDIR)\jumpmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\jumpmodule.dll"
	-@erase "$(OUTDIR)\jumpmodule.exp"
	-@erase "$(OUTDIR)\jumpmodule.ilk"
	-@erase "$(OUTDIR)\jumpmodule.lib"
	-@erase "$(OUTDIR)\jumpmodule.pdb"
	-@erase "jumpmodule.def"
	-@erase "jumpmodule.h"
	-@erase "jumpmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../util/include" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /D "_WINDOWS" /D "_USRDLL" /D "jumpmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\jumpmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\jumpmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\jumpmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\jumpmodule.def" /out:"$(OUTDIR)\jumpmodule.dll" /implib:"$(OUTDIR)\jumpmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\jumpmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\jumpmodule.obj" \
	"$(INTDIR)\jumpmodule_auto.obj"

"$(OUTDIR)\jumpmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\jumpmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\jumpmodule_auto.c" ".\jumpmodule.h" ".\jumpmodule.def" "$(OUTDIR)\jumpmodule.dll"
   copy .\Debug\jumpmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("jumpmodule.dep")
!INCLUDE "jumpmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "jumpmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "jumpmodule - Win32 Release" || "$(CFG)" == "jumpmodule - Win32 Debug"
SOURCE=.\jumpmodule.c

!IF  "$(CFG)" == "jumpmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "..\..\..\util\include" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "jumpmodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\jumpmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\jumpmodule.obj" : $(SOURCE) "$(INTDIR)" ".\jumpmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "jumpmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../util/include" /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /D "_WINDOWS" /D "_USRDLL" /D "jumpmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\jumpmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\jumpmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\jumpmodule_auto.c

"$(INTDIR)\jumpmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\jumpmodule.h"


SOURCE=.\jumpmodule.spec

!IF  "$(CFG)" == "jumpmodule - Win32 Release"

InputPath=.\jumpmodule.spec

".\jumpmodule.h"	".\jumpmodule_auto.c"	".\jumpmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c jumpmodule.spec 
	python ../../pluc.py h jumpmodule.spec 
	python ../../pluc.py def jumpmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "jumpmodule - Win32 Debug"

InputPath=.\jumpmodule.spec

".\jumpmodule.h"	".\jumpmodule_auto.c"	".\jumpmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c jumpmodule.spec 
	python ../../pluc.py h jumpmodule.spec 
	python ../../pluc.py def jumpmodule.spec
<< 
	

!ENDIF 


!ENDIF 

