# Microsoft Developer Studio Generated NMAKE File, Based on audiospecmodule.dsp
!IF "$(CFG)" == ""
CFG=audiospecmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audiospecmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audiospecmodule - Win32 Release" && "$(CFG)" != "audiospecmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audiospecmodule.mak" CFG="audiospecmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audiospecmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audiospecmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audiospecmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audiospecmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiospecmodule.obj"
	-@erase "$(INTDIR)\audiospecmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\audiospecmodule.dll"
	-@erase "$(OUTDIR)\audiospecmodule.exp"
	-@erase "$(OUTDIR)\audiospecmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiospecmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiospecmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiospecmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audiospecmodule.pdb" /machine:I386 /def:".\audiospecmodule.def" /out:"$(OUTDIR)\audiospecmodule.dll" /implib:"$(OUTDIR)\audiospecmodule.lib" 
DEF_FILE= \
	".\audiospecmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiospecmodule.obj" \
	"$(INTDIR)\audiospecmodule_auto.obj"

"$(OUTDIR)\audiospecmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audiospecmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audiospecmodule.dll"
   copy .\Release\audiospecmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audiospecmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audiospecmodule_auto.c" ".\audiospecmodule.h" ".\audiospecmodule.def" "$(OUTDIR)\audiospecmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiospecmodule.obj"
	-@erase "$(INTDIR)\audiospecmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\audiospecmodule.dll"
	-@erase "$(OUTDIR)\audiospecmodule.exp"
	-@erase "$(OUTDIR)\audiospecmodule.ilk"
	-@erase "$(OUTDIR)\audiospecmodule.lib"
	-@erase "$(OUTDIR)\audiospecmodule.pdb"
	-@erase "audiospecmodule.def"
	-@erase "audiospecmodule.h"
	-@erase "audiospecmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiospecmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiospecmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiospecmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audiospecmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audiospecmodule.def" /out:"$(OUTDIR)\audiospecmodule.dll" /implib:"$(OUTDIR)\audiospecmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audiospecmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiospecmodule.obj" \
	"$(INTDIR)\audiospecmodule_auto.obj"

"$(OUTDIR)\audiospecmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audiospecmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audiospecmodule_auto.c" ".\audiospecmodule.h" ".\audiospecmodule.def" "$(OUTDIR)\audiospecmodule.dll"
   copy .\Debug\audiospecmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audiospecmodule.dep")
!INCLUDE "audiospecmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audiospecmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audiospecmodule - Win32 Release" || "$(CFG)" == "audiospecmodule - Win32 Debug"
SOURCE=.\audiospecmodule.cpp

"$(INTDIR)\audiospecmodule.obj" : $(SOURCE) "$(INTDIR)" ".\audiospecmodule.h"


SOURCE=.\audiospecmodule_auto.c

"$(INTDIR)\audiospecmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\audiospecmodule.h"


SOURCE=.\audiospecmodule.spec

!IF  "$(CFG)" == "audiospecmodule - Win32 Release"

InputPath=.\audiospecmodule.spec
InputName=audiospecmodule

".\audiospecmodule.h"	".\audiospecmodule_auto.c"	".\audiospecmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audiospecmodule - Win32 Debug"

InputPath=.\audiospecmodule.spec
InputName=audiospecmodule

".\audiospecmodule.h"	".\audiospecmodule_auto.c"	".\audiospecmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

