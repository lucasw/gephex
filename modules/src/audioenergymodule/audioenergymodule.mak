# Microsoft Developer Studio Generated NMAKE File, Based on audioenergymodule.dsp
!IF "$(CFG)" == ""
CFG=audioenergymodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audioenergymodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audioenergymodule - Win32 Release" && "$(CFG)" != "audioenergymodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audioenergymodule.mak" CFG="audioenergymodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audioenergymodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audioenergymodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audioenergymodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audioenergymodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audioenergymodule.obj"
	-@erase "$(INTDIR)\audioenergymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\audioenergymodule.dll"
	-@erase "$(OUTDIR)\audioenergymodule.exp"
	-@erase "$(OUTDIR)\audioenergymodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audioenergymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audioenergymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audioenergymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audioenergymodule.pdb" /machine:I386 /def:".\audioenergymodule.def" /out:"$(OUTDIR)\audioenergymodule.dll" /implib:"$(OUTDIR)\audioenergymodule.lib" 
DEF_FILE= \
	".\audioenergymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audioenergymodule.obj" \
	"$(INTDIR)\audioenergymodule_auto.obj"

"$(OUTDIR)\audioenergymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audioenergymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audioenergymodule.dll"
   copy .\Release\audioenergymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audioenergymodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audioenergymodule_auto.c" ".\audioenergymodule.h" ".\audioenergymodule.def" "$(OUTDIR)\audioenergymodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audioenergymodule.obj"
	-@erase "$(INTDIR)\audioenergymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\audioenergymodule.dll"
	-@erase "$(OUTDIR)\audioenergymodule.exp"
	-@erase "$(OUTDIR)\audioenergymodule.ilk"
	-@erase "$(OUTDIR)\audioenergymodule.lib"
	-@erase "$(OUTDIR)\audioenergymodule.pdb"
	-@erase "audioenergymodule.def"
	-@erase "audioenergymodule.h"
	-@erase "audioenergymodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audioenergymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audioenergymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audioenergymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audioenergymodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audioenergymodule.def" /out:"$(OUTDIR)\audioenergymodule.dll" /implib:"$(OUTDIR)\audioenergymodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audioenergymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audioenergymodule.obj" \
	"$(INTDIR)\audioenergymodule_auto.obj"

"$(OUTDIR)\audioenergymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audioenergymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audioenergymodule_auto.c" ".\audioenergymodule.h" ".\audioenergymodule.def" "$(OUTDIR)\audioenergymodule.dll"
   copy .\Debug\audioenergymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audioenergymodule.dep")
!INCLUDE "audioenergymodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audioenergymodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audioenergymodule - Win32 Release" || "$(CFG)" == "audioenergymodule - Win32 Debug"
SOURCE=.\audioenergymodule.cpp

"$(INTDIR)\audioenergymodule.obj" : $(SOURCE) "$(INTDIR)" ".\audioenergymodule.h"


SOURCE=.\audioenergymodule_auto.c

"$(INTDIR)\audioenergymodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\audioenergymodule.h"


SOURCE=.\audioenergymodule.spec

!IF  "$(CFG)" == "audioenergymodule - Win32 Release"

InputPath=.\audioenergymodule.spec
InputName=audioenergymodule

".\audioenergymodule.h"	".\audioenergymodule_auto.c"	".\audioenergymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audioenergymodule - Win32 Debug"

InputPath=.\audioenergymodule.spec
InputName=audioenergymodule

".\audioenergymodule.h"	".\audioenergymodule_auto.c"	".\audioenergymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

