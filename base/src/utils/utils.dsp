# Microsoft Developer Studio Project File - Name="utils" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=utils - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "utils.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "utils.mak" CFG="utils - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "utils - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "utils - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "utils - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../../../" /I "../../../util/include/compatibility" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "utils - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GX /ZI /Od /I "../../../" /I "../../../util/include/compatibility" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /FD /GZ /c
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

# Name "utils - Win32 Release"
# Name "utils - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\bufferstream.cpp
# End Source File
# Begin Source File

SOURCE=.\bufferutils.cpp
# End Source File
# Begin Source File

SOURCE=.\circularbuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\configfile.cpp
# End Source File
# Begin Source File

SOURCE=.\configmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\filesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\itokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\sharedlibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\spawn.cpp
# End Source File
# Begin Source File

SOURCE=.\streamlogger.cpp
# End Source File
# Begin Source File

SOURCE=.\streamtokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\string_.cpp
# End Source File
# Begin Source File

SOURCE=.\stringtokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\structreader.cpp
# End Source File
# Begin Source File

SOURCE=.\structscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\timing.cpp
# End Source File
# Begin Source File

SOURCE=.\xmlutils.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\autoptr.h
# End Source File
# Begin Source File

SOURCE=.\buffer.h
# End Source File
# Begin Source File

SOURCE=.\bufferstream.h
# End Source File
# Begin Source File

SOURCE=.\bufferutils.h
# End Source File
# Begin Source File

SOURCE=.\circularbuffer.h
# End Source File
# Begin Source File

SOURCE=.\configfile.h
# End Source File
# Begin Source File

SOURCE=.\configmanager.h
# End Source File
# Begin Source File

SOURCE=.\filesystem.h
# End Source File
# Begin Source File

SOURCE=.\ilogger.h
# End Source File
# Begin Source File

SOURCE=.\istructtokenlistener.h
# End Source File
# Begin Source File

SOURCE=.\itokenizer.h
# End Source File
# Begin Source File

SOURCE=.\sharedlibrary.h
# End Source File
# Begin Source File

SOURCE=.\spawn.h
# End Source File
# Begin Source File

SOURCE=.\streamlogger.h
# End Source File
# Begin Source File

SOURCE=.\streamtokenizer.h
# End Source File
# Begin Source File

SOURCE=.\string_.h
# End Source File
# Begin Source File

SOURCE=.\stringtokenizer.h
# End Source File
# Begin Source File

SOURCE=.\structreader.h
# End Source File
# Begin Source File

SOURCE=.\structscanner.h
# End Source File
# Begin Source File

SOURCE=.\timing.h
# End Source File
# Begin Source File

SOURCE=.\xmlutils.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "utils - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "utils - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
