# Microsoft Developer Studio Project File - Name="base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=base - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "base.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "base.mak" CFG="base - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "base - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "base - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "base - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "HAVE_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\gui_base.lib"

!ENDIF 

# Begin Target

# Name "base - Win32 Release"
# Name "base - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\askforstringdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\key.cpp
# End Source File
# Begin Source File

SOURCE=.\keyboardmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\logwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\picmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\propertyview.cpp
# End Source File
# Begin Source File

SOURCE=.\treeview.cpp
# End Source File
# Begin Source File

SOURCE=.\treeviewitem.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ikeylistener.h
# End Source File
# Begin Source File

SOURCE=.\ipropertydescription.h
# End Source File
# Begin Source File

SOURCE=.\iwidgetconstructor.h
# End Source File
# Begin Source File

SOURCE=.\key.h
# End Source File
# Begin Source File

SOURCE=.\keyboardmanager.h
# End Source File
# Begin Source File

SOURCE=.\logwindow.h
# End Source File
# Begin Source File

SOURCE=.\picmanager.h
# End Source File
# Begin Source File

SOURCE=.\propertyview.h
# End Source File
# Begin Source File

SOURCE=.\treeview.h

!IF  "$(CFG)" == "base - Win32 Release"

# Begin Custom Build
InputPath=.\treeview.h
InputName=treeview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

# Begin Custom Build
InputPath=.\treeview.h
InputName=treeview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\treeviewitem.h
# End Source File
# End Group
# Begin Group "MocHeader-Dateien"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\askforstringdialog.h

!IF  "$(CFG)" == "base - Win32 Release"

# Begin Custom Build
InputPath=.\askforstringdialog.h
InputName=askforstringdialog

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

# Begin Custom Build
InputPath=.\askforstringdialog.h
InputName=askforstringdialog

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Moc-Dateien"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\askforstringdialog_moc.cpp
# End Source File
# End Group
# End Target
# End Project
