# Microsoft Developer Studio Generated NMAKE File, Based on gradnormmodule.dsp
!IF "$(CFG)" == ""
CFG=gradnormmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. gradnormmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "gradnormmodule - Win32 Release" && "$(CFG)" != "gradnormmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "gradnormmodule.mak" CFG="gradnormmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "gradnormmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gradnormmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "gradnormmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\gradnormmodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Release" "$(OUTDIR)\gradnormmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\gradnormmodule.obj"
	-@erase "$(INTDIR)\gradnormmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\gradnormmodule.dll"
	-@erase "$(OUTDIR)\gradnormmodule.exp"
	-@erase "$(OUTDIR)\gradnormmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G5 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "gradnormmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\gradnormmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gradnormmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\gradnormmodule.pdb" /machine:I386 /def:".\gradnormmodule.def" /out:"$(OUTDIR)\gradnormmodule.dll" /implib:"$(OUTDIR)\gradnormmodule.lib" /libpath:"Release" 
DEF_FILE= \
	".\gradnormmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\gradnormmodule.obj" \
	"$(INTDIR)\gradnormmodule_auto.obj" \
	"$(INTDIR)\roberts_cross_x86.obj" \
	"..\..\..\util\src\cpuinfo\Release\cpuinfo.lib"

"$(OUTDIR)\gradnormmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\gradnormmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Release" "$(OUTDIR)\gradnormmodule.dll"
   copy .\Release\gradnormmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "gradnormmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\gradnormmodule_auto.c" ".\gradnormmodule.h" ".\gradnormmodule.def" "$(OUTDIR)\gradnormmodule.dll"

!ELSE 

ALL : "cpuinfo - Win32 Debug" ".\gradnormmodule_auto.c" ".\gradnormmodule.h" ".\gradnormmodule.def" "$(OUTDIR)\gradnormmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cpuinfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\gradnormmodule.obj"
	-@erase "$(INTDIR)\gradnormmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\gradnormmodule.dll"
	-@erase "$(OUTDIR)\gradnormmodule.exp"
	-@erase "$(OUTDIR)\gradnormmodule.ilk"
	-@erase "$(OUTDIR)\gradnormmodule.lib"
	-@erase "$(OUTDIR)\gradnormmodule.pdb"
	-@erase "gradnormmodule.def"
	-@erase "gradnormmodule.h"
	-@erase "gradnormmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "gradnormmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\gradnormmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gradnormmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\gradnormmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\gradnormmodule.def" /out:"$(OUTDIR)\gradnormmodule.dll" /implib:"$(OUTDIR)\gradnormmodule.lib" /pdbtype:sept /libpath:"Debug" 
DEF_FILE= \
	".\gradnormmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\gradnormmodule.obj" \
	"$(INTDIR)\gradnormmodule_auto.obj" \
	"$(INTDIR)\roberts_cross_x86.obj" \
	"..\..\..\util\src\cpuinfo\Debug\cpuinfo.lib"

"$(OUTDIR)\gradnormmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\gradnormmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "cpuinfo - Win32 Debug" ".\gradnormmodule_auto.c" ".\gradnormmodule.h" ".\gradnormmodule.def" "$(OUTDIR)\gradnormmodule.dll"
   copy .\Debug\gradnormmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gradnormmodule.dep")
!INCLUDE "gradnormmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "gradnormmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gradnormmodule - Win32 Release" || "$(CFG)" == "gradnormmodule - Win32 Debug"
SOURCE=.\gradnormmodule.cpp

"$(INTDIR)\gradnormmodule.obj" : $(SOURCE) "$(INTDIR)" ".\gradnormmodule.h"


SOURCE=.\gradnormmodule_auto.c

"$(INTDIR)\gradnormmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\gradnormmodule.h"


!IF  "$(CFG)" == "gradnormmodule - Win32 Release"

"cpuinfo - Win32 Release" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" 
   cd "..\..\..\modules\src\gradnormmodule"

"cpuinfo - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\gradnormmodule"

!ELSEIF  "$(CFG)" == "gradnormmodule - Win32 Debug"

"cpuinfo - Win32 Debug" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" 
   cd "..\..\..\modules\src\gradnormmodule"

"cpuinfo - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\util\src\cpuinfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\cpuinfo.mak" CFG="cpuinfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\modules\src\gradnormmodule"

!ENDIF 

SOURCE=.\gradnormmodule.spec

!IF  "$(CFG)" == "gradnormmodule - Win32 Release"

InputPath=.\gradnormmodule.spec
InputName=gradnormmodule

".\gradnormmodule.h"	".\gradnormmodule_auto.c"	".\gradnormmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "gradnormmodule - Win32 Debug"

InputPath=.\gradnormmodule.spec
InputName=gradnormmodule

".\gradnormmodule.h"	".\gradnormmodule_auto.c"	".\gradnormmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 

SOURCE=.\roberts_cross_x86.asm

!IF  "$(CFG)" == "gradnormmodule - Win32 Release"

OutDir=.\Release
InputPath=.\roberts_cross_x86.asm
InputName=roberts_cross_x86

"$(INTDIR)\roberts_cross_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ELSEIF  "$(CFG)" == "gradnormmodule - Win32 Debug"

OutDir=.\Debug
InputPath=.\roberts_cross_x86.asm
InputName=roberts_cross_x86

"$(INTDIR)\roberts_cross_x86.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm
<< 
	

!ENDIF 


!ENDIF 

