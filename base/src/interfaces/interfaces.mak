# Microsoft Developer Studio Generated NMAKE File, Based on interfaces.dsp
!IF "$(CFG)" == ""
CFG=interfaces - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. interfaces - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "interfaces - Win32 Release" && "$(CFG)" != "interfaces - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "interfaces.mak" CFG="interfaces - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "interfaces - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "interfaces - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "interfaces - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release

ALL : ".\itypeclasssender.h" ".\itypeclassreceiver.h" ".\itypeclassinfosender.h" ".\itypeclassinforeceiver.h" ".\ismartcontrolvaluesender.h" ".\ismartcontrolvaluereceiver.h" ".\iserializedgraphsender.h" ".\iserializedgraphreceiver.h" ".\irendererstatussender.h" ".\irendererstatusreceiver.h" ".\irenderercontrolsender.h" ".\irenderercontrolreceiver.h" ".\imodulestatisticssmartsender.h" ".\imodulestatisticssmartreceiver.h" ".\imodulestatisticssender.h" ".\imodulestatisticsreceiver.h" ".\imoduledatasender.h" ".\imoduledatareceiver.h" ".\imoduleconstructionsmartsender.h" ".\imoduleconstructionsmartreceiver.h" ".\imoduleconstructiondumbsender.h" ".\imoduleconstructiondumbreceiver.h" ".\imoduleclassspecsender.h" ".\imoduleclassspecreceiver.h" ".\imoduleclasssender.h" ".\imoduleclassreceiver.h" ".\imoduleclassnamesender.h" ".\imoduleclassnamereceiver.h" ".\imoduleclassinfosender.h" ".\imoduleclassinforeceiver.h" ".\imodelstatussender.h" ".\imodelstatusreceiver.h" ".\imodelcontrolsender.h" ".\imodelcontrolreceiver.h" ".\igraphnamesender.h" ".\igraphnamereceiver.h" ".\igraphdatasender.h" ".\igraphdatareceiver.h" ".\ierrorsender.h" ".\ierrorreceiver.h" ".\ienginecontrolsender.h"\
 ".\ienginecontrolreceiver.h" ".\icontrolvaluesender.h" ".\icontrolvaluereceiver.h" 


CLEAN :
	-@erase 
	-@erase "icontrolvaluereceiver.h"
	-@erase "icontrolvaluesender.h"
	-@erase "ienginecontrolreceiver.h"
	-@erase "ienginecontrolsender.h"
	-@erase "ierrorreceiver.h"
	-@erase "ierrorsender.h"
	-@erase "igraphdatareceiver.h"
	-@erase "igraphdatasender.h"
	-@erase "igraphnamereceiver.h"
	-@erase "igraphnamesender.h"
	-@erase "imodelcontrolreceiver.h"
	-@erase "imodelcontrolsender.h"
	-@erase "imodelstatusreceiver.h"
	-@erase "imodelstatussender.h"
	-@erase "imoduleclassinforeceiver.h"
	-@erase "imoduleclassinfosender.h"
	-@erase "imoduleclassnamereceiver.h"
	-@erase "imoduleclassnamesender.h"
	-@erase "imoduleclassreceiver.h"
	-@erase "imoduleclasssender.h"
	-@erase "imoduleclassspecreceiver.h"
	-@erase "imoduleclassspecsender.h"
	-@erase "imoduleconstructiondumbreceiver.h"
	-@erase "imoduleconstructiondumbsender.h"
	-@erase "imoduleconstructionsmartreceiver.h"
	-@erase "imoduleconstructionsmartsender.h"
	-@erase "imoduledatareceiver.h"
	-@erase "imoduledatasender.h"
	-@erase "imodulestatisticsreceiver.h"
	-@erase "imodulestatisticssender.h"
	-@erase "imodulestatisticssmartreceiver.h"
	-@erase "imodulestatisticssmartsender.h"
	-@erase "irenderercontrolreceiver.h"
	-@erase "irenderercontrolsender.h"
	-@erase "irendererstatusreceiver.h"
	-@erase "irendererstatussender.h"
	-@erase "iserializedgraphreceiver.h"
	-@erase "iserializedgraphsender.h"
	-@erase "ismartcontrolvaluereceiver.h"
	-@erase "ismartcontrolvaluesender.h"
	-@erase "itypeclassinforeceiver.h"
	-@erase "itypeclassinfosender.h"
	-@erase "itypeclassreceiver.h"
	-@erase "itypeclasssender.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GX /O2 /I "../../../util/src/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\interfaces.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\interfaces.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\interfaces.lib" 
LIB32_OBJS= \
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug

