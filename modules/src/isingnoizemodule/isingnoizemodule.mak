# Microsoft Developer Studio Generated NMAKE File, Based on isingnoizemodule.dsp
!IF "$(CFG)" == ""
CFG=isingnoizemodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. isingnoizemodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "isingnoizemodule - Win32 Release" && "$(CFG)" != "isingnoizemodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "isingnoizemodule.mak" CFG="isingnoizemodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "isingnoizemodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "isingnoizemodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "isingnoizemodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\isingnoizemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\isingnoizemodule.obj"
	-@erase "$(INTDIR)\isingnoizemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\isingnoizemodule.dll"
	-@erase "$(OUTDIR)\isingnoizemodule.exp"
	-@erase "$(OUTDIR)\isingnoizemodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../.." /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "isingnoizemodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\isingnoizemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\isingnoizemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\isingnoizemodule.pdb" /machine:I386 /def:".\isingnoizemodule.def" /out:"$(OUTDIR)\isingnoizemodule.dll" /implib:"$(OUTDIR)\isingnoizemodule.lib" 
DEF_FILE= \
	".\isingnoizemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\isingnoizemodule.obj" \
	"$(INTDIR)\isingnoizemodule_auto.obj"

"$(OUTDIR)\isingnoizemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\isingnoizemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\isingnoizemodule.dll"
   copy .\Release\isingnoizemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "isingnoizemodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\isingnoizemodule_auto.c" ".\isingnoizemodule.h" ".\isingnoizemodule.def" "$(OUTDIR)\isingnoizemodule.dll"


CLEAN :
	-@erase "$(INTDIR)\isingnoizemodule.obj"
	-@erase "$(INTDIR)\isingnoizemodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\isingnoizemodule.dll"
	-@erase "$(OUTDIR)\isingnoizemodule.exp"
	-@erase "$(OUTDIR)\isingnoizemodule.ilk"
	-@erase "$(OUTDIR)\isingnoizemodule.lib"
	-@erase "$(OUTDIR)\isingnoizemodule.pdb"
	-@erase "isingnoizemodule.def"
	-@erase "isingnoizemodule.h"
	-@erase "isingnoizemodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "isingnoizemodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\isingnoizemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\isingnoizemodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\isingnoizemodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\isingnoizemodule.def" /out:"$(OUTDIR)\isingnoizemodule.dll" /implib:"$(OUTDIR)\isingnoizemodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\isingnoizemodule.def"
LINK32_OBJS= \
	"$(INTDIR)\isingnoizemodule.obj" \
	"$(INTDIR)\isingnoizemodule_auto.obj"

"$(OUTDIR)\isingnoizemodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\isingnoizemodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\isingnoizemodule_auto.c" ".\isingnoizemodule.h" ".\isingnoizemodule.def" "$(OUTDIR)\isingnoizemodule.dll"
   copy .\Debug\isingnoizemodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("isingnoizemodule.dep")
!INCLUDE "isingnoizemodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "isingnoizemodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "isingnoizemodule - Win32 Release" || "$(CFG)" == "isingnoizemodule - Win32 Debug"
SOURCE=.\isingnoizemodule.c

!IF  "$(CFG)" == "isingnoizemodule - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../.." /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "isingnoizemodule_EXPORTS" /D "NDEBUG" /D "HAVE_CONFIG_H" /D "_MBCS" /D "WIN32" /Fp"$(INTDIR)\isingnoizemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\isingnoizemodule.obj" : $(SOURCE) "$(INTDIR)" ".\isingnoizemodule.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "isingnoizemodule - Win32 Debug"

CPP_SWITCHES=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../" /I "../../../util/src/misc" /D "_WINDOWS" /D "_USRDLL" /D "isingnoizemodule_EXPORTS" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\isingnoizemodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\isingnoizemodule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\isingnoizemodule_auto.c

"$(INTDIR)\isingnoizemodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\isingnoizemodule.h"


SOURCE=.\isingnoizemodule.spec

!IF  "$(CFG)" == "isingnoizemodule - Win32 Release"

InputPath=.\isingnoizemodule.spec
InputName=isingnoizemodule

".\isingnoizemodule.h"	".\isingnoizemodule_auto.c"	".\isingnoizemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "isingnoizemodule - Win32 Debug"

InputPath=.\isingnoizemodule.spec
InputName=isingnoizemodule

".\isingnoizemodule.h"	".\isingnoizemodule_auto.c"	".\isingnoizemodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

