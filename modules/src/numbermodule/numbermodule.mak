# Microsoft Developer Studio Generated NMAKE File, Based on numbermodule.dsp
!IF "$(CFG)" == ""
CFG=numbermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. numbermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "numbermodule - Win32 Release" && "$(CFG)" != "numbermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "numbermodule.mak" CFG="numbermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "numbermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "numbermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "numbermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\numbermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numbermodule.obj"
	-@erase "$(INTDIR)\numbermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\numbermodule.dll"
	-@erase "$(OUTDIR)\numbermodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "numbermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numbermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\numbermodule.pdb" /machine:I386 /def:".\numbermodule.def" /out:"$(OUTDIR)\numbermodule.dll" /implib:"$(OUTDIR)\numbermodule.lib" 
DEF_FILE= \
	".\numbermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numbermodule.obj" \
	"$(INTDIR)\numbermodule_auto.obj"

"$(OUTDIR)\numbermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\numbermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\numbermodule.dll"
   copy .\Release\numbermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "numbermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\numbermodule_auto.c" ".\numbermodule.h" ".\numbermodule.def" "$(OUTDIR)\numbermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numbermodule.obj"
	-@erase "$(INTDIR)\numbermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\numbermodule.dll"
	-@erase "$(OUTDIR)\numbermodule.exp"
	-@erase "$(OUTDIR)\numbermodule.ilk"
	-@erase "$(OUTDIR)\numbermodule.lib"
	-@erase "$(OUTDIR)\numbermodule.pdb"
	-@erase "numbermodule.def"
	-@erase "numbermodule.h"
	-@erase "numbermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "numbermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numbermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\numbermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\numbermodule.def" /out:"$(OUTDIR)\numbermodule.dll" /implib:"$(OUTDIR)\numbermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\numbermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numbermodule.obj" \
	"$(INTDIR)\numbermodule_auto.obj"

"$(OUTDIR)\numbermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\numbermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\numbermodule_auto.c" ".\numbermodule.h" ".\numbermodule.def" "$(OUTDIR)\numbermodule.dll"
   copy .\Debug\numbermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("numbermodule.dep")
!INCLUDE "numbermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "numbermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "numbermodule - Win32 Release" || "$(CFG)" == "numbermodule - Win32 Debug"
SOURCE=.\numbermodule.c

!IF  "$(CFG)" == "numbermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "numbermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\numbermodule.obj" : $(SOURCE) "$(INTDIR)" ".\numbermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "numbermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "numbermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numbermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\numbermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\numbermodule_auto.c

"$(INTDIR)\numbermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\numbermodule.h"


SOURCE=.\numbermodule.spec

!IF  "$(CFG)" == "numbermodule - Win32 Release"

InputPath=.\numbermodule.spec

".\numbermodule.h"	".\numbermodule_auto.c"	".\numbermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c numbermodule.spec 
	python ../../pluc.py h numbermodule.spec 
	python ../../pluc.py def numbermodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "numbermodule - Win32 Debug"

InputPath=.\numbermodule.spec

".\numbermodule.h"	".\numbermodule_auto.c"	".\numbermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c numbermodule.spec 
	python ../../pluc.py h numbermodule.spec 
	python ../../pluc.py def numbermodule.spec
<< 
	

!ENDIF 


!ENDIF 

