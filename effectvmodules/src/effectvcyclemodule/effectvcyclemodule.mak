# Microsoft Developer Studio Generated NMAKE File, Based on effectvcyclemodule.dsp
!IF "$(CFG)" == ""
CFG=effectvcyclemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvcyclemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvcyclemodule - Win32 Release" && "$(CFG)" != "effectvcyclemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvcyclemodule.mak" CFG="effectvcyclemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvcyclemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvcyclemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "effectvcyclemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\effectvcyclemodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" "$(OUTDIR)\effectvcyclemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvcyclemodule.obj"
	-@erase "$(INTDIR)\effectvcyclemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvcyclemodule.dll"
	-@erase "$(OUTDIR)\effectvcyclemodule.exp"
	-@erase "$(OUTDIR)\effectvcyclemodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvcyclemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvcyclemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvcyclemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvcyclemodule.pdb" /machine:I386 /def:".\effectvcyclemodule.def" /out:"$(OUTDIR)\effectvcyclemodule.dll" /implib:"$(OUTDIR)\effectvcyclemodule.lib" 
DEF_FILE= \
	".\effectvcyclemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvcyclemodule.obj" \
	"$(INTDIR)\effectvcyclemodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvcyclemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvcyclemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" "$(OUTDIR)\effectvcyclemodule.dll"
   copy .\Release\effectvcyclemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvcyclemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvcyclemodule_auto.c" ".\effectvcyclemodule.h" ".\effectvcyclemodule.def" "$(OUTDIR)\effectvcyclemodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" ".\effectvcyclemodule_auto.c" ".\effectvcyclemodule.h" ".\effectvcyclemodule.def" "$(OUTDIR)\effectvcyclemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvcyclemodule.obj"
	-@erase "$(INTDIR)\effectvcyclemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvcyclemodule.dll"
	-@erase "$(OUTDIR)\effectvcyclemodule.exp"
	-@erase "$(OUTDIR)\effectvcyclemodule.ilk"
	-@erase "$(OUTDIR)\effectvcyclemodule.lib"
	-@erase "$(OUTDIR)\effectvcyclemodule.pdb"
	-@erase "effectvcyclemodule.def"
	-@erase "effectvcyclemodule.h"
	-@erase "effectvcyclemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvcyclemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvcyclemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvcyclemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvcyclemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvcyclemodule.def" /out:"$(OUTDIR)\effectvcyclemodule.dll" /implib:"$(OUTDIR)\effectvcyclemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvcyclemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvcyclemodule.obj" \
	"$(INTDIR)\effectvcyclemodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvcyclemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvcyclemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" ".\effectvcyclemodule_auto.c" ".\effectvcyclemodule.h" ".\effectvcyclemodule.def" "$(OUTDIR)\effectvcyclemodule.dll"
   copy .\Debug\effectvcyclemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("effectvcyclemodule.dep")
!INCLUDE "effectvcyclemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvcyclemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvcyclemodule - Win32 Release" || "$(CFG)" == "effectvcyclemodule - Win32 Debug"
SOURCE=.\effectvcyclemodule.c

!IF  "$(CFG)" == "effectvcyclemodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvcyclemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvcyclemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvcyclemodule.obj" : $(SOURCE) "$(INTDIR)" ".\effectvcyclemodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvcyclemodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvcyclemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvcyclemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvcyclemodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvcyclemodule_auto.c

"$(INTDIR)\effectvcyclemodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\effectvcyclemodule.h"


SOURCE=.\cycle.c

!IF  "$(CFG)" == "effectvcyclemodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvcyclemodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvcyclemodule"

!ELSEIF  "$(CFG)" == "effectvcyclemodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvcyclemodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvcyclemodule"

!ENDIF 

SOURCE=.\effectvcyclemodule.spec

!IF  "$(CFG)" == "effectvcyclemodule - Win32 Release"

InputPath=.\effectvcyclemodule.spec
InputName=effectvcyclemodule

".\effectvcyclemodule.h"	".\effectvcyclemodule_auto.c"	".\effectvcyclemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvcyclemodule - Win32 Debug"

InputPath=.\effectvcyclemodule.spec
InputName=effectvcyclemodule

".\effectvcyclemodule.h"	".\effectvcyclemodule_auto.c"	".\effectvcyclemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

