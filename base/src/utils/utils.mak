# Microsoft Developer Studio Generated NMAKE File, Based on utils.dsp
!IF "$(CFG)" == ""
CFG=utils - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. utils - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "utils - Win32 Release" && "$(CFG)" != "utils - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "utils.mak" CFG="utils - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "utils - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "utils - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "utils - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\utils.lib"


CLEAN :
	-@erase "$(INTDIR)\buffer.obj"
	-@erase "$(INTDIR)\bufferstream.obj"
	-@erase "$(INTDIR)\bufferutils.obj"
	-@erase "$(INTDIR)\circularbuffer.obj"
	-@erase "$(INTDIR)\configfile.obj"
	-@erase "$(INTDIR)\configmanager.obj"
	-@erase "$(INTDIR)\filesystem.obj"
	-@erase "$(INTDIR)\itokenizer.obj"
	-@erase "$(INTDIR)\sharedlibrary.obj"
	-@erase "$(INTDIR)\spawn.obj"
	-@erase "$(INTDIR)\streamlogger.obj"
	-@erase "$(INTDIR)\streamtokenizer.obj"
	-@erase "$(INTDIR)\string_.obj"
	-@erase "$(INTDIR)\stringtokenizer.obj"
	-@erase "$(INTDIR)\structreader.obj"
	-@erase "$(INTDIR)\structscanner.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmlutils.obj"
	-@erase "$(OUTDIR)\utils.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../../../" /I "../../../util/include/compatibility" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\utils.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\utils.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\utils.lib" 
LIB32_OBJS= \
	"$(INTDIR)\buffer.obj" \
	"$(INTDIR)\bufferstream.obj" \
	"$(INTDIR)\bufferutils.obj" \
	"$(INTDIR)\circularbuffer.obj" \
	"$(INTDIR)\configfile.obj" \
	"$(INTDIR)\filesystem.obj" \
	"$(INTDIR)\itokenizer.obj" \
	"$(INTDIR)\sharedlibrary.obj" \
	"$(INTDIR)\spawn.obj" \
	"$(INTDIR)\streamlogger.obj" \
	"$(INTDIR)\streamtokenizer.obj" \
	"$(INTDIR)\string_.obj" \
	"$(INTDIR)\stringtokenizer.obj" \
	"$(INTDIR)\structreader.obj" \
	"$(INTDIR)\structscanner.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\xmlutils.obj" \
	"$(INTDIR)\configmanager.obj"

"$(OUTDIR)\utils.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "utils - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "$(OUTDIR)\utils.lib"


CLEAN :
	-@erase "$(INTDIR)\buffer.obj"
	-@erase "$(INTDIR)\bufferstream.obj"
	-@erase "$(INTDIR)\bufferutils.obj"
	-@erase "$(INTDIR)\circularbuffer.obj"
	-@erase "$(INTDIR)\configfile.obj"
	-@erase "$(INTDIR)\configmanager.obj"
	-@erase "$(INTDIR)\filesystem.obj"
	-@erase "$(INTDIR)\itokenizer.obj"
	-@erase "$(INTDIR)\sharedlibrary.obj"
	-@erase "$(INTDIR)\spawn.obj"
	-@erase "$(INTDIR)\streamlogger.obj"
	-@erase "$(INTDIR)\streamtokenizer.obj"
	-@erase "$(INTDIR)\string_.obj"
	-@erase "$(INTDIR)\stringtokenizer.obj"
	-@erase "$(INTDIR)\structreader.obj"
	-@erase "$(INTDIR)\structscanner.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xmlutils.obj"
	-@erase "$(OUTDIR)\utils.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../util/include/compatibility" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\utils.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\utils.lib" 
LIB32_OBJS= \
	"$(INTDIR)\buffer.obj" \
	"$(INTDIR)\bufferstream.obj" \
	"$(INTDIR)\bufferutils.obj" \
	"$(INTDIR)\circularbuffer.obj" \
	"$(INTDIR)\configfile.obj" \
	"$(INTDIR)\filesystem.obj" \
	"$(INTDIR)\itokenizer.obj" \
	"$(INTDIR)\sharedlibrary.obj" \
	"$(INTDIR)\spawn.obj" \
	"$(INTDIR)\streamlogger.obj" \
	"$(INTDIR)\streamtokenizer.obj" \
	"$(INTDIR)\string_.obj" \
	"$(INTDIR)\stringtokenizer.obj" \
	"$(INTDIR)\structreader.obj" \
	"$(INTDIR)\structscanner.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\xmlutils.obj" \
	"$(INTDIR)\configmanager.obj"

"$(OUTDIR)\utils.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("utils.dep")
!INCLUDE "utils.dep"
!ELSE 
!MESSAGE Warning: cannot find "utils.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "utils - Win32 Release" || "$(CFG)" == "utils - Win32 Debug"
SOURCE=.\buffer.cpp

"$(INTDIR)\buffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\bufferstream.cpp

"$(INTDIR)\bufferstream.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\bufferutils.cpp

"$(INTDIR)\bufferutils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\circularbuffer.cpp

"$(INTDIR)\circularbuffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\configfile.cpp

"$(INTDIR)\configfile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\configmanager.cpp

"$(INTDIR)\configmanager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\filesystem.cpp

"$(INTDIR)\filesystem.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\itokenizer.cpp

"$(INTDIR)\itokenizer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\sharedlibrary.cpp

"$(INTDIR)\sharedlibrary.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\spawn.cpp

"$(INTDIR)\spawn.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\streamlogger.cpp

"$(INTDIR)\streamlogger.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\streamtokenizer.cpp

"$(INTDIR)\streamtokenizer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\string_.cpp

"$(INTDIR)\string_.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\stringtokenizer.cpp

"$(INTDIR)\stringtokenizer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\structreader.cpp

"$(INTDIR)\structreader.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\structscanner.cpp

"$(INTDIR)\structscanner.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\timing.cpp

"$(INTDIR)\timing.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xmlutils.cpp

"$(INTDIR)\xmlutils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "utils - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "utils - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

