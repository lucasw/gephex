# Microsoft Developer Studio Generated NMAKE File, Based on model.dsp
!IF "$(CFG)" == ""
CFG=model - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. model - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "model - Win32 Release" && "$(CFG)" != "model - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "model.mak" CFG="model - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "model - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "model - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "model - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\model.lib"


CLEAN :
	-@erase "$(INTDIR)\controlvalueset.obj"
	-@erase "$(INTDIR)\graph.obj"
	-@erase "$(INTDIR)\graphconnection.obj"
	-@erase "$(INTDIR)\graphfilesystem.obj"
	-@erase "$(INTDIR)\graphnode.obj"
	-@erase "$(INTDIR)\graphparser.obj"
	-@erase "$(INTDIR)\graphserial.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\model.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../../base/src" /I "../../../" /D "_LIB" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\model.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\model.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\model.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlvalueset.obj" \
	"$(INTDIR)\graph.obj" \
	"$(INTDIR)\graphconnection.obj" \
	"$(INTDIR)\graphfilesystem.obj" \
	"$(INTDIR)\graphnode.obj" \
	"$(INTDIR)\graphparser.obj" \
	"$(INTDIR)\graphserial.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\model.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "model - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\model.lib"


CLEAN :
	-@erase "$(INTDIR)\controlvalueset.obj"
	-@erase "$(INTDIR)\graph.obj"
	-@erase "$(INTDIR)\graphconnection.obj"
	-@erase "$(INTDIR)\graphfilesystem.obj"
	-@erase "$(INTDIR)\graphnode.obj"
	-@erase "$(INTDIR)\graphparser.obj"
	-@erase "$(INTDIR)\graphserial.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\model.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I ".." /I "../../../base/src" /I "../../../" /D "_LIB" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\model.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\model.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\model.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlvalueset.obj" \
	"$(INTDIR)\graph.obj" \
	"$(INTDIR)\graphconnection.obj" \
	"$(INTDIR)\graphfilesystem.obj" \
	"$(INTDIR)\graphnode.obj" \
	"$(INTDIR)\graphparser.obj" \
	"$(INTDIR)\graphserial.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\model.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("model.dep")
!INCLUDE "model.dep"
!ELSE 
!MESSAGE Warning: cannot find "model.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "model - Win32 Release" || "$(CFG)" == "model - Win32 Debug"
SOURCE=.\controlvalueset.cpp

"$(INTDIR)\controlvalueset.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graph.cpp

"$(INTDIR)\graph.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphconnection.cpp

"$(INTDIR)\graphconnection.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphfilesystem.cpp

"$(INTDIR)\graphfilesystem.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphnode.cpp

"$(INTDIR)\graphnode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphparser.cpp

"$(INTDIR)\graphparser.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphserial.cpp

"$(INTDIR)\graphserial.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\model.cpp

"$(INTDIR)\model.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "model - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "model - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

