# Microsoft Developer Studio Generated NMAKE File, Based on netinterfaces.dsp
!IF "$(CFG)" == ""
CFG=netinterfaces - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. netinterfaces - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "netinterfaces - Win32 Release" && "$(CFG)" != "netinterfaces - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "netinterfaces.mak" CFG="netinterfaces - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "netinterfaces - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "netinterfaces - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : ".\typeclasssendernet.h" ".\typeclasssendernet.cpp" ".\typeclassreceivernet.h" ".\typeclassreceivernet.cpp" ".\typeclassinfosendernet.h" ".\typeclassinfosendernet.cpp" ".\typeclassinforeceivernet.h" ".\typeclassinforeceivernet.cpp" ".\smartcontrolvaluesendernet.h" ".\smartcontrolvaluesendernet.cpp" ".\smartcontrolvaluereceivernet.h" ".\smartcontrolvaluereceivernet.cpp" ".\serializedgraphsendernet.h" ".\serializedgraphsendernet.cpp" ".\serializedgraphreceivernet.h" ".\serializedgraphreceivernet.cpp" ".\rendererstatussendernet.h" ".\rendererstatussendernet.cpp" ".\rendererstatusreceivernet.h" ".\rendererstatusreceivernet.cpp" ".\renderercontrolsendernet.h" ".\renderercontrolsendernet.cpp" ".\renderercontrolreceivernet.h" ".\renderercontrolreceivernet.cpp" ".\modulestatisticssmartsendernet.h" ".\modulestatisticssmartsendernet.cpp" ".\modulestatisticssmartreceivernet.h" ".\modulestatisticssmartreceivernet.cpp" ".\modulestatisticssendernet.h" ".\modulestatisticssendernet.cpp" ".\modulestatisticsreceivernet.h" ".\modulestatisticsreceivernet.cpp" ".\moduledatasendernet.h" ".\moduledatasendernet.cpp" ".\moduledatareceivernet.h" ".\moduledatareceivernet.cpp"\
 ".\moduleconstructionsmartsendernet.h" ".\moduleconstructionsmartsendernet.cpp" ".\moduleconstructionsmartreceivernet.h" ".\moduleconstructionsmartreceivernet.cpp" ".\moduleconstructiondumbsendernet.h" ".\moduleconstructiondumbsendernet.cpp" ".\moduleconstructiondumbreceivernet.h" ".\moduleconstructiondumbreceivernet.cpp" ".\moduleclassspecsendernet.h" ".\moduleclassspecsendernet.cpp" ".\moduleclassspecreceivernet.h" ".\moduleclassspecreceivernet.cpp" ".\moduleclasssendernet.h" ".\moduleclasssendernet.cpp" ".\moduleclassreceivernet.h" ".\moduleclassreceivernet.cpp" ".\moduleclassnamesendernet.h" ".\moduleclassnamesendernet.cpp" ".\moduleclassnamereceivernet.h" ".\moduleclassnamereceivernet.cpp" ".\moduleclassinfosendernet.h" ".\moduleclassinfosendernet.cpp" ".\moduleclassinforeceivernet.h" ".\moduleclassinforeceivernet.cpp" ".\modelstatussendernet.h" ".\modelstatussendernet.cpp" ".\modelstatusreceivernet.h" ".\modelstatusreceivernet.cpp" ".\modelcontrolsendernet.h" ".\modelcontrolsendernet.cpp" ".\modelcontrolreceivernet.h" ".\modelcontrolreceivernet.cpp" ".\graphnamesendernet.h" ".\graphnamesendernet.cpp" ".\graphnamereceivernet.h" ".\graphnamereceivernet.cpp"\
 ".\graphdatasendernet.h" ".\graphdatasendernet.cpp" ".\graphdatareceivernet.h" ".\graphdatareceivernet.cpp" ".\errorsendernet.h" ".\errorsendernet.cpp" ".\errorreceivernet.h" ".\errorreceivernet.cpp" ".\enginecontrolsendernet.h" ".\enginecontrolsendernet.cpp" ".\enginecontrolreceivernet.h" ".\enginecontrolreceivernet.cpp" ".\controlvaluesendernet.h" ".\controlvaluesendernet.cpp" ".\controlvaluereceivernet.h" ".\controlvaluereceivernet.cpp" "$(OUTDIR)\netinterfaces.lib"


