# Microsoft Developer Studio Generated NMAKE File, Based on sdlfontmodule.dsp
!IF "$(CFG)" == ""
CFG=sdlfontmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. sdlfontmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "sdlfontmodule - Win32 Release" && "$(CFG)" != "sdlfontmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sdlfontmodule.mak" CFG="sdlfontmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sdlfontmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sdlfontmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sdlfontmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\sdlfontmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\sdlfontmodule.obj"
	-@erase "$(INTDIR)\sdlfontmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\sdlfontmodule.dll"
	-@erase "$(OUTDIR)\sdlfontmodule.exp"
	-@erase "$(OUTDIR)\sdlfontmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "$(SDL_DIR)/include" /I "$(SDL_TTF_DIR)" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/stringtype" /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sdlfontmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\sdlfontmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sdlfontmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib sdl_ttf.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\sdlfontmodule.pdb" /machine:I386 /def:".\sdlfontmodule.def" /out:"$(OUTDIR)\sdlfontmodule.dll" /implib:"$(OUTDIR)\sdlfontmodule.lib" /libpath:"$(SDL_TTF_DIR)/lib" /libpath:"$(SDL_DIR)/lib" 
DEF_FILE= \
	".\sdlfontmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\sdlfontmodule.obj" \
	"$(INTDIR)\sdlfontmodule_auto.obj"

"$(OUTDIR)\sdlfontmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\sdlfontmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\sdlfontmodule.dll"
   copy .\Release\sdlfontmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "sdlfontmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\sdlfontmodule_auto.c" ".\sdlfontmodule.h" ".\sdlfontmodule.def" "$(OUTDIR)\sdlfontmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\sdlfontmodule.obj"
	-@erase "$(INTDIR)\sdlfontmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\sdlfontmodule.dll"
	-@erase "$(OUTDIR)\sdlfontmodule.exp"
	-@erase "$(OUTDIR)\sdlfontmodule.ilk"
	-@erase "$(OUTDIR)\sdlfontmodule.lib"
	-@erase "$(OUTDIR)\sdlfontmodule.pdb"
	-@erase "sdlfontmodule.def"
	-@erase "sdlfontmodule.h"
	-@erase "sdlfontmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "$(SDL_DIR)/include" /I "$(SDL_TTF_DIR)" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/stringtype" /I "../../../types/src/positiontype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sdlfontmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\sdlfontmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sdlfontmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib sdl_ttf.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\sdlfontmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\sdlfontmodule.def" /out:"$(OUTDIR)\sdlfontmodule.dll" /implib:"$(OUTDIR)\sdlfontmodule.lib" /pdbtype:sept /libpath:"$(SDL_TTF_DIR)/lib" /libpath:"$(SDL_DIR)/lib" 
DEF_FILE= \
	".\sdlfontmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\sdlfontmodule.obj" \
	"$(INTDIR)\sdlfontmodule_auto.obj"

"$(OUTDIR)\sdlfontmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\sdlfontmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\sdlfontmodule_auto.c" ".\sdlfontmodule.h" ".\sdlfontmodule.def" "$(OUTDIR)\sdlfontmodule.dll"
   copy .\Debug\sdlfontmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("sdlfontmodule.dep")
!INCLUDE "sdlfontmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "sdlfontmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sdlfontmodule - Win32 Release" || "$(CFG)" == "sdlfontmodule - Win32 Debug"
SOURCE=.\sdlfontmodule.cpp

"$(INTDIR)\sdlfontmodule.obj" : $(SOURCE) "$(INTDIR)" ".\sdlfontmodule.h"


SOURCE=.\sdlfontmodule_auto.c

"$(INTDIR)\sdlfontmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\sdlfontmodule.h"


SOURCE=.\sdlfontmodule.spec

!IF  "$(CFG)" == "sdlfontmodule - Win32 Release"

InputPath=.\sdlfontmodule.spec
InputName=sdlfontmodule

".\sdlfontmodule.h"	".\sdlfontmodule_auto.c"	".\sdlfontmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "sdlfontmodule - Win32 Debug"

InputPath=.\sdlfontmodule.spec
InputName=sdlfontmodule

".\sdlfontmodule.h"	".\sdlfontmodule_auto.c"	".\sdlfontmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

