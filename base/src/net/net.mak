# Microsoft Developer Studio Generated NMAKE File, Based on net.dsp
!IF "$(CFG)" == ""
CFG=net - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. net - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "net - Win32 Release" && "$(CFG)" != "net - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "net.mak" CFG="net - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "net - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "net - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "net - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "$(OUTDIR)\net.lib"


CLEAN :
	-@erase "$(INTDIR)\convertbin.obj"
	-@erase "$(INTDIR)\domainclientsocket.obj"
	-@erase "$(INTDIR)\domainserversocket.obj"
	-@erase "$(INTDIR)\fdsocket.obj"
	-@erase "$(INTDIR)\fhsocket.obj"
	-@erase "$(INTDIR)\isocket.obj"
	-@erase "$(INTDIR)\namedpipeclientsocket.obj"
	-@erase "$(INTDIR)\namedpipeserversocket.obj"
	-@erase "$(INTDIR)\netexceptions.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\socketadaptor.obj"
	-@erase "$(INTDIR)\socketutils.obj"
	-@erase "$(INTDIR)\sotimeout.obj"
	-@erase "$(INTDIR)\tagutils.obj"
	-@erase "$(INTDIR)\tcpclientsocket.obj"
	-@erase "$(INTDIR)\tcpserversocket.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\net.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../../" /I "../../../util/include" /I "../../../util/include/compatibility" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\net.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\net.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\net.lib" 
LIB32_OBJS= \
	"$(INTDIR)\convertbin.obj" \
	"$(INTDIR)\domainclientsocket.obj" \
	"$(INTDIR)\domainserversocket.obj" \
	"$(INTDIR)\fdsocket.obj" \
	"$(INTDIR)\fhsocket.obj" \
	"$(INTDIR)\isocket.obj" \
	"$(INTDIR)\namedpipeclientsocket.obj" \
	"$(INTDIR)\namedpipeserversocket.obj" \
	"$(INTDIR)\netexceptions.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\socketadaptor.obj" \
	"$(INTDIR)\socketutils.obj" \
	"$(INTDIR)\sotimeout.obj" \
	"$(INTDIR)\tagutils.obj" \
	"$(INTDIR)\tcpclientsocket.obj" \
	"$(INTDIR)\tcpserversocket.obj"

"$(OUTDIR)\net.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "net - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\net.lib"


CLEAN :
	-@erase "$(INTDIR)\convertbin.obj"
	-@erase "$(INTDIR)\domainclientsocket.obj"
	-@erase "$(INTDIR)\domainserversocket.obj"
	-@erase "$(INTDIR)\fdsocket.obj"
	-@erase "$(INTDIR)\fhsocket.obj"
	-@erase "$(INTDIR)\isocket.obj"
	-@erase "$(INTDIR)\namedpipeclientsocket.obj"
	-@erase "$(INTDIR)\namedpipeserversocket.obj"
	-@erase "$(INTDIR)\netexceptions.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\socketadaptor.obj"
	-@erase "$(INTDIR)\socketutils.obj"
	-@erase "$(INTDIR)\sotimeout.obj"
	-@erase "$(INTDIR)\tagutils.obj"
	-@erase "$(INTDIR)\tcpclientsocket.obj"
	-@erase "$(INTDIR)\tcpserversocket.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\net.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GX /ZI /Od /I ".." /I "../../../" /I "../../../util/include" /I "../../../util/include/compatibility" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\net.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\net.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\net.lib" 
LIB32_OBJS= \
	"$(INTDIR)\convertbin.obj" \
	"$(INTDIR)\domainclientsocket.obj" \
	"$(INTDIR)\domainserversocket.obj" \
	"$(INTDIR)\fdsocket.obj" \
	"$(INTDIR)\fhsocket.obj" \
	"$(INTDIR)\isocket.obj" \
	"$(INTDIR)\namedpipeclientsocket.obj" \
	"$(INTDIR)\namedpipeserversocket.obj" \
	"$(INTDIR)\netexceptions.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\socketadaptor.obj" \
	"$(INTDIR)\socketutils.obj" \
	"$(INTDIR)\sotimeout.obj" \
	"$(INTDIR)\tagutils.obj" \
	"$(INTDIR)\tcpclientsocket.obj" \
	"$(INTDIR)\tcpserversocket.obj"

"$(OUTDIR)\net.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("net.dep")
!INCLUDE "net.dep"
!ELSE 
!MESSAGE Warning: cannot find "net.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "net - Win32 Release" || "$(CFG)" == "net - Win32 Debug"
SOURCE=.\convertbin.cpp

"$(INTDIR)\convertbin.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\domainclientsocket.cpp

"$(INTDIR)\domainclientsocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\domainserversocket.cpp

"$(INTDIR)\domainserversocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\fdsocket.cpp

"$(INTDIR)\fdsocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\fhsocket.cpp

"$(INTDIR)\fhsocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\isocket.cpp

"$(INTDIR)\isocket.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\namedpipeclientsocket.cpp

"$(INTDIR)\namedpipeclientsocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\namedpipeserversocket.cpp

"$(INTDIR)\namedpipeserversocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\netexceptions.cpp

"$(INTDIR)\netexceptions.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\protocol.cpp

"$(INTDIR)\protocol.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\socketadaptor.cpp

"$(INTDIR)\socketadaptor.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\socketutils.cpp

"$(INTDIR)\socketutils.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\sotimeout.cpp

"$(INTDIR)\sotimeout.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tagutils.cpp

"$(INTDIR)\tagutils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tcpclientsocket.cpp

"$(INTDIR)\tcpclientsocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\tcpserversocket.cpp

"$(INTDIR)\tcpserversocket.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "net - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "net - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

