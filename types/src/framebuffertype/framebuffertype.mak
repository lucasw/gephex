# Microsoft Developer Studio Generated NMAKE File, Based on framebuffertype.dsp
!IF "$(CFG)" == ""
CFG=framebuffertype - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. framebuffertype - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "framebuffertype - Win32 Release" && "$(CFG)" != "framebuffertype - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "framebuffertype.mak" CFG="framebuffertype - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "framebuffertype - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "framebuffertype - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "framebuffertype - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\framebuffertype.dll"


CLEAN :
	-@erase "$(INTDIR)\framebuffertype.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\framebuffertype.dll"
	-@erase "$(OUTDIR)\framebuffertype.exp"
	-@erase "$(OUTDIR)\framebuffertype.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEBUFFERTYPE_EXPORTS" /D "WIN32" /D "NDEBUG" /D "VERBOSE_ENGINE" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\framebuffertype.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\framebuffertype.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\framebuffertype.pdb" /machine:I386 /def:".\framebuffertype.def" /out:"$(OUTDIR)\framebuffertype.dll" /implib:"$(OUTDIR)\framebuffertype.lib" 
DEF_FILE= \
	".\framebuffertype.def"
LINK32_OBJS= \
	"$(INTDIR)\framebuffertype.obj"

"$(OUTDIR)\framebuffertype.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\framebuffertype.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\framebuffertype.dll"
   copy .\Release\framebuffertype.dll ..\..\..\dlls\types
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "framebuffertype - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\framebuffertype.dll"


CLEAN :
	-@erase "$(INTDIR)\framebuffertype.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\framebuffertype.dll"
	-@erase "$(OUTDIR)\framebuffertype.exp"
	-@erase "$(OUTDIR)\framebuffertype.ilk"
	-@erase "$(OUTDIR)\framebuffertype.lib"
	-@erase "$(OUTDIR)\framebuffertype.pdb"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEBUFFERTYPE_EXPORTS" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\framebuffertype.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\framebuffertype.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\framebuffertype.pdb" /debug /machine:I386 /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\framebuffertype.def" /out:"$(OUTDIR)\framebuffertype.dll" /implib:"$(OUTDIR)\framebuffertype.lib" /pdbtype:sept 
DEF_FILE= \
	".\framebuffertype.def"
LINK32_OBJS= \
	"$(INTDIR)\framebuffertype.obj"

"$(OUTDIR)\framebuffertype.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\framebuffertype.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "..\..\..\config.h" "$(OUTDIR)\framebuffertype.dll"
   copy .\Debug\framebuffertype.dll ..\..\..\dlls\types
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("framebuffertype.dep")
!INCLUDE "framebuffertype.dep"
!ELSE 
!MESSAGE Warning: cannot find "framebuffertype.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "framebuffertype - Win32 Release" || "$(CFG)" == "framebuffertype - Win32 Debug"
SOURCE=.\framebuffertype.c

"$(INTDIR)\framebuffertype.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "framebuffertype - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "framebuffertype - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

