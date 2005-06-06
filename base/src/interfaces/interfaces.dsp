# Microsoft Developer Studio Project File - Name="interfaces" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=interfaces - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "interfaces.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "interfaces.mak" CFG="interfaces - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "interfaces - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "interfaces - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "interfaces - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /w /W0 /GX /O2 /I "../../../util/src/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I "../../../util/include" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
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

# Name "interfaces - Win32 Release"
# Name "interfaces - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\imodule.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclass.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassspec.h
# End Source File
# Begin Source File

SOURCE=.\itask.h
# End Source File
# Begin Source File

SOURCE=.\itype.h
# End Source File
# Begin Source File

SOURCE=.\itypeclass.h
# End Source File
# Begin Source File

SOURCE=.\itypefactory.h
# End Source File
# End Group
# Begin Group "Interfaces"

# PROP Default_Filter "if"
# Begin Source File

SOURCE=.\controlvalue.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\controlvalue.if
InputName=controlvalue

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\controlvalue.if
InputName=controlvalue

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\enginecontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\enginecontrol.if
InputName=enginecontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\enginecontrol.if
InputName=enginecontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\error.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\error.if
InputName=error

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\error.if
InputName=error

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\graphdata.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\graphdata.if
InputName=graphdata

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build
InputPath=.\graphdata.if
InputName=graphdata

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\graphname.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\graphname.if
InputName=graphname

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\graphname.if
InputName=graphname

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modelcontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\modelcontrol.if
InputName=modelcontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\modelcontrol.if
InputName=modelcontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modelstatus.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\modelstatus.if
InputName=modelstatus

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\modelstatus.if
InputName=modelstatus

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleclass.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleclass.if
InputName=moduleclass

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleclass.if
InputName=moduleclass

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleclassinfo.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleclassinfo.if
InputName=moduleclassinfo

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleclassinfo.if
InputName=moduleclassinfo

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleclassname.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleclassname.if
InputName=moduleclassname

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleclassname.if
InputName=moduleclassname

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleclassspec.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleclassspec.if
InputName=moduleclassspec

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleclassspec.if
InputName=moduleclassspec

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleconstructiondumb.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleconstructiondumb.if
InputName=moduleconstructiondumb

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleconstructiondumb.if
InputName=moduleconstructiondumb

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleconstructionsmart.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduleconstructionsmart.if
InputName=moduleconstructionsmart

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduleconstructionsmart.if
InputName=moduleconstructionsmart

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduledata.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\moduledata.if
InputName=moduledata

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\moduledata.if
InputName=moduledata

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modulestatistics.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\modulestatistics.if
InputName=modulestatistics

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\modulestatistics.if
InputName=modulestatistics

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modulestatisticssmart.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\modulestatisticssmart.if
InputName=modulestatisticssmart

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\modulestatisticssmart.if
InputName=modulestatisticssmart

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\renderercontrol.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\renderercontrol.if
InputName=renderercontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\renderercontrol.if
InputName=renderercontrol

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rendererstatus.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\rendererstatus.if
InputName=rendererstatus

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\rendererstatus.if
InputName=rendererstatus

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\serializedgraph.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\serializedgraph.if
InputName=serializedgraph

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\serializedgraph.if
InputName=serializedgraph

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smartcontrolvalue.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\smartcontrolvalue.if
InputName=smartcontrolvalue

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\smartcontrolvalue.if
InputName=smartcontrolvalue

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\typeclass.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\typeclass.if
InputName=typeclass

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\typeclass.if
InputName=typeclass

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\typeclassinfo.if

!IF  "$(CFG)" == "interfaces - Win32 Release"

# Begin Custom Build
InputPath=.\typeclassinfo.if
InputName=typeclassinfo

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interfaces - Win32 Debug"

# Begin Custom Build - Creating interface headers for $(InputPath) ...
InputPath=.\typeclassinfo.if
InputName=typeclassinfo

BuildCmds= \
	python ../../nic.py is . $(InputPath) \
	python ../../nic.py ir . $(InputPath) \
	

"i$(InputName)sender.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"i$(InputName)receiver.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Autocreated Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\icontrolvaluereceiver.h
# End Source File
# Begin Source File

SOURCE=.\icontrolvaluesender.h
# End Source File
# Begin Source File

SOURCE=.\ienginecontrolreceiver.h
# End Source File
# Begin Source File

SOURCE=.\ienginecontrolsender.h
# End Source File
# Begin Source File

SOURCE=.\ierrorreceiver.h
# End Source File
# Begin Source File

SOURCE=.\ierrorsender.h
# End Source File
# Begin Source File

SOURCE=.\igraphnamereceiver.h
# End Source File
# Begin Source File

SOURCE=.\igraphnamesender.h
# End Source File
# Begin Source File

SOURCE=.\imodelcontrolreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imodelcontrolsender.h
# End Source File
# Begin Source File

SOURCE=.\imodelstatusreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imodelstatussender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassinforeceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassinfosender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassloadercontrolreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassloadercontrolsender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassnamereceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassnamesender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclasssender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassspecreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleclassspecsender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleconstructiondumbreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleconstructiondumbsender.h
# End Source File
# Begin Source File

SOURCE=.\imoduleconstructionsmartreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduleconstructionsmartsender.h
# End Source File
# Begin Source File

SOURCE=.\imoduledatareceiver.h
# End Source File
# Begin Source File

SOURCE=.\imoduledatasender.h
# End Source File
# Begin Source File

SOURCE=.\imodulestatisticsreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imodulestatisticssender.h
# End Source File
# Begin Source File

SOURCE=.\imodulestatisticssmartreceiver.h
# End Source File
# Begin Source File

SOURCE=.\imodulestatisticssmartsender.h
# End Source File
# Begin Source File

SOURCE=.\irenderercontrolreceiver.h
# End Source File
# Begin Source File

SOURCE=.\irenderercontrolsender.h
# End Source File
# Begin Source File

SOURCE=.\irendererstatusreceiver.h
# End Source File
# Begin Source File

SOURCE=.\irendererstatussender.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\nic.py
# End Source File
# End Target
# End Project
