# Microsoft Developer Studio Generated NMAKE File, Based on libcolorconv.dsp
!IF "$(CFG)" == ""
CFG=libcolorconv - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. libcolorconv - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "libcolorconv - Win32 Release" && "$(CFG)" != "libcolorconv - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "libcolorconv.mak" CFG="libcolorconv - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "libcolorconv - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "libcolorconv - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "libcolorconv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\libcolorconv.lib"


CLEAN :
	-@erase "$(INTDIR)\libcolorconv.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\libcolorconv.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../" /I "../../../util/include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\libcolorconv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libcolorconv.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libcolorconv.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libcolorconv.obj"

"$(OUTDIR)\libcolorconv.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libcolorconv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\libcolorconv.lib"


CLEAN :
	-@erase "$(INTDIR)\libcolorconv.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\libcolorconv.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../" /I "../../../util/include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\libcolorconv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libcolorconv.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libcolorconv.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libcolorconv.obj"

"$(OUTDIR)\libcolorconv.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("libcolorconv.dep")
!INCLUDE "libcolorconv.dep"
!ELSE 
!MESSAGE Warning: cannot find "libcolorconv.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "libcolorconv - Win32 Release" || "$(CFG)" == "libcolorconv - Win32 Debug"
SOURCE=.\libcolorconv.cpp

"$(INTDIR)\libcolorconv.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

