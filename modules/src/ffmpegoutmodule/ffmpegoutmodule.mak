# Microsoft Developer Studio Generated NMAKE File, Based on ffmpegoutmodule.dsp
!IF "$(CFG)" == ""
CFG=ffmpegoutmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ffmpegoutmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ffmpegoutmodule - Win32 Release" && "$(CFG)" != "ffmpegoutmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ffmpegoutmodule.mak" CFG="ffmpegoutmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ffmpegoutmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ffmpegoutmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ffmpegoutmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\ffmpegoutmodule_auto.c" ".\ffmpegoutmodule.h" ".\ffmpegoutmodule.def" "$(OUTDIR)\ffmpegoutmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ffmpegoutmodule.obj"
	-@erase "$(INTDIR)\ffmpegoutmodule_auto.obj"
	-@erase "$(INTDIR)\ffmpegwriter.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ffmpegoutmodule.dll"
	-@erase "$(OUTDIR)\ffmpegoutmodule.exp"
	-@erase "$(OUTDIR)\ffmpegoutmodule.lib"
	-@erase "ffmpegoutmodule.def"
	-@erase "ffmpegoutmodule.h"
	-@erase "ffmpegoutmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ffmpegoutmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ffmpegoutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ffmpegoutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib avcodec.lib avformat.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ffmpegoutmodule.pdb" /machine:I386 /def:".\ffmpegoutmodule.def" /out:"$(OUTDIR)\ffmpegoutmodule.dll" /implib:"$(OUTDIR)\ffmpegoutmodule.lib" /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec" 
DEF_FILE= \
	".\ffmpegoutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ffmpegoutmodule_auto.obj" \
	"$(INTDIR)\ffmpegoutmodule.obj" \
	"$(INTDIR)\ffmpegwriter.obj"

"$(OUTDIR)\ffmpegoutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\ffmpegoutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\ffmpegoutmodule_auto.c" ".\ffmpegoutmodule.h" ".\ffmpegoutmodule.def" "$(OUTDIR)\ffmpegoutmodule.dll"
   copy .\Release\ffmpegoutmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ffmpegoutmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ffmpegoutmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\ffmpegoutmodule.obj"
	-@erase "$(INTDIR)\ffmpegoutmodule_auto.obj"
	-@erase "$(INTDIR)\ffmpegwriter.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ffmpegoutmodule.dll"
	-@erase "$(OUTDIR)\ffmpegoutmodule.exp"
	-@erase "$(OUTDIR)\ffmpegoutmodule.ilk"
	-@erase "$(OUTDIR)\ffmpegoutmodule.lib"
	-@erase "$(OUTDIR)\ffmpegoutmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ffmpegoutmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\ffmpegoutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ffmpegoutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib avcodec.lib avformat.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ffmpegoutmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\ffmpegoutmodule.def" /out:"$(OUTDIR)\ffmpegoutmodule.dll" /implib:"$(OUTDIR)\ffmpegoutmodule.lib" /pdbtype:sept /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec" 
DEF_FILE= \
	".\ffmpegoutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\ffmpegoutmodule_auto.obj" \
	"$(INTDIR)\ffmpegoutmodule.obj" \
	"$(INTDIR)\ffmpegwriter.obj"

"$(OUTDIR)\ffmpegoutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\ffmpegoutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ffmpegoutmodule.dll"
   copy .\Debug\ffmpegoutmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("ffmpegoutmodule.dep")
!INCLUDE "ffmpegoutmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "ffmpegoutmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ffmpegoutmodule - Win32 Release" || "$(CFG)" == "ffmpegoutmodule - Win32 Debug"
SOURCE=.\ffmpegoutmodule.cpp

"$(INTDIR)\ffmpegoutmodule.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ffmpegoutmodule_auto.c

"$(INTDIR)\ffmpegoutmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ffmpegwriter.cpp

"$(INTDIR)\ffmpegwriter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ffmpegoutmodule.spec

!IF  "$(CFG)" == "ffmpegoutmodule - Win32 Release"

InputPath=.\ffmpegoutmodule.spec
InputName=ffmpegoutmodule

".\ffmpegoutmodule.h"	".\ffmpegoutmodule_auto.c"	".\ffmpegoutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "ffmpegoutmodule - Win32 Debug"

InputPath=.\ffmpegoutmodule.spec
InputName=ffmpegoutmodule

".\ffmpegoutmodule.h"	".\ffmpegoutmodule_auto.c"	".\ffmpegoutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

