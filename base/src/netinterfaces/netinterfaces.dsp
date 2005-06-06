# Microsoft Developer Studio Project File - Name="netinterfaces" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=netinterfaces - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "netinterfaces.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "netinterfaces.mak" CFG="netinterfaces - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "netinterfaces - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "netinterfaces - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../" /I "../../../util/src/include" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "../../" /I "../../../util/include" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "netinterfaces - Win32 Release"
# Name "netinterfaces - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\controlvaluereceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\controlvaluesendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\enginecontrolreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\enginecontrolsendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\errorreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\errorsendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\graphdatareceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\graphdatasendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\graphnamereceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\graphnamesendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modelcontrolreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modelcontrolsendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modelstatusreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modelstatussendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassinforeceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassinfosendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassnamereceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassnamesendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleconstructiondumbreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleconstructiondumbsendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduledatareceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\moduledatasendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modulestatisticsreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\modulestatisticssendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\renderercontrolreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\renderercontrolsendernet.cpp
# End Source File
# Begin Source File

SOURCE=.\rendererstatusreceivernet.cpp
# End Source File
# Begin Source File

SOURCE=.\rendererstatussendernet.cpp
# End Source File
# End Group
# Begin Group "Autocreated Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\controlvaluereceivernet.h
# End Source File
# Begin Source File

SOURCE=.\controlvaluesendernet.h
# End Source File
# Begin Source File

SOURCE=.\enginecontrolreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\enginecontrolsendernet.h
# End Source File
# Begin Source File

SOURCE=.\errorreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\errorsendernet.h
# End Source File
# Begin Source File

SOURCE=.\graphdatareceivernet.h
# End Source File
# Begin Source File

SOURCE=.\graphdatasendernet.h
# End Source File
# Begin Source File

SOURCE=.\graphnamereceivernet.h
# End Source File
# Begin Source File

SOURCE=.\graphnamesendernet.h
# End Source File
# Begin Source File

SOURCE=.\modelcontrolreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\modelcontrolsendernet.h
# End Source File
# Begin Source File

SOURCE=.\modelstatusreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\modelstatussendernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassinforeceivernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassinfosendernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassloadercontrolreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassloadercontrolsender.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassloadercontrolsendernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassnamereceivernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassnamesendernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleconstructiondumbreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\moduleconstructiondumbsendernet.h
# End Source File
# Begin Source File

SOURCE=.\moduledatareceivernet.h
# End Source File
# Begin Source File

SOURCE=.\moduledatasendernet.h
# End Source File
# Begin Source File

SOURCE=.\modulestatisticsreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\modulestatisticssendernet.h
# End Source File
# Begin Source File

SOURCE=.\renderercontrolreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\renderercontrolsendernet.h
# End Source File
# Begin Source File

SOURCE=.\rendererstatusreceivernet.h
# End Source File
# Begin Source File

SOURCE=.\rendererstatussendernet.h
# End Source File
# End Group
# Begin Group "Interfaces"

# PROP Default_Filter "if"
# Begin Source File

SOURCE=..\interfaces\controlvalue.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\controlvalue.if
InputName=controlvalue

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\controlvalue.if
InputName=controlvalue

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\enginecontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\enginecontrol.if
InputName=enginecontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\enginecontrol.if
InputName=enginecontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\error.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\error.if
InputName=error

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\error.if
InputName=error

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\graphdata.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\graphdata.if
InputName=graphdata

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build
InputPath=..\interfaces\graphdata.if
InputName=graphdata

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\graphname.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\graphname.if
InputName=graphname

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\graphname.if
InputName=graphname

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\modelcontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\modelcontrol.if
InputName=modelcontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\modelcontrol.if
InputName=modelcontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\modelstatus.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\modelstatus.if
InputName=modelstatus

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\modelstatus.if
InputName=modelstatus

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleclass.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleclass.if
InputName=moduleclass

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleclass.if
InputName=moduleclass

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleclassinfo.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleclassinfo.if
InputName=moduleclassinfo

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleclassinfo.if
InputName=moduleclassinfo

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleclassname.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleclassname.if
InputName=moduleclassname

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleclassname.if
InputName=moduleclassname

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleclassspec.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleclassspec.if
InputName=moduleclassspec

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleclassspec.if
InputName=moduleclassspec

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleconstructiondumb.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleconstructiondumb.if
InputName=moduleconstructiondumb

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleconstructiondumb.if
InputName=moduleconstructiondumb

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduleconstructionsmart.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduleconstructionsmart.if
InputName=moduleconstructionsmart

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduleconstructionsmart.if
InputName=moduleconstructionsmart

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\moduledata.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\moduledata.if
InputName=moduledata

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\moduledata.if
InputName=moduledata

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\modulestatistics.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\modulestatistics.if
InputName=modulestatistics

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\modulestatistics.if
InputName=modulestatistics

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\modulestatisticssmart.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\modulestatisticssmart.if
InputName=modulestatisticssmart

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\modulestatisticssmart.if
InputName=modulestatisticssmart

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\renderercontrol.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\renderercontrol.if
InputName=renderercontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\renderercontrol.if
InputName=renderercontrol

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\rendererstatus.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\rendererstatus.if
InputName=rendererstatus

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\rendererstatus.if
InputName=rendererstatus

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\serializedgraph.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\serializedgraph.if
InputName=serializedgraph

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\serializedgraph.if
InputName=serializedgraph

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\smartcontrolvalue.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\smartcontrolvalue.if
InputName=smartcontrolvalue

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\smartcontrolvalue.if
InputName=smartcontrolvalue

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\typeclass.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\typeclass.if
InputName=typeclass

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\typeclass.if
InputName=typeclass

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\interfaces\typeclassinfo.if

!IF  "$(CFG)" == "netinterfaces - Win32 Release"

# Begin Custom Build
InputPath=..\interfaces\typeclassinfo.if
InputName=typeclassinfo

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "netinterfaces - Win32 Debug"

# Begin Custom Build - Creating netinterface headers and implementations for $(InputPath) ...
InputPath=..\interfaces\typeclassinfo.if
InputName=typeclassinfo

BuildCmds= \
	python ../../nic.py nrh . $(InputPath) \
	python ../../nic.py nrc . $(InputPath) \
	python ../../nic.py nsh . $(InputPath) \
	python ../../nic.py nsc . $(InputPath) \
	

"$(InputName)receivernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)receivernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)sendernet.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