CLEAN :
	-@erase "$(INTDIR)\controlvaluereceivernet.obj"
	-@erase "$(INTDIR)\controlvaluesendernet.obj"
	-@erase "$(INTDIR)\enginecontrolreceivernet.obj"
	-@erase "$(INTDIR)\enginecontrolsendernet.obj"
	-@erase "$(INTDIR)\errorreceivernet.obj"
	-@erase "$(INTDIR)\errorsendernet.obj"
	-@erase "$(INTDIR)\graphdatareceivernet.obj"
	-@erase "$(INTDIR)\graphdatasendernet.obj"
	-@erase "$(INTDIR)\graphnamereceivernet.obj"
	-@erase "$(INTDIR)\graphnamesendernet.obj"
	-@erase "$(INTDIR)\modelcontrolreceivernet.obj"
	-@erase "$(INTDIR)\modelcontrolsendernet.obj"
	-@erase "$(INTDIR)\modelstatusreceivernet.obj"
	-@erase "$(INTDIR)\modelstatussendernet.obj"
	-@erase "$(INTDIR)\moduleclassinforeceivernet.obj"
	-@erase "$(INTDIR)\moduleclassinfosendernet.obj"
	-@erase "$(INTDIR)\moduleclassnamereceivernet.obj"
	-@erase "$(INTDIR)\moduleclassnamesendernet.obj"
	-@erase "$(INTDIR)\moduleconstructiondumbreceivernet.obj"
	-@erase "$(INTDIR)\moduleconstructiondumbsendernet.obj"
	-@erase "$(INTDIR)\moduledatareceivernet.obj"
	-@erase "$(INTDIR)\moduledatasendernet.obj"
	-@erase "$(INTDIR)\modulestatisticsreceivernet.obj"
	-@erase "$(INTDIR)\modulestatisticssendernet.obj"
	-@erase "$(INTDIR)\renderercontrolreceivernet.obj"
	-@erase "$(INTDIR)\renderercontrolsendernet.obj"
	-@erase "$(INTDIR)\rendererstatusreceivernet.obj"
	-@erase "$(INTDIR)\rendererstatussendernet.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\netinterfaces.lib"
	-@erase "controlvaluereceivernet.cpp"
	-@erase "controlvaluereceivernet.h"
	-@erase "controlvaluesendernet.cpp"
	-@erase "controlvaluesendernet.h"
	-@erase "enginecontrolreceivernet.cpp"
	-@erase "enginecontrolreceivernet.h"
	-@erase "enginecontrolsendernet.cpp"
	-@erase "enginecontrolsendernet.h"
	-@erase "errorreceivernet.cpp"
	-@erase "errorreceivernet.h"
	-@erase "errorsendernet.cpp"
	-@erase "errorsendernet.h"
	-@erase "graphdatareceivernet.cpp"
	-@erase "graphdatareceivernet.h"
	-@erase "graphdatasendernet.cpp"
	-@erase "graphdatasendernet.h"
	-@erase "graphnamereceivernet.cpp"
	-@erase "graphnamereceivernet.h"
	-@erase "graphnamesendernet.cpp"
	-@erase "graphnamesendernet.h"
	-@erase "modelcontrolreceivernet.cpp"
	-@erase "modelcontrolreceivernet.h"
	-@erase "modelcontrolsendernet.cpp"
	-@erase "modelcontrolsendernet.h"
	-@erase "modelstatusreceivernet.cpp"
	-@erase "modelstatusreceivernet.h"
	-@erase "modelstatussendernet.cpp"
	-@erase "modelstatussendernet.h"
	-@erase "moduleclassinforeceivernet.cpp"
	-@erase "moduleclassinforeceivernet.h"
	-@erase "moduleclassinfosendernet.cpp"
	-@erase "moduleclassinfosendernet.h"
	-@erase "moduleclassnamereceivernet.cpp"
	-@erase "moduleclassnamereceivernet.h"
	-@erase "moduleclassnamesendernet.cpp"
	-@erase "moduleclassnamesendernet.h"
	-@erase "moduleclassreceivernet.cpp"
	-@erase "moduleclassreceivernet.h"
	-@erase "moduleclasssendernet.cpp"
	-@erase "moduleclasssendernet.h"
	-@erase "moduleclassspecreceivernet.cpp"
	-@erase "moduleclassspecreceivernet.h"
	-@erase "moduleclassspecsendernet.cpp"
	-@erase "moduleclassspecsendernet.h"
	-@erase "moduleconstructiondumbreceivernet.cpp"
	-@erase "moduleconstructiondumbreceivernet.h"
	-@erase "moduleconstructiondumbsendernet.cpp"
	-@erase "moduleconstructiondumbsendernet.h"
	-@erase "moduleconstructionsmartreceivernet.cpp"
	-@erase "moduleconstructionsmartreceivernet.h"
	-@erase "moduleconstructionsmartsendernet.cpp"
	-@erase "moduleconstructionsmartsendernet.h"
	-@erase "moduledatareceivernet.cpp"
	-@erase "moduledatareceivernet.h"
	-@erase "moduledatasendernet.cpp"
	-@erase "moduledatasendernet.h"
	-@erase "modulestatisticsreceivernet.cpp"
	-@erase "modulestatisticsreceivernet.h"
	-@erase "modulestatisticssendernet.cpp"
	-@erase "modulestatisticssendernet.h"
	-@erase "modulestatisticssmartreceivernet.cpp"
	-@erase "modulestatisticssmartreceivernet.h"
	-@erase "modulestatisticssmartsendernet.cpp"
	-@erase "modulestatisticssmartsendernet.h"
	-@erase "renderercontrolreceivernet.cpp"
	-@erase "renderercontrolreceivernet.h"
	-@erase "renderercontrolsendernet.cpp"
	-@erase "renderercontrolsendernet.h"
	-@erase "rendererstatusreceivernet.cpp"
	-@erase "rendererstatusreceivernet.h"
	-@erase "rendererstatussendernet.cpp"
	-@erase "rendererstatussendernet.h"
	-@erase "serializedgraphreceivernet.cpp"
	-@erase "serializedgraphreceivernet.h"
	-@erase "serializedgraphsendernet.cpp"
	-@erase "serializedgraphsendernet.h"
	-@erase "smartcontrolvaluereceivernet.cpp"
	-@erase "smartcontrolvaluereceivernet.h"
	-@erase "smartcontrolvaluesendernet.cpp"
	-@erase "smartcontrolvaluesendernet.h"
	-@erase "typeclassinforeceivernet.cpp"
	-@erase "typeclassinforeceivernet.h"
	-@erase "typeclassinfosendernet.cpp"
	-@erase "typeclassinfosendernet.h"
	-@erase "typeclassreceivernet.cpp"
	-@erase "typeclassreceivernet.h"
	-@erase "typeclasssendernet.cpp"
	-@erase "typeclasssendernet.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../" /I "../../../util/src/include" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\netinterfaces.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netinterfaces.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\netinterfaces.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlvaluereceivernet.obj" \
	"$(INTDIR)\controlvaluesendernet.obj" \
	"$(INTDIR)\enginecontrolreceivernet.obj" \
	"$(INTDIR)\enginecontrolsendernet.obj" \
	"$(INTDIR)\errorreceivernet.obj" \
	"$(INTDIR)\errorsendernet.obj" \
	"$(INTDIR)\graphdatareceivernet.obj" \
	"$(INTDIR)\graphdatasendernet.obj" \
	"$(INTDIR)\graphnamereceivernet.obj" \
	"$(INTDIR)\graphnamesendernet.obj" \
	"$(INTDIR)\modelcontrolreceivernet.obj" \
	"$(INTDIR)\modelcontrolsendernet.obj" \
	"$(INTDIR)\modelstatusreceivernet.obj" \
	"$(INTDIR)\modelstatussendernet.obj" \
	"$(INTDIR)\moduleclassinforeceivernet.obj" \
	"$(INTDIR)\moduleclassinfosendernet.obj" \
	"$(INTDIR)\moduleclassnamereceivernet.obj" \
	"$(INTDIR)\moduleclassnamesendernet.obj" \
	"$(INTDIR)\moduleconstructiondumbreceivernet.obj" \
	"$(INTDIR)\moduleconstructiondumbsendernet.obj" \
	"$(INTDIR)\moduledatareceivernet.obj" \
	"$(INTDIR)\moduledatasendernet.obj" \
	"$(INTDIR)\modulestatisticsreceivernet.obj" \
	"$(INTDIR)\modulestatisticssendernet.obj" \
	"$(INTDIR)\renderercontrolreceivernet.obj" \
	"$(INTDIR)\renderercontrolsendernet.obj" \
	"$(INTDIR)\rendererstatusreceivernet.obj" \
	"$(INTDIR)\rendererstatussendernet.obj"

