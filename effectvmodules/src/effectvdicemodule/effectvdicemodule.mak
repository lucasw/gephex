# Microsoft Developer Studio Generated NMAKE File, Based on effectvdicemodule.dsp
!IF "$(CFG)" == ""
CFG=effectvdicemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvdicemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvdicemodule - Win32 Release" && "$(CFG)" != "effectvdicemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvdicemodule.mak" CFG="effectvdicemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvdicemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvdicemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "effectvdicemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdicemodule.obj"
	-@erase "$(INTDIR)\effectvdicemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvdicemodule.dll"
	-@erase "$(OUTDIR)\effectvdicemodule.exp"
	-@erase "$(OUTDIR)\effectvdicemodule.lib"
	-@erase "effectvdicemodule.def"
	-@erase "effectvdicemodule.h"
	-@erase "effectvdicemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdicemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdicemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdicemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvdicemodule.pdb" /machine:I386 /def:".\effectvdicemodule.def" /out:"$(OUTDIR)\effectvdicemodule.dll" /implib:"$(OUTDIR)\effectvdicemodule.lib" 
DEF_FILE= \
	".\effectvdicemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdicemodule.obj" \
	"$(INTDIR)\effectvdicemodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvdicemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvdicemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"
   copy .\Release\effectvdicemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvdicemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdicemodule.obj"
	-@erase "$(INTDIR)\effectvdicemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvdicemodule.dll"
	-@erase "$(OUTDIR)\effectvdicemodule.exp"
	-@erase "$(OUTDIR)\effectvdicemodule.ilk"
	-@erase "$(OUTDIR)\effectvdicemodule.lib"
	-@erase "$(OUTDIR)\effectvdicemodule.pdb"
	-@erase "effectvdicemodule.def"
	-@erase "effectvdicemodule.h"
	-@erase "effectvdicemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdicemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdicemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdicemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvdicemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvdicemodule.def" /out:"$(OUTDIR)\effectvdicemodule.dll" /implib:"$(OUTDIR)\effectvdicemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvdicemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdicemodule.obj" \
	"$(INTDIR)\effectvdicemodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvdicemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvdicemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" ".\effectvdicemodule_auto.c" ".\effectvdicemodule.h" ".\effectvdicemodule.def" "$(OUTDIR)\effectvdicemodule.dll"
   copy .\Debug\effectvdicemodule.dll ..\..\..\dlls\modules
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
!IF EXISTS("effectvdicemodule.dep")
!INCLUDE "effectvdicemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvdicemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvdicemodule - Win32 Release" || "$(CFG)" == "effectvdicemodule - Win32 Debug"
SOURCE=.\effectvdicemodule.c

!IF  "$(CFG)" == "effectvdicemodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdicemodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdicemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvdicemodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvdicemodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../types/src/framebuffertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdicemodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\effectvdicemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvdicemodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvdicemodule_auto.c

"$(INTDIR)\effectvdicemodule_auto.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "effectvdicemodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvdicemodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvdicemodule"

!ELSEIF  "$(CFG)" == "effectvdicemodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvdicemodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvdicemodule"

!ENDIF 

SOURCE=.\effectvdicemodule.spec

!IF  "$(CFG)" == "effectvdicemodule - Win32 Release"

InputPath=.\effectvdicemodule.spec
InputName=effectvdicemodule

".\effectvdicemodule.h"	".\effectvdicemodule_auto.c"	".\effectvdicemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvdicemodule - Win32 Debug"

InputPath=.\effectvdicemodule.spec
InputName=effectvdicemodule

".\effectvdicemodule.h"	".\effectvdicemodule_auto.c"	".\effectvdicemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

