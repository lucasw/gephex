# Microsoft Developer Studio Generated NMAKE File, Based on frbinmodule.dsp
!IF "$(CFG)" == ""
CFG=frbinmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. frbinmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "frbinmodule - Win32 Release" && "$(CFG)" != "frbinmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "frbinmodule.mak" CFG="frbinmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "frbinmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "frbinmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "frbinmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\frbinmodule.dll"

!ELSE 

ALL : "libscale - Win32 Release" "libdshow - Win32 Release" "$(OUTDIR)\frbinmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libdshow - Win32 ReleaseCLEAN" "libscale - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bmpdriver.obj"
	-@erase "$(INTDIR)\ffmpegdriver.obj"
	-@erase "$(INTDIR)\framecache.obj"
	-@erase "$(INTDIR)\frbinmodule.obj"
	-@erase "$(INTDIR)\frbinmodule_auto.obj"
	-@erase "$(INTDIR)\sdlimagedriver.obj"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vfwdriver.obj"
	-@erase "$(OUTDIR)\frbinmodule.dll"
	-@erase "$(OUTDIR)\frbinmodule.exp"
	-@erase "$(OUTDIR)\frbinmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "$(DXSDK_DIR)\Include" /I "$(SDL_DIR)/include" /I "$(SDL_IMAGE_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libscale" /I "../libdshow" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /I "../../../contrib/ffmpeg/libavutil" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\frbinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\frbinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl.lib sdl_image.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib strmiids.lib quartz.lib avcodec.lib avformat.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\frbinmodule.pdb" /machine:I386 /def:".\frbinmodule.def" /out:"$(OUTDIR)\frbinmodule.dll" /implib:"$(OUTDIR)\frbinmodule.lib" /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" /libpath:"$(DXSDK_DIR)/Lib" /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec" 
DEF_FILE= \
	".\frbinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\bmpdriver.obj" \
	"$(INTDIR)\ffmpegdriver.obj" \
	"$(INTDIR)\framecache.obj" \
	"$(INTDIR)\frbinmodule.obj" \
	"$(INTDIR)\frbinmodule_auto.obj" \
	"$(INTDIR)\sdlimagedriver.obj" \
	"$(INTDIR)\timer.obj" \
	"$(INTDIR)\vfwdriver.obj" \
	"..\libdshow\Release\libdshow.lib" \
	"..\libscale\Release\libscale.lib"

"$(OUTDIR)\frbinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\frbinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Release" "libdshow - Win32 Release" "$(OUTDIR)\frbinmodule.dll"
   copy .\Release\frbinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\frbinmodule_auto.c" ".\frbinmodule.h" ".\frbinmodule.def" "$(OUTDIR)\frbinmodule.dll"

!ELSE 

ALL : "libscale - Win32 Debug" "libdshow - Win32 Debug" ".\frbinmodule_auto.c" ".\frbinmodule.h" ".\frbinmodule.def" "$(OUTDIR)\frbinmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libdshow - Win32 DebugCLEAN" "libscale - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bmpdriver.obj"
	-@erase "$(INTDIR)\ffmpegdriver.obj"
	-@erase "$(INTDIR)\framecache.obj"
	-@erase "$(INTDIR)\frbinmodule.obj"
	-@erase "$(INTDIR)\frbinmodule_auto.obj"
	-@erase "$(INTDIR)\sdlimagedriver.obj"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vfwdriver.obj"
	-@erase "$(OUTDIR)\frbinmodule.dll"
	-@erase "$(OUTDIR)\frbinmodule.exp"
	-@erase "$(OUTDIR)\frbinmodule.ilk"
	-@erase "$(OUTDIR)\frbinmodule.lib"
	-@erase "$(OUTDIR)\frbinmodule.pdb"
	-@erase "frbinmodule.def"
	-@erase "frbinmodule.h"
	-@erase "frbinmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "$(DXSDK_DIR)\Include" /I "$(SDL_DIR)/include" /I "$(SDL_IMAGE_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libscale" /I "../libdshow" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /I "../../../contrib/ffmpeg/libavutil" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\frbinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\frbinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=sdl.lib sdl_image.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib strmiids.lib quartz.lib avcodec.lib avformat.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\frbinmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\frbinmodule.def" /out:"$(OUTDIR)\frbinmodule.dll" /implib:"$(OUTDIR)\frbinmodule.lib" /pdbtype:sept /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" /libpath:"$(DXSDK_DIR)/Lib" /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec" 
DEF_FILE= \
	".\frbinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\bmpdriver.obj" \
	"$(INTDIR)\ffmpegdriver.obj" \
	"$(INTDIR)\framecache.obj" \
	"$(INTDIR)\frbinmodule.obj" \
	"$(INTDIR)\frbinmodule_auto.obj" \
	"$(INTDIR)\sdlimagedriver.obj" \
	"$(INTDIR)\timer.obj" \
	"$(INTDIR)\vfwdriver.obj" \
	"..\libdshow\Debug\libdshow.lib" \
	"..\libscale\Debug\libscale.lib"

"$(OUTDIR)\frbinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\frbinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Debug" "libdshow - Win32 Debug" ".\frbinmodule_auto.c" ".\frbinmodule.h" ".\frbinmodule.def" "$(OUTDIR)\frbinmodule.dll"
   copy .\Debug\frbinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("frbinmodule.dep")
!INCLUDE "frbinmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "frbinmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "frbinmodule - Win32 Release" || "$(CFG)" == "frbinmodule - Win32 Debug"
SOURCE=.\bmpdriver.cpp

"$(INTDIR)\bmpdriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ffmpegdriver.cpp

"$(INTDIR)\ffmpegdriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\framecache.cpp

"$(INTDIR)\framecache.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\frbinmodule.cpp

"$(INTDIR)\frbinmodule.obj" : $(SOURCE) "$(INTDIR)" ".\frbinmodule.h"


SOURCE=.\frbinmodule_auto.c

"$(INTDIR)\frbinmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\frbinmodule.h"


SOURCE=.\sdlimagedriver.cpp

"$(INTDIR)\sdlimagedriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\timer.cpp

"$(INTDIR)\timer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vfwdriver.cpp

"$(INTDIR)\vfwdriver.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "frbinmodule - Win32 Release"

"libdshow - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Release" 
   cd "..\frbinmodule"

"libdshow - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Release" RECURSE=1 CLEAN 
   cd "..\frbinmodule"

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

"libdshow - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Debug" 
   cd "..\frbinmodule"

"libdshow - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\frbinmodule"

!ENDIF 

!IF  "$(CFG)" == "frbinmodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\frbinmodule"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\frbinmodule"

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\frbinmodule"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\frbinmodule"

!ENDIF 

SOURCE=.\frbinmodule.spec

!IF  "$(CFG)" == "frbinmodule - Win32 Release"

InputPath=.\frbinmodule.spec
InputName=frbinmodule

".\frbinmodule.h"	".\frbinmodule_auto.c"	".\frbinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

InputPath=.\frbinmodule.spec
InputName=frbinmodule

".\frbinmodule.h"	".\frbinmodule_auto.c"	".\frbinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

