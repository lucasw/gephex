# Microsoft Developer Studio Generated NMAKE File, Based on number2colormodule.dsp
!IF "$(CFG)" == ""
CFG=number2colormodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. number2colormodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "number2colormodule - Win32 Release" && "$(CFG)" != "number2colormodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "number2colormodule.mak" CFG="number2colormodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "number2colormodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "number2colormodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "number2colormodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\number2colormodule.dll"


CLEAN :
	-@erase "$(INTDIR)\number2colormodule.obj"
	-@erase "$(INTDIR)\number2colormodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\number2colormodule.dll"
	-@erase "$(OUTDIR)\number2colormodule.exp"
	-@erase "$(OUTDIR)\number2colormodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../types/rgbtype" /I "../../types/numbertype" /I "../../engine" /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "number2colormodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\number2colormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\number2colormodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\number2colormodule.pdb" /machine:I386 /def:".\number2colormodule.def" /out:"$(OUTDIR)\number2colormodule.dll" /implib:"$(OUTDIR)\number2colormodule.lib" 
DEF_FILE= \
	".\number2colormodule.def"
LINK32_OBJS= \
	"$(INTDIR)\number2colormodule.obj" \
	"$(INTDIR)\number2colormodule_auto.obj"

"$(OUTDIR)\number2colormodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\number2colormodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\number2colormodule.dll"
   copy .\Release\number2colormodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "number2colormodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\number2colormodule_auto.c" ".\number2colormodule.h" ".\number2colormodule.def" "$(OUTDIR)\number2colormodule.dll"


CLEAN :
	-@erase "$(INTDIR)\number2colormodule.obj"
	-@erase "$(INTDIR)\number2colormodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\number2colormodule.dll"
	-@erase "$(OUTDIR)\number2colormodule.exp"
	-@erase "$(OUTDIR)\number2colormodule.ilk"
	-@erase "$(OUTDIR)\number2colormodule.lib"
	-@erase "$(OUTDIR)\number2colormodule.pdb"
	-@erase "number2colormodule.def"
	-@erase "number2colormodule.h"
	-@erase "number2colormodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "number2colormodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\number2colormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\number2colormodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\number2colormodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\number2colormodule.def" /out:"$(OUTDIR)\number2colormodule.dll" /implib:"$(OUTDIR)\number2colormodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\number2colormodule.def"
LINK32_OBJS= \
	"$(INTDIR)\number2colormodule.obj" \
	"$(INTDIR)\number2colormodule_auto.obj"

"$(OUTDIR)\number2colormodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\number2colormodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\number2colormodule_auto.c" ".\number2colormodule.h" ".\number2colormodule.def" "$(OUTDIR)\number2colormodule.dll"
   copy .\Debug\number2colormodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("number2colormodule.dep")
!INCLUDE "number2colormodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "number2colormodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "number2colormodule - Win32 Release" || "$(CFG)" == "number2colormodule - Win32 Debug"
SOURCE=.\number2colormodule.c

!IF  "$(CFG)" == "number2colormodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../types/rgbtype" /I "../../types/numbertype" /I "../../engine" /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "number2colormodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\number2colormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\number2colormodule.obj" : $(SOURCE) "$(INTDIR)" ".\number2colormodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "number2colormodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/rgbtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "number2colormodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\number2colormodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\number2colormodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\number2colormodule_auto.c

"$(INTDIR)\number2colormodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\number2colormodule.h"


SOURCE=.\number2colormodule.spec

!IF  "$(CFG)" == "number2colormodule - Win32 Release"

InputPath=.\number2colormodule.spec

".\number2colormodule.h"	".\number2colormodule_auto.c"	".\number2colormodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c number2colormodule.spec 
	python ..\..\pluc.py h number2colormodule.spec 
	python ..\..\pluc.py def number2colormodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "number2colormodule - Win32 Debug"

InputPath=.\number2colormodule.spec

".\number2colormodule.h"	".\number2colormodule_auto.c"	".\number2colormodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c number2colormodule.spec 
	python ..\..\pluc.py h number2colormodule.spec 
	python ..\..\pluc.py def number2colormodule.spec
<< 
	

!ENDIF 


!ENDIF 