"$(OUTDIR)\netinterfaces.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : ".\typeclasssendernet.h" ".\typeclasssendernet.cpp" ".\typeclassreceivernet.h" ".\typeclassreceivernet.cpp" ".\typeclassinfosendernet.h" ".\typeclassinfosendernet.cpp" ".\typeclassinforeceivernet.h" ".\typeclassinforeceivernet.cpp" ".\smartcontrolvaluesendernet.h" ".\smartcontrolvaluesendernet.cpp" ".\smartcontrolvaluereceivernet.h" ".\smartcontrolvaluereceivernet.cpp" ".\serializedgraphsendernet.h" ".\serializedgraphsendernet.cpp" ".\serializedgraphreceivernet.h" ".\serializedgraphreceivernet.cpp" ".\modulestatisticssmartsendernet.h" ".\modulestatisticssmartsendernet.cpp" ".\modulestatisticssmartreceivernet.h" ".\modulestatisticssmartreceivernet.cpp" ".\moduleconstructionsmartsendernet.h" ".\moduleconstructionsmartsendernet.cpp" ".\moduleconstructionsmartreceivernet.h" ".\moduleconstructionsmartreceivernet.cpp" ".\moduleclassspecsendernet.h" ".\moduleclassspecsendernet.cpp" ".\moduleclassspecreceivernet.h" ".\moduleclassspecreceivernet.cpp" ".\moduleclasssendernet.h" ".\moduleclasssendernet.cpp" ".\moduleclassreceivernet.h" ".\moduleclassreceivernet.cpp" "$(OUTDIR)\netinterfaces.lib"


