# Microsoft Developer Studio Generated NMAKE File, Based on y4moutputmodule.dsp
!IF "$(CFG)" == ""
CFG=y4moutputmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. y4moutputmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "y4moutputmodule - Win32 Release" && "$(CFG)" != "y4moutputmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "y4moutputmodule.mak" CFG="y4moutputmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "y4moutputmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "y4moutputmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "y4moutputmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\y4moutputmodule.dll"

!ELSE 

ALL : "libscale - Win32 Release" "libcolorconv - Win32 Release" "$(OUTDIR)\y4moutputmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libcolorconv - Win32 ReleaseCLEAN" "libscale - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\y4moutputmodule.obj"
	-@erase "$(INTDIR)\y4moutputmodule_auto.obj"
	-@erase "$(OUTDIR)\y4moutputmodule.dll"
	-@erase "$(OUTDIR)\y4moutputmodule.exp"
	-@erase "$(OUTDIR)\y4moutputmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libcolorconv" /I "../libscale" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "y4moutputmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\y4moutputmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\y4moutputmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\y4moutputmodule.pdb" /machine:I386 /def:".\y4moutputmodule.def" /out:"$(OUTDIR)\y4moutputmodule.dll" /implib:"$(OUTDIR)\y4moutputmodule.lib" 
DEF_FILE= \
	".\y4moutputmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\y4moutputmodule.obj" \
	"$(INTDIR)\y4moutputmodule_auto.obj" \
	"..\libcolorconv\Release\libcolorconv.lib" \
	"..\libscale\Release\libscale.lib"

"$(OUTDIR)\y4moutputmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\y4moutputmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Release" "libcolorconv - Win32 Release" "$(OUTDIR)\y4moutputmodule.dll"
   copy .\Release\y4moutputmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "y4moutputmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\y4moutputmodule_auto.c" ".\y4moutputmodule.h" ".\y4moutputmodule.def" "$(OUTDIR)\y4moutputmodule.dll"

!ELSE 

ALL : "libscale - Win32 Debug" "libcolorconv - Win32 Debug" ".\y4moutputmodule_auto.c" ".\y4moutputmodule.h" ".\y4moutputmodule.def" "$(OUTDIR)\y4moutputmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libcolorconv - Win32 DebugCLEAN" "libscale - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\y4moutputmodule.obj"
	-@erase "$(INTDIR)\y4moutputmodule_auto.obj"
	-@erase "$(OUTDIR)\y4moutputmodule.dll"
	-@erase "$(OUTDIR)\y4moutputmodule.exp"
	-@erase "$(OUTDIR)\y4moutputmodule.ilk"
	-@erase "$(OUTDIR)\y4moutputmodule.lib"
	-@erase "$(OUTDIR)\y4moutputmodule.pdb"
	-@erase "y4moutputmodule.def"
	-@erase "y4moutputmodule.h"
	-@erase "y4moutputmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libcolorconv" /I "../libscale" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "y4moutputmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\y4moutputmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\y4moutputmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\y4moutputmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\y4moutputmodule.def" /out:"$(OUTDIR)\y4moutputmodule.dll" /implib:"$(OUTDIR)\y4moutputmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\y4moutputmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\y4moutputmodule.obj" \
	"$(INTDIR)\y4moutputmodule_auto.obj" \
	"..\libcolorconv\Debug\libcolorconv.lib" \
	"..\libscale\Debug\libscale.lib"

"$(OUTDIR)\y4moutputmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\y4moutputmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Debug" "libcolorconv - Win32 Debug" ".\y4moutputmodule_auto.c" ".\y4moutputmodule.h" ".\y4moutputmodule.def" "$(OUTDIR)\y4moutputmodule.dll"
   copy .\Debug\y4moutputmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("y4moutputmodule.dep")
!INCLUDE "y4moutputmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "y4moutputmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "y4moutputmodule - Win32 Release" || "$(CFG)" == "y4moutputmodule - Win32 Debug"
SOURCE=.\y4moutputmodule.cpp

"$(INTDIR)\y4moutputmodule.obj" : $(SOURCE) "$(INTDIR)" ".\y4moutputmodule.h"


SOURCE=.\y4moutputmodule_auto.c

"$(INTDIR)\y4moutputmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\y4moutputmodule.h"


!IF  "$(CFG)" == "y4moutputmodule - Win32 Release"

"libcolorconv - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Release" 
   cd "..\yuv4mpeg2module"

"libcolorconv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\yuv4mpeg2module"

!ELSEIF  "$(CFG)" == "y4moutputmodule - Win32 Debug"

"libcolorconv - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Debug" 
   cd "..\yuv4mpeg2module"

"libcolorconv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\yuv4mpeg2module"

!ENDIF 

!IF  "$(CFG)" == "y4moutputmodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\yuv4mpeg2module"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\yuv4mpeg2module"

!ELSEIF  "$(CFG)" == "y4moutputmodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\yuv4mpeg2module"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\yuv4mpeg2module"

!ENDIF 

SOURCE=.\y4moutputmodule.spec

!IF  "$(CFG)" == "y4moutputmodule - Win32 Release"

InputPath=.\y4moutputmodule.spec
InputName=y4moutputmodule

".\y4moutputmodule.h"	".\y4moutputmodule_auto.c"	".\y4moutputmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "y4moutputmodule - Win32 Debug"

InputPath=.\y4moutputmodule.spec
InputName=y4moutputmodule

".\y4moutputmodule.h"	".\y4moutputmodule_auto.c"	".\y4moutputmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

