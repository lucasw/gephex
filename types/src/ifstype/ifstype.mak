# Microsoft Developer Studio Generated NMAKE File, Based on ifstype.dsp
!IF "$(CFG)" == ""
CFG=ifstype - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ifstype - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ifstype - Win32 Release" && "$(CFG)" != "ifstype - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ifstype.mak" CFG="ifstype - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ifstype - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifstype - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ifstype - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ifstype.dll"


CLEAN :
	-@erase "$(INTDIR)\ifstype.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ifstype.dll"
	-@erase "$(OUTDIR)\ifstype.exp"
	-@erase "$(OUTDIR)\ifstype.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IFSTYPE_EXPORTS" /D "WIN32" /D "NDEBUG" /D "VERBOSE_ENGINE" /Fp"$(INTDIR)\ifstype.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifstype.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ifstype.pdb" /machine:I386 /def:".\ifstype.def" /out:"$(OUTDIR)\ifstype.dll" /implib:"$(OUTDIR)\ifstype.lib" 
DEF_FILE= \
	".\ifstype.def"
LINK32_OBJS= \
	"$(INTDIR)\ifstype.obj"

"$(OUTDIR)\ifstype.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\ifstype.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ifstype.dll"
   copy .\Release\ifstype.dll ..\..\..\dlls\types
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ifstype - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ifstype.dll"


CLEAN :
	-@erase "$(INTDIR)\ifstype.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ifstype.dll"
	-@erase "$(OUTDIR)\ifstype.exp"
	-@erase "$(OUTDIR)\ifstype.ilk"
	-@erase "$(OUTDIR)\ifstype.lib"
	-@erase "$(OUTDIR)\ifstype.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "../../engine" /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IFSTYPE_EXPORTS" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\ifstype.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ifstype.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ifstype.pdb" /debug /machine:I386 /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /def:".\ifstype.def" /out:"$(OUTDIR)\ifstype.dll" /implib:"$(OUTDIR)\ifstype.lib" /pdbtype:sept 
DEF_FILE= \
	".\ifstype.def"
LINK32_OBJS= \
	"$(INTDIR)\ifstype.obj"

"$(OUTDIR)\ifstype.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\ifstype.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ifstype.dll"
   copy .\Debug\ifstype.dll ..\..\..\dlls\types
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ifstype.dep")
!INCLUDE "ifstype.dep"
!ELSE 
!MESSAGE Warning: cannot find "ifstype.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ifstype - Win32 Release" || "$(CFG)" == "ifstype - Win32 Debug"
SOURCE=.\ifstype.c

"$(INTDIR)\ifstype.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