CLEAN :
	-@erase "$(INTDIR)\controlvaluereceivernet.obj"
	-@erase "$(INTDIR)\controlvaluesendernet.obj"
	-@erase "$(INTDIR)\enginecontrolreceivernet.obj"
	-@erase "$(INTDIR)\enginecontrolsendernet.obj"
	-@erase "$(INTDIR)\errorreceivernet.obj"
	-@erase "$(INTDIR)\errorsendernet.obj"
	-@erase "$(INTDIR)\graphdatareceivernet.obj"
	-@erase "$(INTDIR)\graphdatasendernet.obj"
	-@erase "$(INTDIR)\graphnamereceivernet.obj"
	-@erase "$(INTDIR)\graphnamesendernet.obj"
	-@erase "$(INTDIR)\modelcontrolreceivernet.obj"
	-@erase "$(INTDIR)\modelcontrolsendernet.obj"
	-@erase "$(INTDIR)\modelstatusreceivernet.obj"
	-@erase "$(INTDIR)\modelstatussendernet.obj"
	-@erase "$(INTDIR)\moduleclassinforeceivernet.obj"
	-@erase "$(INTDIR)\moduleclassinfosendernet.obj"
	-@erase "$(INTDIR)\moduleclassnamereceivernet.obj"
	-@erase "$(INTDIR)\moduleclassnamesendernet.obj"
	-@erase "$(INTDIR)\moduleconstructiondumbreceivernet.obj"
	-@erase "$(INTDIR)\moduleconstructiondumbsendernet.obj"
	-@erase "$(INTDIR)\moduledatareceivernet.obj"
	-@erase "$(INTDIR)\moduledatasendernet.obj"
	-@erase "$(INTDIR)\modulestatisticsreceivernet.obj"
	-@erase "$(INTDIR)\modulestatisticssendernet.obj"
	-@erase "$(INTDIR)\renderercontrolreceivernet.obj"
	-@erase "$(INTDIR)\renderercontrolsendernet.obj"
	-@erase "$(INTDIR)\rendererstatusreceivernet.obj"
	-@erase "$(INTDIR)\rendererstatussendernet.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\netinterfaces.lib"
	-@erase "moduleclassreceivernet.cpp"
	-@erase "moduleclassreceivernet.h"
	-@erase "moduleclasssendernet.cpp"
	-@erase "moduleclasssendernet.h"
	-@erase "moduleclassspecreceivernet.cpp"
	-@erase "moduleclassspecreceivernet.h"
	-@erase "moduleclassspecsendernet.cpp"
	-@erase "moduleclassspecsendernet.h"
	-@erase "moduleconstructionsmartreceivernet.cpp"
	-@erase "moduleconstructionsmartreceivernet.h"
	-@erase "moduleconstructionsmartsendernet.cpp"
	-@erase "moduleconstructionsmartsendernet.h"
	-@erase "modulestatisticssmartreceivernet.cpp"
	-@erase "modulestatisticssmartreceivernet.h"
	-@erase "modulestatisticssmartsendernet.cpp"
	-@erase "modulestatisticssmartsendernet.h"
	-@erase "serializedgraphreceivernet.cpp"
	-@erase "serializedgraphreceivernet.h"
	-@erase "serializedgraphsendernet.cpp"
	-@erase "serializedgraphsendernet.h"
	-@erase "smartcontrolvaluereceivernet.cpp"
	-@erase "smartcontrolvaluereceivernet.h"
	-@erase "smartcontrolvaluesendernet.cpp"
	-@erase "smartcontrolvaluesendernet.h"
	-@erase "typeclassinforeceivernet.cpp"
	-@erase "typeclassinforeceivernet.h"
	-@erase "typeclassinfosendernet.cpp"
	-@erase "typeclassinfosendernet.h"
	-@erase "typeclassreceivernet.cpp"
	-@erase "typeclassreceivernet.h"
	-@erase "typeclasssendernet.cpp"
	-@erase "typeclasssendernet.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "../../" /I "../../../util/include" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\netinterfaces.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netinterfaces.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\netinterfaces.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controlvaluereceivernet.obj" \
	"$(INTDIR)\controlvaluesendernet.obj" \
	"$(INTDIR)\enginecontrolreceivernet.obj" \
	"$(INTDIR)\enginecontrolsendernet.obj" \
	"$(INTDIR)\errorreceivernet.obj" \
	"$(INTDIR)\errorsendernet.obj" \
	"$(INTDIR)\graphdatareceivernet.obj" \
	"$(INTDIR)\graphdatasendernet.obj" \
	"$(INTDIR)\graphnamereceivernet.obj" \
	"$(INTDIR)\graphnamesendernet.obj" \
	"$(INTDIR)\modelcontrolreceivernet.obj" \
	"$(INTDIR)\modelcontrolsendernet.obj" \
	"$(INTDIR)\modelstatusreceivernet.obj" \
	"$(INTDIR)\modelstatussendernet.obj" \
	"$(INTDIR)\moduleclassinforeceivernet.obj" \
	"$(INTDIR)\moduleclassinfosendernet.obj" \
	"$(INTDIR)\moduleclassnamereceivernet.obj" \
	"$(INTDIR)\moduleclassnamesendernet.obj" \
	"$(INTDIR)\moduleconstructiondumbreceivernet.obj" \
	"$(INTDIR)\moduleconstructiondumbsendernet.obj" \
	"$(INTDIR)\moduledatareceivernet.obj" \
	"$(INTDIR)\moduledatasendernet.obj" \
	"$(INTDIR)\modulestatisticsreceivernet.obj" \
	"$(INTDIR)\modulestatisticssendernet.obj" \
	"$(INTDIR)\renderercontrolreceivernet.obj" \
	"$(INTDIR)\renderercontrolsendernet.obj" \
	"$(INTDIR)\rendererstatusreceivernet.obj" \
	"$(INTDIR)\rendererstatussendernet.obj"

