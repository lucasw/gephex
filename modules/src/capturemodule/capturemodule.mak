# Microsoft Developer Studio Generated NMAKE File, Based on capturemodule.dsp
!IF "$(CFG)" == ""
CFG=capturemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. capturemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "capturemodule - Win32 Release" && "$(CFG)" != "capturemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "capturemodule.mak" CFG="capturemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "capturemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "capturemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "capturemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\capturemodule.dll"

!ELSE 

ALL : "libdshow - Win32 Release" "libscale - Win32 Release" "$(OUTDIR)\capturemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 ReleaseCLEAN" "libdshow - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\capturemodule.obj"
	-@erase "$(INTDIR)\capturemodule_auto.obj"
	-@erase "$(INTDIR)\dshowcapturedriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\capturemodule.dll"
	-@erase "$(OUTDIR)\capturemodule.exp"
	-@erase "$(OUTDIR)\capturemodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GR /GX /O2 /Ob2 /I "$(DXSDK_DIR)\Include" /I "../libscale" /I "../libdshow" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "capturemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\capturemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\capturemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib strmiids.lib quartz.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\capturemodule.pdb" /machine:I386 /def:".\capturemodule.def" /out:"$(OUTDIR)\capturemodule.dll" /implib:"$(OUTDIR)\capturemodule.lib" /libpath:"$(DXSDK_DIR)/Lib" 
DEF_FILE= \
	".\capturemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\capturemodule.obj" \
	"$(INTDIR)\capturemodule_auto.obj" \
	"$(INTDIR)\dshowcapturedriver.obj" \
	"..\libscale\Release\libscale.lib" \
	"..\libdshow\Release\libdshow.lib"

"$(OUTDIR)\capturemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\capturemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libdshow - Win32 Release" "libscale - Win32 Release" "$(OUTDIR)\capturemodule.dll"
   copy .\Release\capturemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "capturemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\capturemodule_auto.c" ".\capturemodule.h" ".\capturemodule.def" "$(OUTDIR)\capturemodule.dll"

!ELSE 

ALL : "libdshow - Win32 Debug" "libscale - Win32 Debug" ".\capturemodule_auto.c" ".\capturemodule.h" ".\capturemodule.def" "$(OUTDIR)\capturemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libscale - Win32 DebugCLEAN" "libdshow - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\capturemodule.obj"
	-@erase "$(INTDIR)\capturemodule_auto.obj"
	-@erase "$(INTDIR)\dshowcapturedriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\capturemodule.dll"
	-@erase "$(OUTDIR)\capturemodule.exp"
	-@erase "$(OUTDIR)\capturemodule.ilk"
	-@erase "$(OUTDIR)\capturemodule.lib"
	-@erase "$(OUTDIR)\capturemodule.pdb"
	-@erase "capturemodule.def"
	-@erase "capturemodule.h"
	-@erase "capturemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(DXSDK_DIR)\Include" /I "../libscale" /I "../libdshow" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "capturemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\capturemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\capturemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib strmiids.lib quartz.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\capturemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\capturemodule.def" /out:"$(OUTDIR)\capturemodule.dll" /implib:"$(OUTDIR)\capturemodule.lib" /pdbtype:sept /libpath:"$(DXSDK_DIR)/Lib" 
DEF_FILE= \
	".\capturemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\capturemodule.obj" \
	"$(INTDIR)\capturemodule_auto.obj" \
	"$(INTDIR)\dshowcapturedriver.obj" \
	"..\libscale\Debug\libscale.lib" \
	"..\libdshow\Debug\libdshow.lib"

"$(OUTDIR)\capturemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\capturemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libdshow - Win32 Debug" "libscale - Win32 Debug" ".\capturemodule_auto.c" ".\capturemodule.h" ".\capturemodule.def" "$(OUTDIR)\capturemodule.dll"
   copy .\Debug\capturemodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("capturemodule.dep")
!INCLUDE "capturemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "capturemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "capturemodule - Win32 Release" || "$(CFG)" == "capturemodule - Win32 Debug"
SOURCE=.\capturemodule.cpp

"$(INTDIR)\capturemodule.obj" : $(SOURCE) "$(INTDIR)" ".\capturemodule.h"


SOURCE=.\capturemodule_auto.c

"$(INTDIR)\capturemodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\capturemodule.h"


SOURCE=.\dshowcapturedriver.cpp

"$(INTDIR)\dshowcapturedriver.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "capturemodule - Win32 Release"

"libscale - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" 
   cd "..\capturemodule"

"libscale - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Release" RECURSE=1 CLEAN 
   cd "..\capturemodule"

!ELSEIF  "$(CFG)" == "capturemodule - Win32 Debug"

"libscale - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" 
   cd "..\capturemodule"

"libscale - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libscale"
   $(MAKE) /$(MAKEFLAGS) /F ".\libscale.mak" CFG="libscale - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\capturemodule"

!ENDIF 

!IF  "$(CFG)" == "capturemodule - Win32 Release"

"libdshow - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Release" 
   cd "..\capturemodule"

"libdshow - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Release" RECURSE=1 CLEAN 
   cd "..\capturemodule"

!ELSEIF  "$(CFG)" == "capturemodule - Win32 Debug"

"libdshow - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Debug" 
   cd "..\capturemodule"

"libdshow - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libdshow"
   $(MAKE) /$(MAKEFLAGS) /F ".\libdshow.mak" CFG="libdshow - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\capturemodule"

!ENDIF 

SOURCE=.\capturemodule.spec

!IF  "$(CFG)" == "capturemodule - Win32 Release"

InputPath=.\capturemodule.spec
InputName=capturemodule

".\capturemodule.h"	".\capturemodule_auto.c"	".\capturemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "capturemodule - Win32 Debug"

InputPath=.\capturemodule.spec
InputName=capturemodule

".\capturemodule.h"	".\capturemodule_auto.c"	".\capturemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

