# Microsoft Developer Studio Generated NMAKE File, Based on midiinmodule.dsp
!IF "$(CFG)" == ""
CFG=midiinmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. midiinmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "midiinmodule - Win32 Release" && "$(CFG)" != "midiinmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "midiinmodule.mak" CFG="midiinmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "midiinmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "midiinmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "midiinmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\midiinmodule.dll"

!ELSE 

ALL : "libmidi - Win32 Release" "$(OUTDIR)\midiinmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmidi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\midiinmodule.obj"
	-@erase "$(INTDIR)\midiinmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wavemidiindriver.obj"
	-@erase "$(OUTDIR)\midiinmodule.dll"
	-@erase "$(OUTDIR)\midiinmodule.exp"
	-@erase "$(OUTDIR)\midiinmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../" /I "../libmidi" /I "../../../types/src/numbertype" /I "../../../types/src/miditype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "midiinmodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\midiinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\midiinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\midiinmodule.pdb" /machine:I386 /def:".\midiinmodule.def" /out:"$(OUTDIR)\midiinmodule.dll" /implib:"$(OUTDIR)\midiinmodule.lib" 
DEF_FILE= \
	".\midiinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\midiinmodule.obj" \
	"$(INTDIR)\midiinmodule_auto.obj" \
	"$(INTDIR)\wavemidiindriver.obj" \
	"..\libmidi\Release\libmidi.lib"

"$(OUTDIR)\midiinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\midiinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libmidi - Win32 Release" "$(OUTDIR)\midiinmodule.dll"
   copy .\Release\midiinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "midiinmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\midiinmodule_auto.c" ".\midiinmodule.h" ".\midiinmodule.def" "..\..\..\config.h" "$(OUTDIR)\midiinmodule.dll"

!ELSE 

ALL : "libmidi - Win32 Debug" ".\midiinmodule_auto.c" ".\midiinmodule.h" ".\midiinmodule.def" "..\..\..\config.h" "$(OUTDIR)\midiinmodule.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmidi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\midiinmodule.obj"
	-@erase "$(INTDIR)\midiinmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wavemidiindriver.obj"
	-@erase "$(OUTDIR)\midiinmodule.dll"
	-@erase "$(OUTDIR)\midiinmodule.exp"
	-@erase "$(OUTDIR)\midiinmodule.ilk"
	-@erase "$(OUTDIR)\midiinmodule.lib"
	-@erase "$(OUTDIR)\midiinmodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "midiinmodule.def"
	-@erase "midiinmodule.h"
	-@erase "midiinmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../.." /I "../libmidi" /I "../../../types/src/numbertype" /I "../../../types/src/miditype" /I "../../../types/src/stringtype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_WINDOWS" /D "_USRDLL" /D "midiinmodule_EXPORTS" /D "_DEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\midiinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\midiinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\midiinmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\midiinmodule.def" /out:"$(OUTDIR)\midiinmodule.dll" /implib:"$(OUTDIR)\midiinmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\midiinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\midiinmodule.obj" \
	"$(INTDIR)\midiinmodule_auto.obj" \
	"$(INTDIR)\wavemidiindriver.obj" \
	"..\libmidi\Debug\libmidi.lib"

"$(OUTDIR)\midiinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\midiinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "libmidi - Win32 Debug" ".\midiinmodule_auto.c" ".\midiinmodule.h" ".\midiinmodule.def" "..\..\..\config.h" "$(OUTDIR)\midiinmodule.dll"
   copy .\Debug\midiinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("midiinmodule.dep")
!INCLUDE "midiinmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "midiinmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "midiinmodule - Win32 Release" || "$(CFG)" == "midiinmodule - Win32 Debug"
SOURCE=.\midiinmodule.cpp

"$(INTDIR)\midiinmodule.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h" ".\midiinmodule.h"


SOURCE=.\midiinmodule_auto.c

"$(INTDIR)\midiinmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\midiinmodule.h"


SOURCE=.\wavemidiindriver.cpp

"$(INTDIR)\wavemidiindriver.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "midiinmodule - Win32 Release"

"libmidi - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Release" 
   cd "..\midiinmodule"

"libmidi - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\midiinmodule"

!ELSEIF  "$(CFG)" == "midiinmodule - Win32 Debug"

"libmidi - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Debug" 
   cd "..\midiinmodule"

"libmidi - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\libmidi"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmidi.mak" CFG="libmidi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\midiinmodule"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "midiinmodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "midiinmodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\midiinmodule.spec

!IF  "$(CFG)" == "midiinmodule - Win32 Release"

InputPath=.\midiinmodule.spec
InputName=midiinmodule

".\midiinmodule.h"	".\midiinmodule_auto.c"	".\midiinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "midiinmodule - Win32 Debug"

InputPath=.\midiinmodule.spec
InputName=midiinmodule

".\midiinmodule.h"	".\midiinmodule_auto.c"	".\midiinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