"$(OUTDIR)\netinterfaces.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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
!IF EXISTS("netinterfaces.dep")
!INCLUDE "netinterfaces.dep"
!ELSE 
!MESSAGE Warning: cannot find "netinterfaces.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "netinterfaces - Win32 Release" || "$(CFG)" == "netinterfaces - Win32 Debug"
SOURCE=.\controlvaluereceivernet.cpp

"$(INTDIR)\controlvaluereceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\controlvaluesendernet.cpp

"$(INTDIR)\controlvaluesendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\enginecontrolreceivernet.cpp

"$(INTDIR)\enginecontrolreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\enginecontrolsendernet.cpp

"$(INTDIR)\enginecontrolsendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\errorreceivernet.cpp

"$(INTDIR)\errorreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\errorsendernet.cpp

"$(INTDIR)\errorsendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphdatareceivernet.cpp

"$(INTDIR)\graphdatareceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphdatasendernet.cpp

"$(INTDIR)\graphdatasendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphnamereceivernet.cpp

"$(INTDIR)\graphnamereceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphnamesendernet.cpp

"$(INTDIR)\graphnamesendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modelcontrolreceivernet.cpp

"$(INTDIR)\modelcontrolreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modelcontrolsendernet.cpp

"$(INTDIR)\modelcontrolsendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modelstatusreceivernet.cpp

