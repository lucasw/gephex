# Microsoft Developer Studio Generated NMAKE File, Based on effectvquarkmodule.dsp
!IF "$(CFG)" == ""
CFG=effectvquarkmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvquarkmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvquarkmodule - Win32 Release" && "$(CFG)" != "effectvquarkmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvquarkmodule.mak" CFG="effectvquarkmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvquarkmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvquarkmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "effectvquarkmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\effectvquarkmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" "$(OUTDIR)\effectvquarkmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvquarkmodule.obj"
	-@erase "$(INTDIR)\effectvquarkmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvquarkmodule.dll"
	-@erase "$(OUTDIR)\effectvquarkmodule.exp"
	-@erase "$(OUTDIR)\effectvquarkmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvquarkmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvquarkmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvquarkmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvquarkmodule.pdb" /machine:I386 /def:".\effectvquarkmodule.def" /out:"$(OUTDIR)\effectvquarkmodule.dll" /implib:"$(OUTDIR)\effectvquarkmodule.lib" 
DEF_FILE= \
	".\effectvquarkmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvquarkmodule.obj" \
	"$(INTDIR)\effectvquarkmodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvquarkmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvquarkmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" "$(OUTDIR)\effectvquarkmodule.dll"
   copy .\Release\effectvquarkmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvquarkmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvquarkmodule_auto.c" ".\effectvquarkmodule.h" ".\effectvquarkmodule.def" "$(OUTDIR)\effectvquarkmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" ".\effectvquarkmodule_auto.c" ".\effectvquarkmodule.h" ".\effectvquarkmodule.def" "$(OUTDIR)\effectvquarkmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvquarkmodule.obj"
	-@erase "$(INTDIR)\effectvquarkmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvquarkmodule.dll"
	-@erase "$(OUTDIR)\effectvquarkmodule.exp"
	-@erase "$(OUTDIR)\effectvquarkmodule.ilk"
	-@erase "$(OUTDIR)\effectvquarkmodule.lib"
	-@erase "$(OUTDIR)\effectvquarkmodule.pdb"
	-@erase "effectvquarkmodule.def"
	-@erase "effectvquarkmodule.h"
	-@erase "effectvquarkmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvquarkmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvquarkmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvquarkmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvquarkmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvquarkmodule.def" /out:"$(OUTDIR)\effectvquarkmodule.dll" /implib:"$(OUTDIR)\effectvquarkmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvquarkmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvquarkmodule.obj" \
	"$(INTDIR)\effectvquarkmodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvquarkmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvquarkmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" ".\effectvquarkmodule_auto.c" ".\effectvquarkmodule.h" ".\effectvquarkmodule.def" "$(OUTDIR)\effectvquarkmodule.dll"
   copy .\Debug\effectvquarkmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("effectvquarkmodule.dep")
!INCLUDE "effectvquarkmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvquarkmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvquarkmodule - Win32 Release" || "$(CFG)" == "effectvquarkmodule - Win32 Debug"
SOURCE=.\effectvquarkmodule.c

!IF  "$(CFG)" == "effectvquarkmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvquarkmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvquarkmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvquarkmodule.obj" : $(SOURCE) "$(INTDIR)" ".\effectvquarkmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvquarkmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvquarkmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvquarkmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvquarkmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvquarkmodule_auto.c

"$(INTDIR)\effectvquarkmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\effectvquarkmodule.h"


SOURCE=.\quark.c

!IF  "$(CFG)" == "effectvquarkmodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvquarkmodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvquarkmodule"

!ELSEIF  "$(CFG)" == "effectvquarkmodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvquarkmodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvquarkmodule"

!ENDIF 

SOURCE=.\effectvquarkmodule.spec

!IF  "$(CFG)" == "effectvquarkmodule - Win32 Release"

InputPath=.\effectvquarkmodule.spec
InputName=effectvquarkmodule

".\effectvquarkmodule.h"	".\effectvquarkmodule_auto.c"	".\effectvquarkmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvquarkmodule - Win32 Debug"

InputPath=.\effectvquarkmodule.spec
InputName=effectvquarkmodule

".\effectvquarkmodule.h"	".\effectvquarkmodule_auto.c"	".\effectvquarkmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

