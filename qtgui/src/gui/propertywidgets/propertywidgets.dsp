# Microsoft Developer Studio Project File - Name="propertywidgets" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=propertywidgets - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "propertywidgets.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "propertywidgets.mak" CFG="propertywidgets - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "propertywidgets - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "propertywidgets - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

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

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /D "_MBCS" /D "_LIB" /D "QT_DLL" /D "_DEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /GZ /c
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

# Name "propertywidgets - Win32 Release"
# Name "propertywidgets - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\colorselectorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\colorselectorwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\fileselectorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\fileselectorwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\fontselectorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\fontselectorwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\lineeditwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\lineeditwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\numberselectorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\numberselectorwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\radiobuttonwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\radiobuttonwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\videowallselectorwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\videowallselectorwidget_moc.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\colorselectorwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\colorselectorwidget.h
InputName=colorselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\colorselectorwidget.h
InputName=colorselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\comboboxwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\comboboxwidget.h
InputName=comboboxwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\comboboxwidget.h
InputName=comboboxwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fileselectorwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\fileselectorwidget.h
InputName=fileselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\fileselectorwidget.h
InputName=fileselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fontselectorwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\fontselectorwidget.h
InputName=fontselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\fontselectorwidget.h
InputName=fontselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lineeditwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\lineeditwidget.h
InputName=lineeditwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\lineeditwidget.h
InputName=lineeditwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\numberselectorwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\numberselectorwidget.h
InputName=numberselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\numberselectorwidget.h
InputName=numberselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\radiobuttonwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\radiobuttonwidget.h
InputName=radiobuttonwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\radiobuttonwidget.h
InputName=radiobuttonwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\videowallselectorwidget.h

!IF  "$(CFG)" == "propertywidgets - Win32 Release"

# Begin Custom Build
InputPath=.\videowallselectorwidget.h
InputName=videowallselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "propertywidgets - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)
InputPath=.\videowallselectorwidget.h
InputName=videowallselectorwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