"$(INTDIR)\modelstatusreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modelstatussendernet.cpp

"$(INTDIR)\modelstatussendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassinforeceivernet.cpp

"$(INTDIR)\moduleclassinforeceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassinfosendernet.cpp

"$(INTDIR)\moduleclassinfosendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassnamereceivernet.cpp

"$(INTDIR)\moduleclassnamereceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassnamesendernet.cpp

"$(INTDIR)\moduleclassnamesendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleconstructiondumbreceivernet.cpp

"$(INTDIR)\moduleconstructiondumbreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleconstructiondumbsendernet.cpp

"$(INTDIR)\moduleconstructiondumbsendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduledatareceivernet.cpp

"$(INTDIR)\moduledatareceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduledatasendernet.cpp

"$(INTDIR)\moduledatasendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modulestatisticsreceivernet.cpp

"$(INTDIR)\modulestatisticsreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modulestatisticssendernet.cpp

"$(INTDIR)\modulestatisticssendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\renderercontrolreceivernet.cpp

"$(INTDIR)\renderercontrolreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\renderercontrolsendernet.cpp

"$(INTDIR)\renderercontrolsendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rendererstatusreceivernet.cpp

"$(INTDIR)\rendererstatusreceivernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rendererstatussendernet.cpp

"$(INTDIR)\rendererstatussendernet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\interfaces\controlvalue.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\controlvalue.if
InputName=controlvalue

".\controlvaluereceivernet.h"	".\controlvaluereceivernet.cpp"	".\controlvaluesendernet.h"	".\controlvaluesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\controlvalue.if
InputName=controlvalue

".\controlvaluereceivernet.h"	".\controlvaluereceivernet.cpp"	".\controlvaluesendernet.h"	".\controlvaluesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\enginecontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\enginecontrol.if
InputName=enginecontrol

".\enginecontrolreceivernet.h"	".\enginecontrolreceivernet.cpp"	".\enginecontrolsendernet.h"	".\enginecontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\enginecontrol.if
InputName=enginecontrol

".\enginecontrolreceivernet.h"	".\enginecontrolreceivernet.cpp"	".\enginecontrolsendernet.h"	".\enginecontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\error.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\error.if
InputName=error

".\errorreceivernet.h"	".\errorreceivernet.cpp"	".\errorsendernet.h"	".\errorsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\error.if
InputName=error

".\errorreceivernet.h"	".\errorreceivernet.cpp"	".\errorsendernet.h"	".\errorsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\graphdata.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\graphdata.if
InputName=graphdata

".\graphdatareceivernet.h"	".\graphdatareceivernet.cpp"	".\graphdatasendernet.h"	".\graphdatasendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\graphdata.if
InputName=graphdata

".\graphdatareceivernet.h"	".\graphdatareceivernet.cpp"	".\graphdatasendernet.h"	".\graphdatasendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\graphname.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\graphname.if
InputName=graphname

