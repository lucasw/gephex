# Microsoft Developer Studio Generated NMAKE File, Based on numxfadermodule.dsp
!IF "$(CFG)" == ""
CFG=numxfadermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. numxfadermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "numxfadermodule - Win32 Release" && "$(CFG)" != "numxfadermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "numxfadermodule.mak" CFG="numxfadermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "numxfadermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "numxfadermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "numxfadermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\numxfadermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numxfadermodule.obj"
	-@erase "$(INTDIR)\numxfadermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\numxfadermodule.dll"
	-@erase "$(OUTDIR)\numxfadermodule.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "numxfadermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numxfadermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\numxfadermodule.pdb" /machine:I386 /def:".\numxfadermodule.def" /out:"$(OUTDIR)\numxfadermodule.dll" /implib:"$(OUTDIR)\numxfadermodule.lib" 
DEF_FILE= \
	".\numxfadermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numxfadermodule.obj" \
	"$(INTDIR)\numxfadermodule_auto.obj"

"$(OUTDIR)\numxfadermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\numxfadermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\numxfadermodule.dll"
   copy .\Release\numxfadermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "numxfadermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\numxfadermodule_auto.c" ".\numxfadermodule.h" ".\numxfadermodule.def" "$(OUTDIR)\numxfadermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\numxfadermodule.obj"
	-@erase "$(INTDIR)\numxfadermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\numxfadermodule.dll"
	-@erase "$(OUTDIR)\numxfadermodule.exp"
	-@erase "$(OUTDIR)\numxfadermodule.ilk"
	-@erase "$(OUTDIR)\numxfadermodule.lib"
	-@erase "$(OUTDIR)\numxfadermodule.pdb"
	-@erase "numxfadermodule.def"
	-@erase "numxfadermodule.h"
	-@erase "numxfadermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "numxfadermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\numxfadermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\numxfadermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\numxfadermodule.def" /out:"$(OUTDIR)\numxfadermodule.dll" /implib:"$(OUTDIR)\numxfadermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\numxfadermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\numxfadermodule.obj" \
	"$(INTDIR)\numxfadermodule_auto.obj"

"$(OUTDIR)\numxfadermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\numxfadermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\numxfadermodule_auto.c" ".\numxfadermodule.h" ".\numxfadermodule.def" "$(OUTDIR)\numxfadermodule.dll"
   copy .\Debug\numxfadermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("numxfadermodule.dep")
!INCLUDE "numxfadermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "numxfadermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "numxfadermodule - Win32 Release" || "$(CFG)" == "numxfadermodule - Win32 Debug"
SOURCE=.\numxfadermodule.c

!IF  "$(CFG)" == "numxfadermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "numxfadermodule_EXPORTS" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\numxfadermodule.obj" : $(SOURCE) "$(INTDIR)" ".\numxfadermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "numxfadermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_USRDLL" /D "numxfadermodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\numxfadermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\numxfadermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\numxfadermodule_auto.c

"$(INTDIR)\numxfadermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\numxfadermodule.h"


SOURCE=.\numxfadermodule.spec

!IF  "$(CFG)" == "numxfadermodule - Win32 Release"

InputPath=.\numxfadermodule.spec

".\numxfadermodule.h"	".\numxfadermodule_auto.c"	".\numxfadermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c numxfadermodule.spec 
	python ../../pluc.py h numxfadermodule.spec 
	python ../../pluc.py def numxfadermodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "numxfadermodule - Win32 Debug"

InputPath=.\numxfadermodule.spec

".\numxfadermodule.h"	".\numxfadermodule_auto.c"	".\numxfadermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c numxfadermodule.spec 
	python ../../pluc.py h numxfadermodule.spec 
	python ../../pluc.py def numxfadermodule.spec
<< 
	

!ENDIF 


!ENDIF 

