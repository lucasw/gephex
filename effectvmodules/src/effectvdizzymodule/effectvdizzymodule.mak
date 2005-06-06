# Microsoft Developer Studio Generated NMAKE File, Based on effectvdizzymodule.dsp
!IF "$(CFG)" == ""
CFG=effectvdizzymodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvdizzymodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvdizzymodule - Win32 Release" && "$(CFG)" != "effectvdizzymodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvdizzymodule.mak" CFG="effectvdizzymodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvdizzymodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvdizzymodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "effectvdizzymodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdizzymodule_auto.c" ".\effectvdizzymodule.h" ".\effectvdizzymodule.def" "$(OUTDIR)\effectvdizzymodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" ".\effectvdizzymodule_auto.c" ".\effectvdizzymodule.h" ".\effectvdizzymodule.def" "$(OUTDIR)\effectvdizzymodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdizzymodule.obj"
	-@erase "$(INTDIR)\effectvdizzymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvdizzymodule.dll"
	-@erase "$(OUTDIR)\effectvdizzymodule.exp"
	-@erase "$(OUTDIR)\effectvdizzymodule.lib"
	-@erase "effectvdizzymodule.def"
	-@erase "effectvdizzymodule.h"
	-@erase "effectvdizzymodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdizzymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdizzymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdizzymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvdizzymodule.pdb" /machine:I386 /def:".\effectvdizzymodule.def" /out:"$(OUTDIR)\effectvdizzymodule.dll" /implib:"$(OUTDIR)\effectvdizzymodule.lib" 
DEF_FILE= \
	".\effectvdizzymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdizzymodule.obj" \
	"$(INTDIR)\effectvdizzymodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvdizzymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvdizzymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" ".\effectvdizzymodule_auto.c" ".\effectvdizzymodule.h" ".\effectvdizzymodule.def" "$(OUTDIR)\effectvdizzymodule.dll"
   copy .\Release\effectvdizzymodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvdizzymodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\effectvdizzymodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" "$(OUTDIR)\effectvdizzymodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdizzymodule.obj"
	-@erase "$(INTDIR)\effectvdizzymodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvdizzymodule.dll"
	-@erase "$(OUTDIR)\effectvdizzymodule.exp"
	-@erase "$(OUTDIR)\effectvdizzymodule.ilk"
	-@erase "$(OUTDIR)\effectvdizzymodule.lib"
	-@erase "$(OUTDIR)\effectvdizzymodule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdizzymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdizzymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdizzymodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvdizzymodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvdizzymodule.def" /out:"$(OUTDIR)\effectvdizzymodule.dll" /implib:"$(OUTDIR)\effectvdizzymodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvdizzymodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdizzymodule.obj" \
	"$(INTDIR)\effectvdizzymodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvdizzymodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvdizzymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" "$(OUTDIR)\effectvdizzymodule.dll"
   copy .\Debug\effectvdizzymodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("effectvdizzymodule.dep")
!INCLUDE "effectvdizzymodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvdizzymodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvdizzymodule - Win32 Release" || "$(CFG)" == "effectvdizzymodule - Win32 Debug"
SOURCE=.\effectvdizzymodule.c

!IF  "$(CFG)" == "effectvdizzymodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdizzymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdizzymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvdizzymodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvdizzymodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdizzymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdizzymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvdizzymodule.obj" : $(SOURCE) "$(INTDIR)" ".\effectvdizzymodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvdizzymodule_auto.c

"$(INTDIR)\effectvdizzymodule_auto.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "effectvdizzymodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvdizzymodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvdizzymodule"

!ELSEIF  "$(CFG)" == "effectvdizzymodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvdizzymodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvdizzymodule"

!ENDIF 

SOURCE=.\effectvdizzymodule.spec

!IF  "$(CFG)" == "effectvdizzymodule - Win32 Release"

InputPath=.\effectvdizzymodule.spec
InputName=effectvdizzymodule

".\effectvdizzymodule.h"	".\effectvdizzymodule_auto.c"	".\effectvdizzymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvdizzymodule - Win32 Debug"

InputPath=.\effectvdizzymodule.spec
InputName=effectvdizzymodule

".\effectvdizzymodule.h"	".\effectvdizzymodule_auto.c"	".\effectvdizzymodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

