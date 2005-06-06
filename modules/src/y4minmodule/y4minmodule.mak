# Microsoft Developer Studio Generated NMAKE File, Based on y4minmodule.dsp
!IF "$(CFG)" == ""
CFG=y4minmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. y4minmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "y4minmodule - Win32 Release" && "$(CFG)" != "y4minmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "y4minmodule.mak" CFG="y4minmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "y4minmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "y4minmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "y4minmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\y4minmodule_auto.c" ".\y4minmodule.h" ".\y4minmodule.def" "$(OUTDIR)\y4minmodule.dll"

!ELSE 

ALL : "libscale - Win32 Release" "libcolorconv - Win32 Release" ".\y4minmodule_auto.c" ".\y4minmodule.h" ".\y4minmodule.def" "$(OUTDIR)\y4minmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libcolorconv - Win32 ReleaseCLEAN" "libscale - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\y4minmodule.obj"
	-@erase "$(INTDIR)\y4minmodule_auto.obj"
	-@erase "$(OUTDIR)\y4minmodule.dll"
	-@erase "$(OUTDIR)\y4minmodule.exp"
	-@erase "$(OUTDIR)\y4minmodule.lib"
	-@erase "y4minmodule.def"
	-@erase "y4minmodule.h"
	-@erase "y4minmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libcolorconv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "y4minmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\y4minmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\y4minmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\y4minmodule.pdb" /machine:I386 /def:".\y4minmodule.def" /out:"$(OUTDIR)\y4minmodule.dll" /implib:"$(OUTDIR)\y4minmodule.lib" 
DEF_FILE= \
	".\y4minmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\y4minmodule_auto.obj" \
	"$(INTDIR)\y4minmodule.obj" \
	"..\libcolorconv\Release\libcolorconv.lib" \
	"..\libscale\Release\libscale.lib"

"$(OUTDIR)\y4minmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\y4minmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Release" "libcolorconv - Win32 Release" ".\y4minmodule_auto.c" ".\y4minmodule.h" ".\y4minmodule.def" "$(OUTDIR)\y4minmodule.dll"
   copy .\Release\y4minmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "y4minmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\y4minmodule.dll"

!ELSE 

ALL : "libscale - Win32 Debug" "libcolorconv - Win32 Debug" "$(OUTDIR)\y4minmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libcolorconv - Win32 DebugCLEAN" "libscale - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\y4minmodule.obj"
	-@erase "$(INTDIR)\y4minmodule_auto.obj"
	-@erase "$(OUTDIR)\y4minmodule.dll"
	-@erase "$(OUTDIR)\y4minmodule.exp"
	-@erase "$(OUTDIR)\y4minmodule.ilk"
	-@erase "$(OUTDIR)\y4minmodule.lib"
	-@erase "$(OUTDIR)\y4minmodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libcolorconv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "y4minmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\y4minmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\y4minmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\y4minmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\y4minmodule.def" /out:"$(OUTDIR)\y4minmodule.dll" /implib:"$(OUTDIR)\y4minmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\y4minmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\y4minmodule_auto.obj" \
	"$(INTDIR)\y4minmodule.obj" \
	"..\libcolorconv\Debug\libcolorconv.lib" \
	"..\libscale\Debug\libscale.lib"

"$(OUTDIR)\y4minmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\y4minmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libscale - Win32 Debug" "libcolorconv - Win32 Debug" "$(OUTDIR)\y4minmodule.dll"
   copy .\Debug\y4minmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("y4minmodule.dep")
!INCLUDE "y4minmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "y4minmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "y4minmodule - Win32 Release" || "$(CFG)" == "y4minmodule - Win32 Debug"
SOURCE=.\y4minmodule.cpp

"$(INTDIR)\y4minmodule.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\y4minmodule_auto.c

"$(INTDIR)\y4minmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "y4minmodule - Win32 Release"

"libcolorconv - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Release" 
   cd "..\y4minmodule"

"libcolorconv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\y4minmodule"

!ELSEIF  "$(CFG)" == "y4minmodule - Win32 Debug"

"libcolorconv - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Debug" 
   cd "..\y4minmodule"

"libcolorconv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libcolorconv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libcolorconv.mak" CFG="libcolorconv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\y4minmodule"

!ENDIF 

!IF  "$(CFG)" == "y4minmodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\y4minmodule"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\y4minmodule"

!ELSEIF  "$(CFG)" == "y4minmodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\y4minmodule"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\y4minmodule"

!ENDIF 

SOURCE=.\y4minmodule.spec

!IF  "$(CFG)" == "y4minmodule - Win32 Release"

InputPath=.\y4minmodule.spec
InputName=y4minmodule

".\y4minmodule.h"	".\y4minmodule_auto.c"	".\y4minmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "y4minmodule - Win32 Debug"

InputPath=.\y4minmodule.spec
InputName=y4minmodule

".\y4minmodule.h"	".\y4minmodule_auto.c"	".\y4minmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

