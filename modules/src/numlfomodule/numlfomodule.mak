# Microsoft Developer Studio Generated NMAKE File, Based on numlfomodule.dsp
!IF "$(CFG)" == ""
CFG=numlfomodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. numlfomodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "numlfomodule - Win32 Release" && "$(CFG)" != "numlfomodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "numlfomodule.mak" CFG="numlfomodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "numlfomodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "numlfomodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "numlfomodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\numlfomodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numlfomodule.obj"
	-@erase "$(INTDIR)\numlfomodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\numlfomodule.dll"
	-@erase "$(OUTDIR)\numlfomodule.exp"
	-@erase "$(OUTDIR)\numlfomodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/lfotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "numlfomodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\numlfomodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numlfomodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\numlfomodule.pdb" /machine:I386 /def:".\numlfomodule.def" /out:"$(OUTDIR)\numlfomodule.dll" /implib:"$(OUTDIR)\numlfomodule.lib" 
DEF_FILE= \
	".\numlfomodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numlfomodule.obj" \
	"$(INTDIR)\numlfomodule_auto.obj"

"$(OUTDIR)\numlfomodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\numlfomodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\numlfomodule.dll"
   copy .\Release\numlfomodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "numlfomodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\numlfomodule_auto.c" ".\numlfomodule.h" ".\numlfomodule.def" "$(OUTDIR)\numlfomodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numlfomodule.obj"
	-@erase "$(INTDIR)\numlfomodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\numlfomodule.dll"
	-@erase "$(OUTDIR)\numlfomodule.exp"
	-@erase "$(OUTDIR)\numlfomodule.ilk"
	-@erase "$(OUTDIR)\numlfomodule.lib"
	-@erase "$(OUTDIR)\numlfomodule.pdb"
	-@erase "numlfomodule.def"
	-@erase "numlfomodule.h"
	-@erase "numlfomodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/lfotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "numlfomodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\numlfomodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numlfomodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\numlfomodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\numlfomodule.def" /out:"$(OUTDIR)\numlfomodule.dll" /implib:"$(OUTDIR)\numlfomodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\numlfomodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numlfomodule.obj" \
	"$(INTDIR)\numlfomodule_auto.obj"

"$(OUTDIR)\numlfomodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\numlfomodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\numlfomodule_auto.c" ".\numlfomodule.h" ".\numlfomodule.def" "$(OUTDIR)\numlfomodule.dll"
   copy .\Debug\numlfomodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("numlfomodule.dep")
!INCLUDE "numlfomodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "numlfomodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "numlfomodule - Win32 Release" || "$(CFG)" == "numlfomodule - Win32 Debug"
SOURCE=.\numlfomodule.c

!IF  "$(CFG)" == "numlfomodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/lfotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "numlfomodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\numlfomodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\numlfomodule.obj" : $(SOURCE) "$(INTDIR)" ".\numlfomodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "numlfomodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/lfotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "numlfomodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\numlfomodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\numlfomodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\numlfomodule_auto.c

"$(INTDIR)\numlfomodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\numlfomodule.h"


SOURCE=.\numlfomodule.spec

!IF  "$(CFG)" == "numlfomodule - Win32 Release"

InputPath=.\numlfomodule.spec
InputName=numlfomodule

".\numlfomodule.h"	".\numlfomodule_auto.c"	".\numlfomodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "numlfomodule - Win32 Debug"

InputPath=.\numlfomodule.spec
InputName=numlfomodule

".\numlfomodule.h"	".\numlfomodule_auto.c"	".\numlfomodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

