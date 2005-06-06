# Microsoft Developer Studio Generated NMAKE File, Based on effectvdiffmodule.dsp
!IF "$(CFG)" == ""
CFG=effectvdiffmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvdiffmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvdiffmodule - Win32 Release" && "$(CFG)" != "effectvdiffmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvdiffmodule.mak" CFG="effectvdiffmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvdiffmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvdiffmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "effectvdiffmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdiffmodule.obj"
	-@erase "$(INTDIR)\effectvdiffmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvdiffmodule.dll"
	-@erase "$(OUTDIR)\effectvdiffmodule.exp"
	-@erase "$(OUTDIR)\effectvdiffmodule.lib"
	-@erase "effectvdiffmodule.def"
	-@erase "effectvdiffmodule.h"
	-@erase "effectvdiffmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdiffmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdiffmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdiffmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvdiffmodule.pdb" /machine:I386 /def:".\effectvdiffmodule.def" /out:"$(OUTDIR)\effectvdiffmodule.dll" /implib:"$(OUTDIR)\effectvdiffmodule.lib" 
DEF_FILE= \
	".\effectvdiffmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdiffmodule.obj" \
	"$(INTDIR)\effectvdiffmodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvdiffmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvdiffmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"
   copy .\Release\effectvdiffmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvdiffmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdiffmodule.obj"
	-@erase "$(INTDIR)\effectvdiffmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvdiffmodule.dll"
	-@erase "$(OUTDIR)\effectvdiffmodule.exp"
	-@erase "$(OUTDIR)\effectvdiffmodule.ilk"
	-@erase "$(OUTDIR)\effectvdiffmodule.lib"
	-@erase "$(OUTDIR)\effectvdiffmodule.pdb"
	-@erase "effectvdiffmodule.def"
	-@erase "effectvdiffmodule.h"
	-@erase "effectvdiffmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdiffmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdiffmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdiffmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvdiffmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvdiffmodule.def" /out:"$(OUTDIR)\effectvdiffmodule.dll" /implib:"$(OUTDIR)\effectvdiffmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvdiffmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdiffmodule.obj" \
	"$(INTDIR)\effectvdiffmodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvdiffmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvdiffmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" ".\effectvdiffmodule_auto.c" ".\effectvdiffmodule.h" ".\effectvdiffmodule.def" "$(OUTDIR)\effectvdiffmodule.dll"
   copy .\Debug\effectvdiffmodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("effectvdiffmodule.dep")
!INCLUDE "effectvdiffmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvdiffmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvdiffmodule - Win32 Release" || "$(CFG)" == "effectvdiffmodule - Win32 Debug"
SOURCE=.\effectvdiffmodule.c

!IF  "$(CFG)" == "effectvdiffmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdiffmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdiffmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvdiffmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvdiffmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdiffmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdiffmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvdiffmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvdiffmodule_auto.c

"$(INTDIR)\effectvdiffmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "effectvdiffmodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvdiffmodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvdiffmodule"

!ELSEIF  "$(CFG)" == "effectvdiffmodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvdiffmodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvdiffmodule"

!ENDIF 

SOURCE=.\effectvdiffmodule.spec

!IF  "$(CFG)" == "effectvdiffmodule - Win32 Release"

InputPath=.\effectvdiffmodule.spec
InputName=effectvdiffmodule

".\effectvdiffmodule.h"	".\effectvdiffmodule_auto.c"	".\effectvdiffmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvdiffmodule - Win32 Debug"

InputPath=.\effectvdiffmodule.spec
InputName=effectvdiffmodule

".\effectvdiffmodule.h"	".\effectvdiffmodule_auto.c"	".\effectvdiffmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

