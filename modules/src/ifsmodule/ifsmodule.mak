# Microsoft Developer Studio Generated NMAKE File, Based on ifsmodule.dsp
!IF "$(CFG)" == ""
CFG=ifsmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ifsmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ifsmodule - Win32 Release" && "$(CFG)" != "ifsmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ifsmodule.mak" CFG="ifsmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ifsmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifsmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ifsmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ifsmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ifsmodule.obj"
	-@erase "$(INTDIR)\ifsmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ifsmodule.dll"
	-@erase "$(OUTDIR)\ifsmodule.exp"
	-@erase "$(OUTDIR)\ifsmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../.." /I "../../../util/include/" /I "../../../types/src/ifstype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include/compatibility" /I "../../../util/include" /I "../../../util/src/misc" /D "NDEBUG" /D "HAVE_CONFIG_H" /D for="if(0); else for" /D "_WINDOWS" /D "_USRDLL" /D "ifsmodule_EXPORTS" /D for="if (0); else for" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\ifsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifsmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ifsmodule.pdb" /machine:I386 /def:".\ifsmodule.def" /out:"$(OUTDIR)\ifsmodule.dll" /implib:"$(OUTDIR)\ifsmodule.lib" 
DEF_FILE= \
	".\ifsmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ifsmodule.obj" \
	"$(INTDIR)\ifsmodule_auto.obj"

"$(OUTDIR)\ifsmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\ifsmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ifsmodule.dll"
   copy .\Release\ifsmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ifsmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ifsmodule_auto.c" ".\ifsmodule.h" ".\ifsmodule.def" "..\..\..\config.h" "$(OUTDIR)\ifsmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ifsmodule.obj"
	-@erase "$(INTDIR)\ifsmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ifsmodule.dll"
	-@erase "$(OUTDIR)\ifsmodule.exp"
	-@erase "$(OUTDIR)\ifsmodule.ilk"
	-@erase "$(OUTDIR)\ifsmodule.lib"
	-@erase "$(OUTDIR)\ifsmodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "ifsmodule.def"
	-@erase "ifsmodule.h"
	-@erase "ifsmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/ifstype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include/compatibility" /I "../../../util/include" /I "../../../util/src/misc" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "ifsmodule_EXPORTS" /D for="if (0); else for" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ifsmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifsmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ifsmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\ifsmodule.def" /out:"$(OUTDIR)\ifsmodule.dll" /implib:"$(OUTDIR)\ifsmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\ifsmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ifsmodule.obj" \
	"$(INTDIR)\ifsmodule_auto.obj"

"$(OUTDIR)\ifsmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\ifsmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\ifsmodule_auto.c" ".\ifsmodule.h" ".\ifsmodule.def" "..\..\..\config.h" "$(OUTDIR)\ifsmodule.dll"
   copy .\Debug\ifsmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("ifsmodule.dep")
!INCLUDE "ifsmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "ifsmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ifsmodule - Win32 Release" || "$(CFG)" == "ifsmodule - Win32 Debug"
SOURCE=.\ifsmodule.cpp

"$(INTDIR)\ifsmodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\ifsmodule.h"


SOURCE=.\ifsmodule_auto.c

"$(INTDIR)\ifsmodule_auto.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\ifsmodule.h"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "ifsmodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "ifsmodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\ifsmodule.spec

!IF  "$(CFG)" == "ifsmodule - Win32 Release"

InputPath=.\ifsmodule.spec
InputName=ifsmodule

".\ifsmodule.h"	".\ifsmodule_auto.c"	".\ifsmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "ifsmodule - Win32 Debug"

InputPath=.\ifsmodule.spec
InputName=ifsmodule

".\ifsmodule.h"	".\ifsmodule_auto.c"	".\ifsmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

