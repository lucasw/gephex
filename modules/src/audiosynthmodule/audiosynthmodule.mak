# Microsoft Developer Studio Generated NMAKE File, Based on audiosynthmodule.dsp
!IF "$(CFG)" == ""
CFG=audiosynthmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audiosynthmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audiosynthmodule - Win32 Release" && "$(CFG)" != "audiosynthmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audiosynthmodule.mak" CFG="audiosynthmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audiosynthmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audiosynthmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audiosynthmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audiosynthmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiosynthmodule.obj"
	-@erase "$(INTDIR)\audiosynthmodule_auto.obj"
	-@erase "$(INTDIR)\synth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\audiosynthmodule.dll"
	-@erase "$(OUTDIR)\audiosynthmodule.exp"
	-@erase "$(OUTDIR)\audiosynthmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/envtype" /I "../../../types/src/lfotype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiosynthmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiosynthmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiosynthmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audiosynthmodule.pdb" /machine:I386 /def:".\audiosynthmodule.def" /out:"$(OUTDIR)\audiosynthmodule.dll" /implib:"$(OUTDIR)\audiosynthmodule.lib" 
DEF_FILE= \
	".\audiosynthmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiosynthmodule.obj" \
	"$(INTDIR)\audiosynthmodule_auto.obj" \
	"$(INTDIR)\synth.obj"

"$(OUTDIR)\audiosynthmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audiosynthmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audiosynthmodule.dll"
   copy .\Release\audiosynthmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audiosynthmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audiosynthmodule_auto.c" ".\audiosynthmodule.h" ".\audiosynthmodule.def" "$(OUTDIR)\audiosynthmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiosynthmodule.obj"
	-@erase "$(INTDIR)\audiosynthmodule_auto.obj"
	-@erase "$(INTDIR)\synth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\audiosynthmodule.dll"
	-@erase "$(OUTDIR)\audiosynthmodule.exp"
	-@erase "$(OUTDIR)\audiosynthmodule.ilk"
	-@erase "$(OUTDIR)\audiosynthmodule.lib"
	-@erase "$(OUTDIR)\audiosynthmodule.pdb"
	-@erase "audiosynthmodule.def"
	-@erase "audiosynthmodule.h"
	-@erase "audiosynthmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/envtype" /I "../../../types/src/lfotype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiosynthmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiosynthmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiosynthmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audiosynthmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audiosynthmodule.def" /out:"$(OUTDIR)\audiosynthmodule.dll" /implib:"$(OUTDIR)\audiosynthmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audiosynthmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiosynthmodule.obj" \
	"$(INTDIR)\audiosynthmodule_auto.obj" \
	"$(INTDIR)\synth.obj"

"$(OUTDIR)\audiosynthmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audiosynthmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audiosynthmodule_auto.c" ".\audiosynthmodule.h" ".\audiosynthmodule.def" "$(OUTDIR)\audiosynthmodule.dll"
   copy .\Debug\audiosynthmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audiosynthmodule.dep")
!INCLUDE "audiosynthmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audiosynthmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audiosynthmodule - Win32 Release" || "$(CFG)" == "audiosynthmodule - Win32 Debug"
SOURCE=.\audiosynthmodule.cpp

"$(INTDIR)\audiosynthmodule.obj" : $(SOURCE) "$(INTDIR)" ".\audiosynthmodule.h"


SOURCE=.\audiosynthmodule_auto.c

"$(INTDIR)\audiosynthmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\audiosynthmodule.h"


SOURCE=.\synth.cpp

"$(INTDIR)\synth.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\audiosynthmodule.spec

!IF  "$(CFG)" == "audiosynthmodule - Win32 Release"

InputPath=.\audiosynthmodule.spec
InputName=audiosynthmodule

".\audiosynthmodule.h"	".\audiosynthmodule_auto.c"	".\audiosynthmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audiosynthmodule - Win32 Debug"

InputPath=.\audiosynthmodule.spec
InputName=audiosynthmodule

".\audiosynthmodule.h"	".\audiosynthmodule_auto.c"	".\audiosynthmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