".\graphnamereceivernet.h"	".\graphnamereceivernet.cpp"	".\graphnamesendernet.h"	".\graphnamesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\graphname.if
InputName=graphname

".\graphnamereceivernet.h"	".\graphnamereceivernet.cpp"	".\graphnamesendernet.h"	".\graphnamesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\modelcontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\modelcontrol.if
InputName=modelcontrol

".\modelcontrolreceivernet.h"	".\modelcontrolreceivernet.cpp"	".\modelcontrolsendernet.h"	".\modelcontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\modelcontrol.if
InputName=modelcontrol

".\modelcontrolreceivernet.h"	".\modelcontrolreceivernet.cpp"	".\modelcontrolsendernet.h"	".\modelcontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\modelstatus.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\modelstatus.if
InputName=modelstatus

".\modelstatusreceivernet.h"	".\modelstatusreceivernet.cpp"	".\modelstatussendernet.h"	".\modelstatussendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\modelstatus.if
InputName=modelstatus

".\modelstatusreceivernet.h"	".\modelstatusreceivernet.cpp"	".\modelstatussendernet.h"	".\modelstatussendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleclass.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleclass.if
InputName=moduleclass

".\moduleclassreceivernet.h"	".\moduleclassreceivernet.cpp"	".\moduleclasssendernet.h"	".\moduleclasssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleclass.if
InputName=moduleclass

".\moduleclassreceivernet.h"	".\moduleclassreceivernet.cpp"	".\moduleclasssendernet.h"	".\moduleclasssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleclassinfo.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleclassinfo.if
InputName=moduleclassinfo

".\moduleclassinforeceivernet.h"	".\moduleclassinforeceivernet.cpp"	".\moduleclassinfosendernet.h"	".\moduleclassinfosendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleclassinfo.if
InputName=moduleclassinfo

".\moduleclassinforeceivernet.h"	".\moduleclassinforeceivernet.cpp"	".\moduleclassinfosendernet.h"	".\moduleclassinfosendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleclassname.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleclassname.if
InputName=moduleclassname

".\moduleclassnamereceivernet.h"	".\moduleclassnamereceivernet.cpp"	".\moduleclassnamesendernet.h"	".\moduleclassnamesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleclassname.if
InputName=moduleclassname

".\moduleclassnamereceivernet.h"	".\moduleclassnamereceivernet.cpp"	".\moduleclassnamesendernet.h"	".\moduleclassnamesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleclassspec.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleclassspec.if
InputName=moduleclassspec

".\moduleclassspecreceivernet.h"	".\moduleclassspecreceivernet.cpp"	".\moduleclassspecsendernet.h"	".\moduleclassspecsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleclassspec.if
InputName=moduleclassspec

".\moduleclassspecreceivernet.h"	".\moduleclassspecreceivernet.cpp"	".\moduleclassspecsendernet.h"	".\moduleclassspecsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleconstructiondumb.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleconstructiondumb.if
InputName=moduleconstructiondumb

".\moduleconstructiondumbreceivernet.h"	".\moduleconstructiondumbreceivernet.cpp"	".\moduleconstructiondumbsendernet.h"	".\moduleconstructiondumbsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleconstructiondumb.if
InputName=moduleconstructiondumb

".\moduleconstructiondumbreceivernet.h"	".\moduleconstructiondumbreceivernet.cpp"	".\moduleconstructiondumbsendernet.h"	".\moduleconstructiondumbsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduleconstructionsmart.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduleconstructionsmart.if
InputName=moduleconstructionsmart

".\moduleconstructionsmartreceivernet.h"	".\moduleconstructionsmartreceivernet.cpp"	".\moduleconstructionsmartsendernet.h"	".\moduleconstructionsmartsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduleconstructionsmart.if
InputName=moduleconstructionsmart

".\moduleconstructionsmartreceivernet.h"	".\moduleconstructionsmartreceivernet.cpp"	".\moduleconstructionsmartsendernet.h"	".\moduleconstructionsmartsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\moduledata.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\moduledata.if
InputName=moduledata

".\moduledatareceivernet.h"	".\moduledatareceivernet.cpp"	".\moduledatasendernet.h"	".\moduledatasendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\moduledata.if
InputName=moduledata

