# Microsoft Developer Studio Generated NMAKE File, Based on ifsxfadermodule.dsp
!IF "$(CFG)" == ""
CFG=ifsxfadermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ifsxfadermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ifsxfadermodule - Win32 Release" && "$(CFG)" != "ifsxfadermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ifsxfadermodule.mak" CFG="ifsxfadermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ifsxfadermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifsxfadermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ifsxfadermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ifsxfadermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ifsxfadermodule.obj"
	-@erase "$(INTDIR)\ifsxfadermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ifsxfadermodule.dll"
	-@erase "$(OUTDIR)\ifsxfadermodule.exp"
	-@erase "$(OUTDIR)\ifsxfadermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/ifstype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ifsxfadermodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ifsxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifsxfadermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ifsxfadermodule.pdb" /machine:I386 /def:".\ifsxfadermodule.def" /out:"$(OUTDIR)\ifsxfadermodule.dll" /implib:"$(OUTDIR)\ifsxfadermodule.lib" 
DEF_FILE= \
	".\ifsxfadermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ifsxfadermodule.obj" \
	"$(INTDIR)\ifsxfadermodule_auto.obj"

"$(OUTDIR)\ifsxfadermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\ifsxfadermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ifsxfadermodule.dll"
   copy .\Release\ifsxfadermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ifsxfadermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ifsxfadermodule_auto.c" ".\ifsxfadermodule.h" ".\ifsxfadermodule.def" "$(OUTDIR)\ifsxfadermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ifsxfadermodule.obj"
	-@erase "$(INTDIR)\ifsxfadermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ifsxfadermodule.dll"
	-@erase "$(OUTDIR)\ifsxfadermodule.exp"
	-@erase "$(OUTDIR)\ifsxfadermodule.ilk"
	-@erase "$(OUTDIR)\ifsxfadermodule.lib"
	-@erase "$(OUTDIR)\ifsxfadermodule.pdb"
	-@erase "ifsxfadermodule.def"
	-@erase "ifsxfadermodule.h"
	-@erase "ifsxfadermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/ifstype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ifsxfadermodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ifsxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifsxfadermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ifsxfadermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\ifsxfadermodule.def" /out:"$(OUTDIR)\ifsxfadermodule.dll" /implib:"$(OUTDIR)\ifsxfadermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\ifsxfadermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ifsxfadermodule.obj" \
	"$(INTDIR)\ifsxfadermodule_auto.obj"

"$(OUTDIR)\ifsxfadermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\ifsxfadermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\ifsxfadermodule_auto.c" ".\ifsxfadermodule.h" ".\ifsxfadermodule.def" "$(OUTDIR)\ifsxfadermodule.dll"
   copy .\Debug\ifsxfadermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ifsxfadermodule.dep")
!INCLUDE "ifsxfadermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "ifsxfadermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ifsxfadermodule - Win32 Release" || "$(CFG)" == "ifsxfadermodule - Win32 Debug"
SOURCE=.\ifsxfadermodule.cpp

!IF  "$(CFG)" == "ifsxfadermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/ifstype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ifsxfadermodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ifsxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ifsxfadermodule.obj" : $(SOURCE) "$(INTDIR)" ".\ifsxfadermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ifsxfadermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/ifstype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ifsxfadermodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ifsxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\ifsxfadermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ifsxfadermodule_auto.c

"$(INTDIR)\ifsxfadermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\ifsxfadermodule.h"


SOURCE=.\ifsxfadermodule.spec

!IF  "$(CFG)" == "ifsxfadermodule - Win32 Release"

InputPath=.\ifsxfadermodule.spec
InputName=ifsxfadermodule

".\ifsxfadermodule.h"	".\ifsxfadermodule_auto.c"	".\ifsxfadermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "ifsxfadermodule - Win32 Debug"

InputPath=.\ifsxfadermodule.spec
InputName=ifsxfadermodule

".\ifsxfadermodule.h"	".\ifsxfadermodule_auto.c"	".\ifsxfadermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

