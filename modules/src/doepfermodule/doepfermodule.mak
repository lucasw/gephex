# Microsoft Developer Studio Generated NMAKE File, Based on doepfermodule.dsp
!IF "$(CFG)" == ""
CFG=doepfermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. doepfermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "doepfermodule - Win32 Release" && "$(CFG)" != "doepfermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "doepfermodule.mak" CFG="doepfermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "doepfermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "doepfermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "doepfermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\doepfermodule.dll"

!ELSE 

ALL : "libmidi - Win32 Release" "$(OUTDIR)\doepfermodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmidi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\doepfermodule.obj"
	-@erase "$(INTDIR)\doepfermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\doepfermodule.dll"
	-@erase "$(OUTDIR)\doepfermodule.exp"
	-@erase "$(OUTDIR)\doepfermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/miditype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /I "../libmidi" /D "_WINDOWS" /D "_USRDLL" /D "doepfermodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\doepfermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\doepfermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\doepfermodule.pdb" /machine:I386 /def:".\doepfermodule.def" /out:"$(OUTDIR)\doepfermodule.dll" /implib:"$(OUTDIR)\doepfermodule.lib" 
DEF_FILE= \
	".\doepfermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\doepfermodule.obj" \
	"$(INTDIR)\doepfermodule_auto.obj" \
	"..\libmidi\Release\libmidi.lib"

"$(OUTDIR)\doepfermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\doepfermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libmidi - Win32 Release" "$(OUTDIR)\doepfermodule.dll"
   copy .\Release\doepfermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "doepfermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\doepfermodule_auto.c" ".\doepfermodule.h" ".\doepfermodule.def" "$(OUTDIR)\doepfermodule.dll"

!ELSE 

ALL : "libmidi - Win32 Debug" ".\doepfermodule_auto.c" ".\doepfermodule.h" ".\doepfermodule.def" "$(OUTDIR)\doepfermodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmidi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\doepfermodule.obj"
	-@erase "$(INTDIR)\doepfermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\doepfermodule.dll"
	-@erase "$(OUTDIR)\doepfermodule.exp"
	-@erase "$(OUTDIR)\doepfermodule.ilk"
	-@erase "$(OUTDIR)\doepfermodule.lib"
	-@erase "$(OUTDIR)\doepfermodule.pdb"
	-@erase "doepfermodule.def"
	-@erase "doepfermodule.h"
	-@erase "doepfermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/miditype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /I "../libmidi" /D "_WINDOWS" /D "_USRDLL" /D "doepfermodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\doepfermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\doepfermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\doepfermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\doepfermodule.def" /out:"$(OUTDIR)\doepfermodule.dll" /implib:"$(OUTDIR)\doepfermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\doepfermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\doepfermodule.obj" \
	"$(INTDIR)\doepfermodule_auto.obj" \
	"..\libmidi\Debug\libmidi.lib"

"$(OUTDIR)\doepfermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\doepfermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libmidi - Win32 Debug" ".\doepfermodule_auto.c" ".\doepfermodule.h" ".\doepfermodule.def" "$(OUTDIR)\doepfermodule.dll"
   copy .\Debug\doepfermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("doepfermodule.dep")
!INCLUDE "doepfermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "doepfermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "doepfermodule - Win32 Release" || "$(CFG)" == "doepfermodule - Win32 Debug"
SOURCE=.\doepfermodule.c

!IF  "$(CFG)" == "doepfermodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/miditype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../.." /I "../libmidi" /D "_WINDOWS" /D "_USRDLL" /D "doepfermodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\doepfermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\doepfermodule.obj" : $(SOURCE) "$(INTDIR)" ".\doepfermodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "doepfermodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/miditype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../" /I "../libmidi" /D "_WINDOWS" /D "_USRDLL" /D "doepfermodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\doepfermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\doepfermodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\doepfermodule_auto.c

"$(INTDIR)\doepfermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\doepfermodule.h"


!IF  "$(CFG)" == "doepfermodule - Win32 Release"

"libmidi - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Release" 
   cd "..\doepfermodule"

"libmidi - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\doepfermodule"

!ELSEIF  "$(CFG)" == "doepfermodule - Win32 Debug"

"libmidi - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Debug" 
   cd "..\doepfermodule"

"libmidi - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\doepfermodule"

!ENDIF 

SOURCE=.\doepfermodule.spec

!IF  "$(CFG)" == "doepfermodule - Win32 Release"

InputPath=.\doepfermodule.spec
InputName=doepfermodule

".\doepfermodule.h"	".\doepfermodule_auto.c"	".\doepfermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "doepfermodule - Win32 Debug"

InputPath=.\doepfermodule.spec
InputName=doepfermodule

".\doepfermodule.h"	".\doepfermodule_auto.c"	".\doepfermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

