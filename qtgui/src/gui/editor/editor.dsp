# Microsoft Developer Studio Project File - Name="editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=editor - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "editor.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "editor.mak" CFG="editor - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "editor - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "editor - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "editor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /MD /GR /GX /O2 /I "../../" /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../" /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /FD /GZ /c
# SUBTRACT CPP /u /YX
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

# Name "editor - Win32 Release"
# Name "editor - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\controleditor.cpp
# End Source File
# Begin Source File

SOURCE=.\controleditorwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\editorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\grapheditor.cpp
# End Source File
# Begin Source File

SOURCE=.\grapheditorwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\labelwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\mouseover.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\combinededitor.h
# End Source File
# Begin Source File

SOURCE=.\controleditorwindow.h
# End Source File
# Begin Source File

SOURCE=.\grapheditorwindow.h
# End Source File
# Begin Source File

SOURCE=.\ieditor.h
# End Source File
# Begin Source File

SOURCE=.\ieditorcommandlistener.h
# End Source File
# Begin Source File

SOURCE=.\ivisibleelement.h
# End Source File
# End Group
# Begin Group "MocHeader-Dateien"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\controleditor.h

!IF  "$(CFG)" == "editor - Win32 Release"

# Begin Custom Build
InputPath=.\controleditor.h
InputName=controleditor

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# Begin Custom Build
InputPath=.\controleditor.h
InputName=controleditor

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\editorwidget.h

!IF  "$(CFG)" == "editor - Win32 Release"

# Begin Custom Build
InputPath=.\editorwidget.h
InputName=editorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# Begin Custom Build
InputPath=.\editorwidget.h
InputName=editorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\grapheditor.h

!IF  "$(CFG)" == "editor - Win32 Release"

# Begin Custom Build
InputPath=.\grapheditor.h
InputName=grapheditor

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# Begin Custom Build
InputPath=.\grapheditor.h
InputName=grapheditor

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\labelwidget.h

!IF  "$(CFG)" == "editor - Win32 Release"

# Begin Custom Build
InputPath=.\labelwidget.h
InputName=labelwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# Begin Custom Build
InputPath=.\labelwidget.h
InputName=labelwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mouseover.h

!IF  "$(CFG)" == "editor - Win32 Release"

USERDEP__MOUSE="mouseover.cpp"	
# Begin Custom Build
InputPath=.\mouseover.h
InputName=mouseover

BuildCmds= \
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h \
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp.cpp $(InputName).cpp \
	

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

USERDEP__MOUSE="mouseover.cpp"	
# Begin Custom Build
InputPath=.\mouseover.h
InputName=mouseover

BuildCmds= \
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h \
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp.cpp $(InputName).cpp \
	

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Moc-Dateien"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\controleditor_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\editorwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\grapheditor_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\labelwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\mouseover_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\mouseover_moc_cpp.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\config_h.win32

!IF  "$(CFG)" == "editor - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\..\config_h.win32

"..\..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\..\config_h.win32

"..\..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
