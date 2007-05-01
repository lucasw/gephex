# Microsoft Developer Studio Generated NMAKE File, Based on audioinmodule.dsp
!IF "$(CFG)" == ""
CFG=audioinmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audioinmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audioinmodule - Win32 Release" && "$(CFG)" != "audioinmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audioinmodule.mak" CFG="audioinmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audioinmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audioinmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audioinmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audioinmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\a_cvt.obj"
	-@erase "$(INTDIR)\audiobuffer.obj"
	-@erase "$(INTDIR)\audioinmodule.obj"
	-@erase "$(INTDIR)\audioinmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\waveindriver.obj"
	-@erase "$(OUTDIR)\audioinmodule.dll"
	-@erase "$(OUTDIR)\audioinmodule.exp"
	-@erase "$(OUTDIR)\audioinmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audioinmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audioinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audioinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audioinmodule.pdb" /machine:I386 /def:".\audioinmodule.def" /out:"$(OUTDIR)\audioinmodule.dll" /implib:"$(OUTDIR)\audioinmodule.lib" 
DEF_FILE= \
	".\audioinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\a_cvt.obj" \
	"$(INTDIR)\audiobuffer.obj" \
	"$(INTDIR)\audioinmodule.obj" \
	"$(INTDIR)\audioinmodule_auto.obj" \
	"$(INTDIR)\waveindriver.obj"

"$(OUTDIR)\audioinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audioinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audioinmodule.dll"
   copy .\Release\audioinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audioinmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audioinmodule_auto.c" ".\audioinmodule.h" ".\audioinmodule.def" "$(OUTDIR)\audioinmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\a_cvt.obj"
	-@erase "$(INTDIR)\audiobuffer.obj"
	-@erase "$(INTDIR)\audioinmodule.obj"
	-@erase "$(INTDIR)\audioinmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\waveindriver.obj"
	-@erase "$(OUTDIR)\audioinmodule.dll"
	-@erase "$(OUTDIR)\audioinmodule.exp"
	-@erase "$(OUTDIR)\audioinmodule.ilk"
	-@erase "$(OUTDIR)\audioinmodule.lib"
	-@erase "$(OUTDIR)\audioinmodule.pdb"
	-@erase "audioinmodule.def"
	-@erase "audioinmodule.h"
	-@erase "audioinmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audioinmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audioinmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audioinmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audioinmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audioinmodule.def" /out:"$(OUTDIR)\audioinmodule.dll" /implib:"$(OUTDIR)\audioinmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audioinmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\a_cvt.obj" \
	"$(INTDIR)\audiobuffer.obj" \
	"$(INTDIR)\audioinmodule.obj" \
	"$(INTDIR)\audioinmodule_auto.obj" \
	"$(INTDIR)\waveindriver.obj"

"$(OUTDIR)\audioinmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audioinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audioinmodule_auto.c" ".\audioinmodule.h" ".\audioinmodule.def" "$(OUTDIR)\audioinmodule.dll"
   copy .\Debug\audioinmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audioinmodule.dep")
!INCLUDE "audioinmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audioinmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audioinmodule - Win32 Release" || "$(CFG)" == "audioinmodule - Win32 Debug"
SOURCE=.\a_cvt.cpp

"$(INTDIR)\a_cvt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\audiobuffer.c

"$(INTDIR)\audiobuffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\audioinmodule.cpp

"$(INTDIR)\audioinmodule.obj" : $(SOURCE) "$(INTDIR)" ".\audioinmodule.h"


SOURCE=.\audioinmodule_auto.c

"$(INTDIR)\audioinmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\waveindriver.cpp

"$(INTDIR)\waveindriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\audioinmodule.spec

!IF  "$(CFG)" == "audioinmodule - Win32 Release"

InputPath=.\audioinmodule.spec
InputName=audioinmodule

".\audioinmodule.h"	".\audioinmodule_auto.c"	".\audioinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audioinmodule - Win32 Debug"

InputPath=.\audioinmodule.spec
InputName=audioinmodule

".\audioinmodule.h"	".\audioinmodule_auto.c"	".\audioinmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

