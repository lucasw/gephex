# Microsoft Developer Studio Generated NMAKE File, Based on imagebuffermodule.dsp
!IF "$(CFG)" == ""
CFG=imagebuffermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. imagebuffermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "imagebuffermodule - Win32 Release" && "$(CFG)" != "imagebuffermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "imagebuffermodule.mak" CFG="imagebuffermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "imagebuffermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "imagebuffermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "imagebuffermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\imagebuffermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\imagebuffermodule.obj"
	-@erase "$(INTDIR)\imagebuffermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\imagebuffermodule.dll"
	-@erase "$(OUTDIR)\imagebuffermodule.exp"
	-@erase "$(OUTDIR)\imagebuffermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "imagebuffermodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imagebuffermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\imagebuffermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\imagebuffermodule.pdb" /machine:I386 /def:".\imagebuffermodule.def" /out:"$(OUTDIR)\imagebuffermodule.dll" /implib:"$(OUTDIR)\imagebuffermodule.lib" 
DEF_FILE= \
	".\imagebuffermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\imagebuffermodule.obj" \
	"$(INTDIR)\imagebuffermodule_auto.obj"

"$(OUTDIR)\imagebuffermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\imagebuffermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\imagebuffermodule.dll"
   copy .\Release\imagebuffermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "imagebuffermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\imagebuffermodule_auto.c" ".\imagebuffermodule.h" ".\imagebuffermodule.def" "$(OUTDIR)\imagebuffermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\imagebuffermodule.obj"
	-@erase "$(INTDIR)\imagebuffermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\imagebuffermodule.dll"
	-@erase "$(OUTDIR)\imagebuffermodule.exp"
	-@erase "$(OUTDIR)\imagebuffermodule.ilk"
	-@erase "$(OUTDIR)\imagebuffermodule.lib"
	-@erase "$(OUTDIR)\imagebuffermodule.pdb"
	-@erase "imagebuffermodule.def"
	-@erase "imagebuffermodule.h"
	-@erase "imagebuffermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "imagebuffermodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\imagebuffermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\imagebuffermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\imagebuffermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\imagebuffermodule.def" /out:"$(OUTDIR)\imagebuffermodule.dll" /implib:"$(OUTDIR)\imagebuffermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\imagebuffermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\imagebuffermodule.obj" \
	"$(INTDIR)\imagebuffermodule_auto.obj"

"$(OUTDIR)\imagebuffermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\imagebuffermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\imagebuffermodule_auto.c" ".\imagebuffermodule.h" ".\imagebuffermodule.def" "$(OUTDIR)\imagebuffermodule.dll"
   copy .\Debug\imagebuffermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("imagebuffermodule.dep")
!INCLUDE "imagebuffermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "imagebuffermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "imagebuffermodule - Win32 Release" || "$(CFG)" == "imagebuffermodule - Win32 Debug"
SOURCE=.\imagebuffermodule.c

!IF  "$(CFG)" == "imagebuffermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "imagebuffermodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\imagebuffermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\imagebuffermodule.obj" : $(SOURCE) "$(INTDIR)" ".\imagebuffermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "imagebuffermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "imagebuffermodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\imagebuffermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\imagebuffermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\imagebuffermodule_auto.c

"$(INTDIR)\imagebuffermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\imagebuffermodule.h"


SOURCE=.\imagebuffermodule.spec

!IF  "$(CFG)" == "imagebuffermodule - Win32 Release"

InputPath=.\imagebuffermodule.spec
InputName=imagebuffermodule

".\imagebuffermodule.h"	".\imagebuffermodule_auto.c"	".\imagebuffermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "imagebuffermodule - Win32 Debug"

InputPath=.\imagebuffermodule.spec
InputName=imagebuffermodule

".\imagebuffermodule.h"	".\imagebuffermodule_auto.c"	".\imagebuffermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

