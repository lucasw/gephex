# Microsoft Developer Studio Generated NMAKE File, Based on dplmodule.dsp
!IF "$(CFG)" == ""
CFG=dplmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. dplmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "dplmodule - Win32 Release" && "$(CFG)" != "dplmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dplmodule.mak" CFG="dplmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "dplmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dplmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dplmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\dplmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\dplmodule.obj"
	-@erase "$(INTDIR)\dplmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dplmodule.dll"
	-@erase "$(OUTDIR)\dplmodule.exp"
	-@erase "$(OUTDIR)\dplmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "dplmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dplmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dplmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dplmodule.pdb" /machine:I386 /def:".\dplmodule.def" /out:"$(OUTDIR)\dplmodule.dll" /implib:"$(OUTDIR)\dplmodule.lib" 
DEF_FILE= \
	".\dplmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\dplmodule.obj" \
	"$(INTDIR)\dplmodule_auto.obj"

"$(OUTDIR)\dplmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\dplmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\dplmodule.dll"
   copy .\Release\dplmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "dplmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\dplmodule_auto.c" ".\dplmodule.h" ".\dplmodule.def" "$(OUTDIR)\dplmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\dplmodule.obj"
	-@erase "$(INTDIR)\dplmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dplmodule.dll"
	-@erase "$(OUTDIR)\dplmodule.exp"
	-@erase "$(OUTDIR)\dplmodule.ilk"
	-@erase "$(OUTDIR)\dplmodule.lib"
	-@erase "$(OUTDIR)\dplmodule.pdb"
	-@erase "dplmodule.def"
	-@erase "dplmodule.h"
	-@erase "dplmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "dplmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dplmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dplmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\dplmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\dplmodule.def" /out:"$(OUTDIR)\dplmodule.dll" /implib:"$(OUTDIR)\dplmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\dplmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\dplmodule.obj" \
	"$(INTDIR)\dplmodule_auto.obj"

"$(OUTDIR)\dplmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\dplmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\dplmodule_auto.c" ".\dplmodule.h" ".\dplmodule.def" "$(OUTDIR)\dplmodule.dll"
   copy .\Debug\dplmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("dplmodule.dep")
!INCLUDE "dplmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "dplmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dplmodule - Win32 Release" || "$(CFG)" == "dplmodule - Win32 Debug"
SOURCE=.\dplmodule.c

!IF  "$(CFG)" == "dplmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "dplmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dplmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dplmodule.obj" : $(SOURCE) "$(INTDIR)" ".\dplmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dplmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "dplmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dplmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dplmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\dplmodule_auto.c

"$(INTDIR)\dplmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\dplmodule.h"


SOURCE=.\dplmodule.spec

!IF  "$(CFG)" == "dplmodule - Win32 Release"

InputPath=.\dplmodule.spec
InputName=dplmodule

".\dplmodule.h"	".\dplmodule_auto.c"	".\dplmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "dplmodule - Win32 Debug"

InputPath=.\dplmodule.spec
InputName=dplmodule

".\dplmodule.h"	".\dplmodule_auto.c"	".\dplmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

