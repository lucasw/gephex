# Microsoft Developer Studio Generated NMAKE File, Based on flipflopmodule.dsp
!IF "$(CFG)" == ""
CFG=flipflopmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. flipflopmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "flipflopmodule - Win32 Release" && "$(CFG)" != "flipflopmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "flipflopmodule.mak" CFG="flipflopmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "flipflopmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flipflopmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "flipflopmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\flipflopmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\flipflopmodule.obj"
	-@erase "$(INTDIR)\flipflopmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\flipflopmodule.dll"
	-@erase "$(OUTDIR)\flipflopmodule.exp"
	-@erase "$(OUTDIR)\flipflopmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /D "_WINDOWS" /D "_USRDLL" /D "flipflopmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flipflopmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\flipflopmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\flipflopmodule.pdb" /machine:I386 /def:".\flipflopmodule.def" /out:"$(OUTDIR)\flipflopmodule.dll" /implib:"$(OUTDIR)\flipflopmodule.lib" 
DEF_FILE= \
	".\flipflopmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\flipflopmodule.obj" \
	"$(INTDIR)\flipflopmodule_auto.obj"

"$(OUTDIR)\flipflopmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\flipflopmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\flipflopmodule.dll"
   copy .\Release\flipflopmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "flipflopmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\flipflopmodule_auto.c" ".\flipflopmodule.h" ".\flipflopmodule.def" "$(OUTDIR)\flipflopmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\flipflopmodule.obj"
	-@erase "$(INTDIR)\flipflopmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\flipflopmodule.dll"
	-@erase "$(OUTDIR)\flipflopmodule.exp"
	-@erase "$(OUTDIR)\flipflopmodule.ilk"
	-@erase "$(OUTDIR)\flipflopmodule.lib"
	-@erase "$(OUTDIR)\flipflopmodule.pdb"
	-@erase "flipflopmodule.def"
	-@erase "flipflopmodule.h"
	-@erase "flipflopmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_USRDLL" /D "flipflopmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\flipflopmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\flipflopmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\flipflopmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\flipflopmodule.def" /out:"$(OUTDIR)\flipflopmodule.dll" /implib:"$(OUTDIR)\flipflopmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\flipflopmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\flipflopmodule.obj" \
	"$(INTDIR)\flipflopmodule_auto.obj"

"$(OUTDIR)\flipflopmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\flipflopmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\flipflopmodule_auto.c" ".\flipflopmodule.h" ".\flipflopmodule.def" "$(OUTDIR)\flipflopmodule.dll"
   copy .\Debug\flipflopmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("flipflopmodule.dep")
!INCLUDE "flipflopmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "flipflopmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "flipflopmodule - Win32 Release" || "$(CFG)" == "flipflopmodule - Win32 Debug"
SOURCE=.\flipflopmodule.c

!IF  "$(CFG)" == "flipflopmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /D "_WINDOWS" /D "_USRDLL" /D "flipflopmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\flipflopmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\flipflopmodule.obj" : $(SOURCE) "$(INTDIR)" ".\flipflopmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "flipflopmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /D "_WINDOWS" /D "_USRDLL" /D "flipflopmodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\flipflopmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\flipflopmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\flipflopmodule_auto.c

"$(INTDIR)\flipflopmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\flipflopmodule.h"


SOURCE=.\flipflopmodule.spec

!IF  "$(CFG)" == "flipflopmodule - Win32 Release"

InputPath=.\flipflopmodule.spec
InputName=flipflopmodule

".\flipflopmodule.h"	".\flipflopmodule_auto.c"	".\flipflopmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "flipflopmodule - Win32 Debug"

InputPath=.\flipflopmodule.spec
InputName=flipflopmodule

".\flipflopmodule.h"	".\flipflopmodule_auto.c"	".\flipflopmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