ALL : ".\itypeclasssender.h" ".\itypeclassreceiver.h" ".\itypeclassinfosender.h" ".\itypeclassinforeceiver.h" ".\ismartcontrolvaluesender.h" ".\ismartcontrolvaluereceiver.h" ".\iserializedgraphsender.h" ".\iserializedgraphreceiver.h" ".\irendererstatussender.h" ".\irendererstatusreceiver.h" ".\irenderercontrolsender.h" ".\irenderercontrolreceiver.h" ".\imodulestatisticssmartsender.h" ".\imodulestatisticssmartreceiver.h" ".\imodulestatisticssender.h" ".\imodulestatisticsreceiver.h" ".\imoduledatasender.h" ".\imoduledatareceiver.h" ".\imoduleconstructionsmartsender.h" ".\imoduleconstructionsmartreceiver.h" ".\imoduleconstructiondumbsender.h" ".\imoduleconstructiondumbreceiver.h" ".\imoduleclassspecsender.h" ".\imoduleclassspecreceiver.h" ".\imoduleclasssender.h" ".\imoduleclassreceiver.h" ".\imoduleclassnamesender.h" ".\imoduleclassnamereceiver.h" ".\imoduleclassinfosender.h" ".\imoduleclassinforeceiver.h" ".\imodelstatussender.h" ".\imodelstatusreceiver.h" ".\imodelcontrolsender.h" ".\imodelcontrolreceiver.h" ".\igraphnamesender.h" ".\igraphnamereceiver.h" ".\igraphdatasender.h" ".\igraphdatareceiver.h" ".\ierrorsender.h" ".\ierrorreceiver.h" ".\ienginecontrolsender.h"\
 ".\ienginecontrolreceiver.h" ".\icontrolvaluesender.h" ".\icontrolvaluereceiver.h" 


CLEAN :
	-@erase 
	-@erase "icontrolvaluereceiver.h"
	-@erase "icontrolvaluesender.h"
	-@erase "ienginecontrolreceiver.h"
	-@erase "ienginecontrolsender.h"
	-@erase "ierrorreceiver.h"
	-@erase "ierrorsender.h"
	-@erase "igraphdatareceiver.h"
	-@erase "igraphdatasender.h"
	-@erase "igraphnamereceiver.h"
	-@erase "igraphnamesender.h"
	-@erase "imodelcontrolreceiver.h"
	-@erase "imodelcontrolsender.h"
	-@erase "imodelstatusreceiver.h"
	-@erase "imodelstatussender.h"
	-@erase "imoduleclassinforeceiver.h"
	-@erase "imoduleclassinfosender.h"
	-@erase "imoduleclassnamereceiver.h"
	-@erase "imoduleclassnamesender.h"
	-@erase "imoduleclassreceiver.h"
	-@erase "imoduleclasssender.h"
	-@erase "imoduleclassspecreceiver.h"
	-@erase "imoduleclassspecsender.h"
	-@erase "imoduleconstructiondumbreceiver.h"
	-@erase "imoduleconstructiondumbsender.h"
	-@erase "imoduleconstructionsmartreceiver.h"
	-@erase "imoduleconstructionsmartsender.h"
	-@erase "imoduledatareceiver.h"
	-@erase "imoduledatasender.h"
	-@erase "imodulestatisticsreceiver.h"
	-@erase "imodulestatisticssender.h"
	-@erase "imodulestatisticssmartreceiver.h"
	-@erase "imodulestatisticssmartsender.h"
	-@erase "irenderercontrolreceiver.h"
	-@erase "irenderercontrolsender.h"
	-@erase "irendererstatusreceiver.h"
	-@erase "irendererstatussender.h"
	-@erase "iserializedgraphreceiver.h"
	-@erase "iserializedgraphsender.h"
	-@erase "ismartcontrolvaluereceiver.h"
	-@erase "ismartcontrolvaluesender.h"
	-@erase "itypeclassinforeceiver.h"
	-@erase "itypeclassinfosender.h"
	-@erase "itypeclassreceiver.h"
	-@erase "itypeclasssender.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I "../../../util/include" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\interfaces.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\interfaces.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\interfaces.lib" 
LIB32_OBJS= \
	

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
!IF EXISTS("interfaces.dep")
!INCLUDE "interfaces.dep"
!ELSE 
!MESSAGE Warning: cannot find "interfaces.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "interfaces - Win32 Release" || "$(CFG)" == "interfaces - Win32 Debug"
SOURCE=.\controlvalue.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\controlvalue.if
InputName=controlvalue

".\icontrolvaluesender.h"	".\icontrolvaluereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\controlvalue.if
InputName=controlvalue

".\icontrolvaluesender.h"	".\icontrolvaluereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\enginecontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\enginecontrol.if
InputName=enginecontrol

".\ienginecontrolsender.h"	".\ienginecontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\enginecontrol.if
InputName=enginecontrol

".\ienginecontrolsender.h"	".\ienginecontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\error.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\error.if
InputName=error

".\ierrorsender.h"	".\ierrorreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\error.if
InputName=error

".\ierrorsender.h"	".\ierrorreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\graphdata.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\graphdata.if
InputName=graphdata

".\igraphdatasender.h"	".\igraphdatareceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\graphdata.if
InputName=graphdata

