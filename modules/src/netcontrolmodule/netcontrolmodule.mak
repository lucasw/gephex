# Microsoft Developer Studio Generated NMAKE File, Based on netcontrolmodule.dsp
!IF "$(CFG)" == ""
CFG=netcontrolmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. netcontrolmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "netcontrolmodule - Win32 Release" && "$(CFG)" != "netcontrolmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "netcontrolmodule.mak" CFG="netcontrolmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "netcontrolmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "netcontrolmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "netcontrolmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\netcontrolmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\netcontrolmodule.obj"
	-@erase "$(INTDIR)\netcontrolmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\netcontrolmodule.dll"
	-@erase "$(OUTDIR)\netcontrolmodule.exp"
	-@erase "$(OUTDIR)\netcontrolmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../.." /I "../../../types/src/miditype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_WINDOWS" /D "_USRDLL" /D "netcontrolmodule_EXPORTS" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\netcontrolmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netcontrolmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\netcontrolmodule.pdb" /machine:I386 /def:".\netcontrolmodule.def" /out:"$(OUTDIR)\netcontrolmodule.dll" /implib:"$(OUTDIR)\netcontrolmodule.lib" 
DEF_FILE= \
	".\netcontrolmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\netcontrolmodule.obj" \
	"$(INTDIR)\netcontrolmodule_auto.obj"

"$(OUTDIR)\netcontrolmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\netcontrolmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\netcontrolmodule.dll"
   copy .\Release\netcontrolmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "netcontrolmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\netcontrolmodule_auto.c" ".\netcontrolmodule.h" ".\netcontrolmodule.def" "..\..\..\config.h" "$(OUTDIR)\netcontrolmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\netcontrolmodule.obj"
	-@erase "$(INTDIR)\netcontrolmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\netcontrolmodule.dll"
	-@erase "$(OUTDIR)\netcontrolmodule.exp"
	-@erase "$(OUTDIR)\netcontrolmodule.ilk"
	-@erase "$(OUTDIR)\netcontrolmodule.lib"
	-@erase "$(OUTDIR)\netcontrolmodule.pdb"
	-@erase "..\..\..\config.h"
	-@erase "netcontrolmodule.def"
	-@erase "netcontrolmodule.h"
	-@erase "netcontrolmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../" /I "../../../types/src/miditype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "netcontrolmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\netcontrolmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netcontrolmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\netcontrolmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\netcontrolmodule.def" /out:"$(OUTDIR)\netcontrolmodule.dll" /implib:"$(OUTDIR)\netcontrolmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\netcontrolmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\netcontrolmodule.obj" \
	"$(INTDIR)\netcontrolmodule_auto.obj"

"$(OUTDIR)\netcontrolmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\netcontrolmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\netcontrolmodule_auto.c" ".\netcontrolmodule.h" ".\netcontrolmodule.def" "..\..\..\config.h" "$(OUTDIR)\netcontrolmodule.dll"
   copy .\Debug\netcontrolmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("netcontrolmodule.dep")
!INCLUDE "netcontrolmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "netcontrolmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "netcontrolmodule - Win32 Release" || "$(CFG)" == "netcontrolmodule - Win32 Debug"
SOURCE=.\netcontrolmodule.c

!IF  "$(CFG)" == "netcontrolmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/numbertype" /I "../.." /I "../../../types/src/miditype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_WINDOWS" /D "_USRDLL" /D "netcontrolmodule_EXPORTS" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\netcontrolmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\netcontrolmodule.obj" : $(SOURCE) "$(INTDIR)" ".\netcontrolmodule.h" "..\..\..\config.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "netcontrolmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/numbertype" /I "../../" /I "../../../types/src/miditype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "netcontrolmodule_EXPORTS" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\netcontrolmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\netcontrolmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\netcontrolmodule_auto.c

"$(INTDIR)\netcontrolmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\netcontrolmodule.h"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "netcontrolmodule - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "netcontrolmodule - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 

SOURCE=.\netcontrolmodule.spec

!IF  "$(CFG)" == "netcontrolmodule - Win32 Release"

InputPath=.\netcontrolmodule.spec
InputName=netcontrolmodule

".\netcontrolmodule.h"	".\netcontrolmodule_auto.c"	".\netcontrolmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "netcontrolmodule - Win32 Debug"

InputPath=.\netcontrolmodule.spec
InputName=netcontrolmodule

".\netcontrolmodule.h"	".\netcontrolmodule_auto.c"	".\netcontrolmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