".\moduledatareceivernet.h"	".\moduledatareceivernet.cpp"	".\moduledatasendernet.h"	".\moduledatasendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\modulestatistics.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\modulestatistics.if
InputName=modulestatistics

".\modulestatisticsreceivernet.h"	".\modulestatisticsreceivernet.cpp"	".\modulestatisticssendernet.h"	".\modulestatisticssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\modulestatistics.if
InputName=modulestatistics

".\modulestatisticsreceivernet.h"	".\modulestatisticsreceivernet.cpp"	".\modulestatisticssendernet.h"	".\modulestatisticssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\modulestatisticssmart.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\modulestatisticssmart.if
InputName=modulestatisticssmart

".\modulestatisticssmartreceivernet.h"	".\modulestatisticssmartreceivernet.cpp"	".\modulestatisticssmartsendernet.h"	".\modulestatisticssmartsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\modulestatisticssmart.if
InputName=modulestatisticssmart

".\modulestatisticssmartreceivernet.h"	".\modulestatisticssmartreceivernet.cpp"	".\modulestatisticssmartsendernet.h"	".\modulestatisticssmartsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\renderercontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\renderercontrol.if
InputName=renderercontrol

".\renderercontrolreceivernet.h"	".\renderercontrolreceivernet.cpp"	".\renderercontrolsendernet.h"	".\renderercontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\renderercontrol.if
InputName=renderercontrol

".\renderercontrolreceivernet.h"	".\renderercontrolreceivernet.cpp"	".\renderercontrolsendernet.h"	".\renderercontrolsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\rendererstatus.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\rendererstatus.if
InputName=rendererstatus

".\rendererstatusreceivernet.h"	".\rendererstatusreceivernet.cpp"	".\rendererstatussendernet.h"	".\rendererstatussendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\rendererstatus.if
InputName=rendererstatus

".\rendererstatusreceivernet.h"	".\rendererstatusreceivernet.cpp"	".\rendererstatussendernet.h"	".\rendererstatussendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\serializedgraph.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\serializedgraph.if
InputName=serializedgraph

".\serializedgraphreceivernet.h"	".\serializedgraphreceivernet.cpp"	".\serializedgraphsendernet.h"	".\serializedgraphsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\serializedgraph.if
InputName=serializedgraph

".\serializedgraphreceivernet.h"	".\serializedgraphreceivernet.cpp"	".\serializedgraphsendernet.h"	".\serializedgraphsendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\smartcontrolvalue.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\smartcontrolvalue.if
InputName=smartcontrolvalue

".\smartcontrolvaluereceivernet.h"	".\smartcontrolvaluereceivernet.cpp"	".\smartcontrolvaluesendernet.h"	".\smartcontrolvaluesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\smartcontrolvalue.if
InputName=smartcontrolvalue

".\smartcontrolvaluereceivernet.h"	".\smartcontrolvaluereceivernet.cpp"	".\smartcontrolvaluesendernet.h"	".\smartcontrolvaluesendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\typeclass.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\typeclass.if
InputName=typeclass

".\typeclassreceivernet.h"	".\typeclassreceivernet.cpp"	".\typeclasssendernet.h"	".\typeclasssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\typeclass.if
InputName=typeclass

".\typeclassreceivernet.h"	".\typeclassreceivernet.cpp"	".\typeclasssendernet.h"	".\typeclasssendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 

SOURCE=..\interfaces\typeclassinfo.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

InputPath=..\interfaces\typeclassinfo.if
InputName=typeclassinfo

".\typeclassinforeceivernet.h"	".\typeclassinforeceivernet.cpp"	".\typeclassinfosendernet.h"	".\typeclassinfosendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

InputPath=..\interfaces\typeclassinfo.if
InputName=typeclassinfo

".\typeclassinforeceivernet.h"	".\typeclassinforeceivernet.cpp"	".\typeclassinfosendernet.h"	".\typeclassinfosendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py nrh . $(InputPath) 
	python ../../nic.py nrc . $(InputPath) 
	python ../../nic.py nsh . $(InputPath) 
	python ../../nic.py nsc . $(InputPath)
<< 
	

!ENDIF 


!ENDIF 

