# Microsoft Developer Studio Generated NMAKE File, Based on audiooutmodule.dsp
!IF "$(CFG)" == ""
CFG=audiooutmodule - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. audiooutmodule - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "audiooutmodule - Win32 Release" && "$(CFG)" != "audiooutmodule - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "audiooutmodule.mak" CFG="audiooutmodule - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "audiooutmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "audiooutmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "audiooutmodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\audiooutmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\a_cvt.obj"
	-@erase "$(INTDIR)\audiooutmodule.obj"
	-@erase "$(INTDIR)\audiooutmodule_auto.obj"
	-@erase "$(INTDIR)\outbuffer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\waveoutdriver.obj"
	-@erase "$(OUTDIR)\audiooutmodule.dll"
	-@erase "$(OUTDIR)\audiooutmodule.exp"
	-@erase "$(OUTDIR)\audiooutmodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../audioinmodule" /I "../../../types/src/stringtype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiooutmodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiooutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiooutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\audiooutmodule.pdb" /machine:I386 /def:".\audiooutmodule.def" /out:"$(OUTDIR)\audiooutmodule.dll" /implib:"$(OUTDIR)\audiooutmodule.lib" 
DEF_FILE= \
	".\audiooutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\a_cvt.obj" \
	"$(INTDIR)\audiooutmodule.obj" \
	"$(INTDIR)\audiooutmodule_auto.obj" \
	"$(INTDIR)\outbuffer.obj" \
	"$(INTDIR)\waveoutdriver.obj"

"$(OUTDIR)\audiooutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\audiooutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\audiooutmodule.dll"
   copy .\Release\audiooutmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "audiooutmodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\audiooutmodule_auto.c" ".\audiooutmodule.h" ".\audiooutmodule.def" "$(OUTDIR)\audiooutmodule.dll"


CLEAN :
	-@erase "$(INTDIR)\a_cvt.obj"
	-@erase "$(INTDIR)\audiooutmodule.obj"
	-@erase "$(INTDIR)\audiooutmodule_auto.obj"
	-@erase "$(INTDIR)\outbuffer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\waveoutdriver.obj"
	-@erase "$(OUTDIR)\audiooutmodule.dll"
	-@erase "$(OUTDIR)\audiooutmodule.exp"
	-@erase "$(OUTDIR)\audiooutmodule.ilk"
	-@erase "$(OUTDIR)\audiooutmodule.lib"
	-@erase "$(OUTDIR)\audiooutmodule.pdb"
	-@erase "audiooutmodule.def"
	-@erase "audiooutmodule.h"
	-@erase "audiooutmodule_auto.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../audioinmodule" /I "../../../types/src/stringtype" /I "../../../types/src/audiotype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "audiooutmodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\audiooutmodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\audiooutmodule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\audiooutmodule.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\audiooutmodule.def" /out:"$(OUTDIR)\audiooutmodule.dll" /implib:"$(OUTDIR)\audiooutmodule.lib" /pdbtype:sept 
DEF_FILE= \
	".\audiooutmodule.def"
LINK32_OBJS= \
	"$(INTDIR)\a_cvt.obj" \
	"$(INTDIR)\audiooutmodule.obj" \
	"$(INTDIR)\audiooutmodule_auto.obj" \
	"$(INTDIR)\outbuffer.obj" \
	"$(INTDIR)\waveoutdriver.obj"

"$(OUTDIR)\audiooutmodule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\audiooutmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\audiooutmodule_auto.c" ".\audiooutmodule.h" ".\audiooutmodule.def" "$(OUTDIR)\audiooutmodule.dll"
   copy .\Debug\audiooutmodule.dll ..\..\..\dlls\modules
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("audiooutmodule.dep")
!INCLUDE "audiooutmodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "audiooutmodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "audiooutmodule - Win32 Release" || "$(CFG)" == "audiooutmodule - Win32 Debug"
SOURCE=..\audioinmodule\a_cvt.cpp

"$(INTDIR)\a_cvt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\audiooutmodule.cpp

"$(INTDIR)\audiooutmodule.obj" : $(SOURCE) "$(INTDIR)" ".\audiooutmodule.h"


SOURCE=.\audiooutmodule_auto.c

"$(INTDIR)\audiooutmodule_auto.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\outbuffer.c

"$(INTDIR)\outbuffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\waveoutdriver.cpp

"$(INTDIR)\waveoutdriver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\audiooutmodule.spec

!IF  "$(CFG)" == "audiooutmodule - Win32 Release"

InputPath=.\audiooutmodule.spec
InputName=audiooutmodule

".\audiooutmodule.h"	".\audiooutmodule_auto.c"	".\audiooutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ELSEIF  "$(CFG)" == "audiooutmodule - Win32 Debug"

InputPath=.\audiooutmodule.spec
InputName=audiooutmodule

".\audiooutmodule.h"	".\audiooutmodule_auto.c"	".\audiooutmodule.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ..\..\pluc.py c $(InputName).spec 
	python ..\..\pluc.py h $(InputName).spec 
	python ..\..\pluc.py def $(InputName).spec
<< 
	

!ENDIF 


!ENDIF 

