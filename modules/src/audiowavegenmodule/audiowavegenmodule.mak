# Microsoft Developer Studio Generated NMAKE File, Based on audiowavegenmodule.dsp
!IF "$(CFG)" == ""
CFG=audiowavegenmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audiowavegenmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audiowavegenmodule - Win32 Release" && "$(CFG)" != "audiowavegenmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audiowavegenmodule.mak" CFG="audiowavegenmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audiowavegenmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audiowavegenmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audiowavegenmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audiowavegenmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiowavegenmodule.obj"
	-@erase "$(INTDIR)\audiowavegenmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\audiowavegenmodule.dll"
	-@erase "$(OUTDIR)\audiowavegenmodule.exp"
	-@erase "$(OUTDIR)\audiowavegenmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiowavegenmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiowavegenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiowavegenmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audiowavegenmodule.pdb" /machine:I386 /def:".\audiowavegenmodule.def" /out:"$(OUTDIR)\audiowavegenmodule.dll" /implib:"$(OUTDIR)\audiowavegenmodule.lib" 
DEF_FILE= \
	".\audiowavegenmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiowavegenmodule.obj" \
	"$(INTDIR)\audiowavegenmodule_auto.obj"

"$(OUTDIR)\audiowavegenmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audiowavegenmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audiowavegenmodule.dll"
   copy .\Release\audiowavegenmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audiowavegenmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audiowavegenmodule_auto.c" ".\audiowavegenmodule.h" ".\audiowavegenmodule.def" "$(OUTDIR)\audiowavegenmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\audiowavegenmodule.obj"
	-@erase "$(INTDIR)\audiowavegenmodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\audiowavegenmodule.dll"
	-@erase "$(OUTDIR)\audiowavegenmodule.exp"
	-@erase "$(OUTDIR)\audiowavegenmodule.ilk"
	-@erase "$(OUTDIR)\audiowavegenmodule.lib"
	-@erase "$(OUTDIR)\audiowavegenmodule.pdb"
	-@erase "audiowavegenmodule.def"
	-@erase "audiowavegenmodule.h"
	-@erase "audiowavegenmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiowavegenmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiowavegenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiowavegenmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audiowavegenmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audiowavegenmodule.def" /out:"$(OUTDIR)\audiowavegenmodule.dll" /implib:"$(OUTDIR)\audiowavegenmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audiowavegenmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\audiowavegenmodule.obj" \
	"$(INTDIR)\audiowavegenmodule_auto.obj"

"$(OUTDIR)\audiowavegenmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audiowavegenmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audiowavegenmodule_auto.c" ".\audiowavegenmodule.h" ".\audiowavegenmodule.def" "$(OUTDIR)\audiowavegenmodule.dll"
   copy .\Debug\audiowavegenmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audiowavegenmodule.dep")
!INCLUDE "audiowavegenmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audiowavegenmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audiowavegenmodule - Win32 Release" || "$(CFG)" == "audiowavegenmodule - Win32 Debug"
SOURCE=.\audiowavegenmodule.c

!IF  "$(CFG)" == "audiowavegenmodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiowavegenmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiowavegenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\audiowavegenmodule.obj" : $(SOURCE) "$(INTDIR)" ".\audiowavegenmodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "audiowavegenmodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiowavegenmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiowavegenmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\audiowavegenmodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\audiowavegenmodule_auto.c

"$(INTDIR)\audiowavegenmodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\audiowavegenmodule.h"


SOURCE=.\audiowavegenmodule.spec

!IF  "$(CFG)" == "audiowavegenmodule - Win32 Release"

InputPath=.\audiowavegenmodule.spec
InputName=audiowavegenmodule

".\audiowavegenmodule.h"	".\audiowavegenmodule_auto.c"	".\audiowavegenmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audiowavegenmodule - Win32 Debug"

InputPath=.\audiowavegenmodule.spec
InputName=audiowavegenmodule

".\audiowavegenmodule.h"	".\audiowavegenmodule_auto.c"	".\audiowavegenmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

