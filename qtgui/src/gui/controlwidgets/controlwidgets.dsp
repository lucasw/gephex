# Microsoft Developer Studio Project File - Name="controlwidgets" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=controlwidgets - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "controlwidgets.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "controlwidgets.mak" CFG="controlwidgets - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "controlwidgets - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "controlwidgets - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /MT /w /W0 /GX /O2 /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /D "_MBCS" /D "_LIB" /D "NDEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GR /GX /ZI /Od /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /D "_MBCS" /D "_LIB" /D "QT_DLL" /D "_DEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /GZ /c
# SUBTRACT CPP /YX
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

# Name "controlwidgets - Win32 Release"
# Name "controlwidgets - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\comboboxwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\dialwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\dialwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\lineeditwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\lineeditwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\positionwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\positionwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\sliderwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\sliderwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\videowallcontrolwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\videowallcontrolwidget_moc.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\comboboxwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\comboboxwidget.h
InputName=comboboxwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\comboboxwidget.h
InputName=comboboxwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dialwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\dialwidget.h
InputName=dialwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\dialwidget.h
InputName=dialwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lineeditwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\lineeditwidget.h
InputName=lineeditwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\lineeditwidget.h
InputName=lineeditwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\positionwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\positionwidget.h
InputName=positionwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\positionwidget.h
InputName=positionwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sliderwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\sliderwidget.h
InputName=sliderwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\sliderwidget.h
InputName=sliderwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\videowallcontrolwidget.h

!IF  "$(CFG)" == "controlwidgets - Win32 Release"

# Begin Custom Build
InputPath=.\videowallcontrolwidget.h
InputName=videowallcontrolwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "controlwidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\videowallcontrolwidget.h
InputName=videowallcontrolwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
