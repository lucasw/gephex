# Microsoft Developer Studio Generated NMAKE File, Based on twolayermodule.dsp
!IF "$(CFG)" == ""
CFG=twolayermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. twolayermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "twolayermodule - Win32 Release" && "$(CFG)" != "twolayermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "twolayermodule.mak" CFG="twolayermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "twolayermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "twolayermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "twolayermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\twolayermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\twolayermodule.obj"
	-@erase "$(INTDIR)\twolayermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\twolayermodule.dll"
	-@erase "$(OUTDIR)\twolayermodule.exp"
	-@erase "$(OUTDIR)\twolayermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "twolayermodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D for="if (0) {} else for" /Fp"$(INTDIR)\twolayermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\twolayermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\twolayermodule.pdb" /machine:I386 /def:".\twolayermodule.def" /out:"$(OUTDIR)\twolayermodule.dll" /implib:"$(OUTDIR)\twolayermodule.lib" 
DEF_FILE= \
	".\twolayermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\twolayermodule.obj" \
	"$(INTDIR)\twolayermodule_auto.obj"

"$(OUTDIR)\twolayermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\twolayermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\twolayermodule.dll"
   copy .\Release\twolayermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "twolayermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\twolayermodule_auto.c" ".\twolayermodule.h" ".\twolayermodule.def" "$(OUTDIR)\twolayermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\twolayermodule.obj"
	-@erase "$(INTDIR)\twolayermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\twolayermodule.dll"
	-@erase "$(OUTDIR)\twolayermodule.exp"
	-@erase "$(OUTDIR)\twolayermodule.ilk"
	-@erase "$(OUTDIR)\twolayermodule.lib"
	-@erase "$(OUTDIR)\twolayermodule.pdb"
	-@erase "twolayermodule.def"
	-@erase "twolayermodule.h"
	-@erase "twolayermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "twolayermodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D for="if (0) {} else for" /Fp"$(INTDIR)\twolayermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\twolayermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\twolayermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\twolayermodule.def" /out:"$(OUTDIR)\twolayermodule.dll" /implib:"$(OUTDIR)\twolayermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\twolayermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\twolayermodule.obj" \
	"$(INTDIR)\twolayermodule_auto.obj"

"$(OUTDIR)\twolayermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\twolayermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\twolayermodule_auto.c" ".\twolayermodule.h" ".\twolayermodule.def" "$(OUTDIR)\twolayermodule.dll"
   copy .\Debug\twolayermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("twolayermodule.dep")
!INCLUDE "twolayermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "twolayermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "twolayermodule - Win32 Release" || "$(CFG)" == "twolayermodule - Win32 Debug"
SOURCE=.\twolayermodule.cpp

"$(INTDIR)\twolayermodule.obj" : $(SOURCE) "$(INTDIR)" ".\twolayermodule.h"


SOURCE=.\twolayermodule_auto.c

"$(INTDIR)\twolayermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\twolayermodule.h"


SOURCE=.\twolayermodule.spec

!IF  "$(CFG)" == "twolayermodule - Win32 Release"

InputPath=.\twolayermodule.spec
InputName=twolayermodule

".\twolayermodule.h"	".\twolayermodule_auto.c"	".\twolayermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "twolayermodule - Win32 Debug"

InputPath=.\twolayermodule.spec
InputName=twolayermodule

".\twolayermodule.h"	".\twolayermodule_auto.c"	".\twolayermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

