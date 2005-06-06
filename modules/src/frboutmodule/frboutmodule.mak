# Microsoft Developer Studio Generated NMAKE File, Based on frboutmodule.dsp
!IF "$(CFG)" == ""
CFG=frboutmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. frboutmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "frboutmodule - Win32 Release" && "$(CFG)" != "frboutmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "frboutmodule.mak" CFG="frboutmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "frboutmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "frboutmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "frboutmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\frboutmodule_auto.c" ".\frboutmodule.h" ".\frboutmodule.def" "$(OUTDIR)\frboutmodule.dll"

!ELSE 

ALL : "libscale - Win32 Release" ".\frboutmodule_auto.c" ".\frboutmodule.h" ".\frboutmodule.def" "$(OUTDIR)\frboutmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\frboutmodule.obj"
	-@erase "$(INTDIR)\frboutmodule_auto.obj"
	-@erase "$(INTDIR)\gdioutput.obj"
	-@erase "$(INTDIR)\multimonitor.obj"
	-@erase "$(INTDIR)\sdloutput.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\frboutmodule.dll"
	-@erase "$(OUTDIR)\frboutmodule.exp"
	-@erase "$(OUTDIR)\frboutmodule.lib"
	-@erase "frboutmodule.def"
	-@erase "frboutmodule.h"
	-@erase "frboutmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "$(SDL_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /I "../libscale" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "_WINDOWS" /D "_USRDLL" /D "frboutmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /D snprintf=_snprintf /Fp"$(INTDIR)\frboutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\frboutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib glu32.lib opengl32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\frboutmodule.pdb" /machine:I386 /def:".\frboutmodule.def" /out:"$(OUTDIR)\frboutmodule.dll" /implib:"$(OUTDIR)\frboutmodule.lib" /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" 
DEF_FILE= \
	".\frboutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\frboutmodule.obj" \
	"$(INTDIR)\frboutmodule_auto.obj" \
	"$(INTDIR)\gdioutput.obj" \
	"$(INTDIR)\multimonitor.obj" \
	"$(INTDIR)\sdloutput.obj" \
	"$(INTDIR)\slist.obj" \
	"..\libscale\Release\libscale.lib"

"$(OUTDIR)\frboutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\frboutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Release" ".\frboutmodule_auto.c" ".\frboutmodule.h" ".\frboutmodule.def" "$(OUTDIR)\frboutmodule.dll"
   copy .\Release\frboutmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "frboutmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\frboutmodule.dll"

!ELSE 

ALL : "libscale - Win32 Debug" "$(OUTDIR)\frboutmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\frboutmodule.obj"
	-@erase "$(INTDIR)\frboutmodule_auto.obj"
	-@erase "$(INTDIR)\gdioutput.obj"
	-@erase "$(INTDIR)\multimonitor.obj"
	-@erase "$(INTDIR)\sdloutput.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\frboutmodule.dll"
	-@erase "$(OUTDIR)\frboutmodule.exp"
	-@erase "$(OUTDIR)\frboutmodule.ilk"
	-@erase "$(OUTDIR)\frboutmodule.lib"
	-@erase "$(OUTDIR)\frboutmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "$(SDL_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /I "../libscale" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "frboutmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /D snprintf=_snprintf /Fp"$(INTDIR)\frboutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\frboutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl_image.lib sdl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib glu32.lib opengl32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\frboutmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\frboutmodule.def" /out:"$(OUTDIR)\frboutmodule.dll" /implib:"$(OUTDIR)\frboutmodule.lib" /pdbtype:sept /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" 
DEF_FILE= \
	".\frboutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\frboutmodule.obj" \
	"$(INTDIR)\frboutmodule_auto.obj" \
	"$(INTDIR)\gdioutput.obj" \
	"$(INTDIR)\multimonitor.obj" \
	"$(INTDIR)\sdloutput.obj" \
	"$(INTDIR)\slist.obj" \
	"..\libscale\Debug\libscale.lib"

"$(OUTDIR)\frboutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\frboutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Debug" "$(OUTDIR)\frboutmodule.dll"
   copy .\Debug\frboutmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("frboutmodule.dep")
!INCLUDE "frboutmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "frboutmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "frboutmodule - Win32 Release" || "$(CFG)" == "frboutmodule - Win32 Debug"
SOURCE=.\frboutmodule.c

!IF  "$(CFG)" == "frboutmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "$(SDL_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /I "../libscale" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "_WINDOWS" /D "_USRDLL" /D "frboutmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /D snprintf=_snprintf /Fp"$(INTDIR)\frboutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\frboutmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "frboutmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "$(SDL_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../" /I "../../../engine/src/engine" /I "../../../types/src/framebuffertype" /I "../../../util/include" /I "../libscale" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "frboutmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /D snprintf=_snprintf /Fp"$(INTDIR)\frboutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\frboutmodule.obj" : $(SOURCE) "$(INTDIR)" ".\frboutmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\frboutmodule_auto.c

"$(INTDIR)\frboutmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gdioutput.c

"$(INTDIR)\gdioutput.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\multimonitor.c

"$(INTDIR)\multimonitor.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\sdloutput.c

"$(INTDIR)\sdloutput.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\slist.c

"$(INTDIR)\slist.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "frboutmodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\frboutmodule"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\frboutmodule"

!ELSEIF  "$(CFG)" == "frboutmodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\frboutmodule"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\frboutmodule"

!ENDIF 

SOURCE=.\frboutmodule.spec

!IF  "$(CFG)" == "frboutmodule - Win32 Release"

InputPath=.\frboutmodule.spec

".\frboutmodule.h"	".\frboutmodule_auto.c"	".\frboutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c frboutmodule.spec 
	python ../../pluc.py h frboutmodule.spec 
	python ../../pluc.py def frboutmodule.spec
<< 
	

!ELSEIF  "$(CFG)" == "frboutmodule - Win32 Debug"

InputPath=.\frboutmodule.spec

".\frboutmodule.h"	".\frboutmodule_auto.c"	".\frboutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../pluc.py c frboutmodule.spec 
	python ../../pluc.py h frboutmodule.spec 
	python ../../pluc.py def frboutmodule.spec
<< 
	

!ENDIF 


!ENDIF 

