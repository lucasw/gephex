# Microsoft Developer Studio Generated NMAKE File, Based on stringtokenizermodule.dsp
!IF "$(CFG)" == ""
CFG=stringtokenizermodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. stringtokenizermodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "stringtokenizermodule - Win32 Release" && "$(CFG)" != "stringtokenizermodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "stringtokenizermodule.mak" CFG="stringtokenizermodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "stringtokenizermodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stringtokenizermodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "stringtokenizermodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\stringtokenizermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\stringtokenizermodule.obj"
	-@erase "$(INTDIR)\stringtokenizermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\stringtokenizermodule.dll"
	-@erase "$(OUTDIR)\stringtokenizermodule.exp"
	-@erase "$(OUTDIR)\stringtokenizermodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "stringtokenizermodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\stringtokenizermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stringtokenizermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\stringtokenizermodule.pdb" /machine:I386 /def:".\stringtokenizermodule.def" /out:"$(OUTDIR)\stringtokenizermodule.dll" /implib:"$(OUTDIR)\stringtokenizermodule.lib" 
DEF_FILE= \
	".\stringtokenizermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\stringtokenizermodule.obj" \
	"$(INTDIR)\stringtokenizermodule_auto.obj"

"$(OUTDIR)\stringtokenizermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\stringtokenizermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\stringtokenizermodule.dll"
   copy .\Release\stringtokenizermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "stringtokenizermodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\stringtokenizermodule_auto.c" ".\stringtokenizermodule.h" ".\stringtokenizermodule.def" "$(OUTDIR)\stringtokenizermodule.dll"


CLEAN :
	-@erase "$(INTDIR)\stringtokenizermodule.obj"
	-@erase "$(INTDIR)\stringtokenizermodule_auto.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\stringtokenizermodule.dll"
	-@erase "$(OUTDIR)\stringtokenizermodule.exp"
	-@erase "$(OUTDIR)\stringtokenizermodule.ilk"
	-@erase "$(OUTDIR)\stringtokenizermodule.lib"
	-@erase "$(OUTDIR)\stringtokenizermodule.pdb"
	-@erase "stringtokenizermodule.def"
	-@erase "stringtokenizermodule.h"
	-@erase "stringtokenizermodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "stringtokenizermodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\stringtokenizermodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stringtokenizermodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\stringtokenizermodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\stringtokenizermodule.def" /out:"$(OUTDIR)\stringtokenizermodule.dll" /implib:"$(OUTDIR)\stringtokenizermodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\stringtokenizermodule.def"
LINK32_OBJS= \
	"$(INTDIR)\stringtokenizermodule.obj" \
	"$(INTDIR)\stringtokenizermodule_auto.obj"

"$(OUTDIR)\stringtokenizermodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\stringtokenizermodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\stringtokenizermodule_auto.c" ".\stringtokenizermodule.h" ".\stringtokenizermodule.def" "$(OUTDIR)\stringtokenizermodule.dll"
   copy .\Debug\stringtokenizermodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("stringtokenizermodule.dep")
!INCLUDE "stringtokenizermodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "stringtokenizermodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "stringtokenizermodule - Win32 Release" || "$(CFG)" == "stringtokenizermodule - Win32 Debug"
SOURCE=.\stringtokenizermodule.cpp

"$(INTDIR)\stringtokenizermodule.obj" : $(SOURCE) "$(INTDIR)" ".\stringtokenizermodule.h"


SOURCE=.\stringtokenizermodule_auto.c

"$(INTDIR)\stringtokenizermodule_auto.obj" : $(SOURCE) "$(INTDIR)" ".\stringtokenizermodule.h"


SOURCE=.\stringtokenizermodule.spec

!IF  "$(CFG)" == "stringtokenizermodule - Win32 Release"

InputPath=.\stringtokenizermodule.spec
InputName=stringtokenizermodule

".\stringtokenizermodule.h"	".\stringtokenizermodule_auto.c"	".\stringtokenizermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "stringtokenizermodule - Win32 Debug"

InputPath=.\stringtokenizermodule.spec
InputName=stringtokenizermodule

".\stringtokenizermodule.h"	".\stringtokenizermodule_auto.c"	".\stringtokenizermodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

