# Microsoft Developer Studio Project File - Name="engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=engine - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak" CFG="engine - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "engine - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "engine - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../../../util/include" /I ".." /I "../../../base/src/utils" /I "../../../base/src/net" /I "../../../" /I "../../../base/src/" /I "../../../base/src/interfaces" /I "../../../base/src/netinterfaces" /I "../model" /I "../dllloader" /I "../renderer" /I "../sequencer" /D "_CONSOLE" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /profile /map /machine:I386 /out:"Release/gephex-engine.exe"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
PostBuild_Cmds=if not exist ..\..\..\bin\ mkdir ..\..\..\bin	copy $(OutDir)\gephex-engine.exe ..\..\..\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../../util/include" /I ".." /I "../../../base/src/utils" /I "../../../base/src/net" /I "../../../" /I "../../../base/src/" /I "../../../base/src/interfaces" /I "../../../base/src/netinterfaces" /I "../model" /I "../dllloader" /I "../renderer" /I "../sequencer" /D "_CONSOLE" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/gephex-engine.exe"
# SUBTRACT LINK32 /profile /map
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
PostBuild_Cmds=if not exist ..\..\..\bin\ mkdir ..\..\..\bin	copy $(OutDir)\gephex-engine.exe ..\..\..\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "engine - Win32 Release"
# Name "engine - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bufferedsender.cpp
# End Source File
# Begin Source File

SOURCE=.\controller.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\netlogger.cpp
# End Source File
# Begin Source File

SOURCE=.\scheduler.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bufferedsender.h
# End Source File
# Begin Source File

SOURCE=.\controller.h
# End Source File
# Begin Source File

SOURCE=.\netlogger.h
# End Source File
# Begin Source File

SOURCE=.\scheduler.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "engine - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath)  ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\profil-27-07-02.txt"
# End Source File
# End Target
# End Project
