# Microsoft Developer Studio Generated NMAKE File, Based on effectvdotmodule.dsp
!IF "$(CFG)" == ""
CFG=effectvdotmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. effectvdotmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "effectvdotmodule - Win32 Release" && "$(CFG)" != "effectvdotmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "effectvdotmodule.mak" CFG="effectvdotmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "effectvdotmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "effectvdotmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "effectvdotmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\effectvdotmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Release" "$(OUTDIR)\effectvdotmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdotmodule.obj"
	-@erase "$(INTDIR)\effectvdotmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\effectvdotmodule.dll"
	-@erase "$(OUTDIR)\effectvdotmodule.exp"
	-@erase "$(OUTDIR)\effectvdotmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdotmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D inline=__inline /Fp"$(INTDIR)\effectvdotmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdotmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\effectvdotmodule.pdb" /machine:I386 /def:".\effectvdotmodule.def" /out:"$(OUTDIR)\effectvdotmodule.dll" /implib:"$(OUTDIR)\effectvdotmodule.lib" 
DEF_FILE= \
	".\effectvdotmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdotmodule.obj" \
	"$(INTDIR)\effectvdotmodule_auto.obj" \
	"..\libeffectv\Release\libeffectv.lib"

"$(OUTDIR)\effectvdotmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\effectvdotmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Release" "$(OUTDIR)\effectvdotmodule.dll"
   copy .\Release\effectvdotmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "effectvdotmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\effectvdotmodule_auto.c" ".\effectvdotmodule.h" ".\effectvdotmodule.def" "$(OUTDIR)\effectvdotmodule.dll"

!ELSE 

ALL : "libeffectv - Win32 Debug" ".\effectvdotmodule_auto.c" ".\effectvdotmodule.h" ".\effectvdotmodule.def" "$(OUTDIR)\effectvdotmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libeffectv - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\effectvdotmodule.obj"
	-@erase "$(INTDIR)\effectvdotmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\effectvdotmodule.dll"
	-@erase "$(OUTDIR)\effectvdotmodule.exp"
	-@erase "$(OUTDIR)\effectvdotmodule.ilk"
	-@erase "$(OUTDIR)\effectvdotmodule.lib"
	-@erase "$(OUTDIR)\effectvdotmodule.pdb"
	-@erase "effectvdotmodule.def"
	-@erase "effectvdotmodule.h"
	-@erase "effectvdotmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdotmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D inline=__inline /Fp"$(INTDIR)\effectvdotmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\effectvdotmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\effectvdotmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\effectvdotmodule.def" /out:"$(OUTDIR)\effectvdotmodule.dll" /implib:"$(OUTDIR)\effectvdotmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\effectvdotmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\effectvdotmodule.obj" \
	"$(INTDIR)\effectvdotmodule_auto.obj" \
	"..\libeffectv\Debug\libeffectv.lib"

"$(OUTDIR)\effectvdotmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\effectvdotmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libeffectv - Win32 Debug" ".\effectvdotmodule_auto.c" ".\effectvdotmodule.h" ".\effectvdotmodule.def" "$(OUTDIR)\effectvdotmodule.dll"
   copy .\Debug\effectvdotmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("effectvdotmodule.dep")
!INCLUDE "effectvdotmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "effectvdotmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "effectvdotmodule - Win32 Release" || "$(CFG)" == "effectvdotmodule - Win32 Debug"
SOURCE=.\effectvdotmodule.c

!IF  "$(CFG)" == "effectvdotmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /w /W0 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdotmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D inline=__inline /Fp"$(INTDIR)\effectvdotmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\effectvdotmodule.obj" : $(SOURCE) "$(INTDIR)" ".\effectvdotmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "effectvdotmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../../" /I "../../../types/src/framebuffertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libeffectv" /I "../libeffectv/trick" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "effectvdotmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /D inline=__inline /Fp"$(INTDIR)\effectvdotmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\effectvdotmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\effectvdotmodule_auto.c

"$(INTDIR)\effectvdotmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\effectvdotmodule.h"


SOURCE=.\dot.c

!IF  "$(CFG)" == "effectvdotmodule - Win32 Release"

"libeffectv - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" 
   cd "..\effectvdotmodule"

"libeffectv - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Release" RECURSE=1 CLEAN 
   cd "..\effectvdotmodule"

!ELSEIF  "$(CFG)" == "effectvdotmodule - Win32 Debug"

"libeffectv - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" 
   cd "..\effectvdotmodule"

"libeffectv - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\libeffectv"
   $(MAKE) /$(MAKEFLAGS) /F ".\libeffectv.mak" CFG="libeffectv - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\effectvdotmodule"

!ENDIF 

SOURCE=.\effectvdotmodule.spec

!IF  "$(CFG)" == "effectvdotmodule - Win32 Release"

InputPath=.\effectvdotmodule.spec
InputName=effectvdotmodule

".\effectvdotmodule.h"	".\effectvdotmodule_auto.c"	".\effectvdotmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "effectvdotmodule - Win32 Debug"

InputPath=.\effectvdotmodule.spec
InputName=effectvdotmodule

".\effectvdotmodule.h"	".\effectvdotmodule_auto.c"	".\effectvdotmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\..\modules\pluc.py c $(InputName).spec 
	python ..\..\..\modules\pluc.py h $(InputName).spec 
	python ..\..\..\modules\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