".\igraphdatasender.h"	".\igraphdatareceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\graphname.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\graphname.if
InputName=graphname

".\igraphnamesender.h"	".\igraphnamereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\graphname.if
InputName=graphname

".\igraphnamesender.h"	".\igraphnamereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\modelcontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\modelcontrol.if
InputName=modelcontrol

".\imodelcontrolsender.h"	".\imodelcontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\modelcontrol.if
InputName=modelcontrol

".\imodelcontrolsender.h"	".\imodelcontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\modelstatus.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\modelstatus.if
InputName=modelstatus

".\imodelstatussender.h"	".\imodelstatusreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\modelstatus.if
InputName=modelstatus

".\imodelstatussender.h"	".\imodelstatusreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleclass.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleclass.if
InputName=moduleclass

".\imoduleclasssender.h"	".\imoduleclassreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleclass.if
InputName=moduleclass

".\imoduleclasssender.h"	".\imoduleclassreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleclassinfo.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleclassinfo.if
InputName=moduleclassinfo

".\imoduleclassinfosender.h"	".\imoduleclassinforeceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleclassinfo.if
InputName=moduleclassinfo

".\imoduleclassinfosender.h"	".\imoduleclassinforeceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleclassname.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleclassname.if
InputName=moduleclassname

".\imoduleclassnamesender.h"	".\imoduleclassnamereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleclassname.if
InputName=moduleclassname

".\imoduleclassnamesender.h"	".\imoduleclassnamereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleclassspec.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleclassspec.if
InputName=moduleclassspec

".\imoduleclassspecsender.h"	".\imoduleclassspecreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleclassspec.if
InputName=moduleclassspec

".\imoduleclassspecsender.h"	".\imoduleclassspecreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleconstructiondumb.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleconstructiondumb.if
InputName=moduleconstructiondumb

".\imoduleconstructiondumbsender.h"	".\imoduleconstructiondumbreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleconstructiondumb.if
InputName=moduleconstructiondumb

".\imoduleconstructiondumbsender.h"	".\imoduleconstructiondumbreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduleconstructionsmart.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduleconstructionsmart.if
InputName=moduleconstructionsmart

".\imoduleconstructionsmartsender.h"	".\imoduleconstructionsmartreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduleconstructionsmart.if
InputName=moduleconstructionsmart

".\imoduleconstructionsmartsender.h"	".\imoduleconstructionsmartreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\moduledata.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\moduledata.if
InputName=moduledata

".\imoduledatasender.h"	".\imoduledatareceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\moduledata.if
InputName=moduledata

".\imoduledatasender.h"	".\imoduledatareceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\modulestatistics.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\modulestatistics.if
InputName=modulestatistics

".\imodulestatisticssender.h"	".\imodulestatisticsreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\modulestatistics.if
InputName=modulestatistics

".\imodulestatisticssender.h"	".\imodulestatisticsreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\modulestatisticssmart.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\modulestatisticssmart.if
InputName=modulestatisticssmart

".\imodulestatisticssmartsender.h"	".\imodulestatisticssmartreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\modulestatisticssmart.if
InputName=modulestatisticssmart

".\imodulestatisticssmartsender.h"	".\imodulestatisticssmartreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\renderercontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\renderercontrol.if
InputName=renderercontrol

".\irenderercontrolsender.h"	".\irenderercontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\renderercontrol.if
InputName=renderercontrol

".\irenderercontrolsender.h"	".\irenderercontrolreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\rendererstatus.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\rendererstatus.if
InputName=rendererstatus

".\irendererstatussender.h"	".\irendererstatusreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\rendererstatus.if
InputName=rendererstatus

".\irendererstatussender.h"	".\irendererstatusreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\serializedgraph.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\serializedgraph.if
InputName=serializedgraph

".\iserializedgraphsender.h"	".\iserializedgraphreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\serializedgraph.if
InputName=serializedgraph

".\iserializedgraphsender.h"	".\iserializedgraphreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\smartcontrolvalue.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\smartcontrolvalue.if
InputName=smartcontrolvalue

".\ismartcontrolvaluesender.h"	".\ismartcontrolvaluereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\smartcontrolvalue.if
InputName=smartcontrolvalue

".\ismartcontrolvaluesender.h"	".\ismartcontrolvaluereceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\typeclass.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\typeclass.if
InputName=typeclass

".\itypeclasssender.h"	".\itypeclassreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\typeclass.if
InputName=typeclass

".\itypeclasssender.h"	".\itypeclassreceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\typeclassinfo.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

InputPath=.\typeclassinfo.if
InputName=typeclassinfo

".\itypeclassinfosender.h"	".\itypeclassinforeceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

InputPath=.\typeclassinfo.if
InputName=typeclassinfo

".\itypeclassinfosender.h"	".\itypeclassinforeceiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	python ../../nic.py is . $(InputPath) 
	python ../../nic.py ir . $(InputPath)
<< 
	

!ENDIF 


!ENDIF 

