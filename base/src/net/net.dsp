# Microsoft Developer Studio Project File - Name="net" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=net - Win32 Debug
!MESSAGE Dies ist kein gÅltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und fÅhren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "net.mak".
!MESSAGE 
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "net.mak" CFG="net - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "net - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "net - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "net - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../../" /I "../../../util/include" /I "../../../util/include/compatibility" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "net - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GX /ZI /Od /I ".." /I "../../../" /I "../../../util/include" /I "../../../util/include/compatibility" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "net - Win32 Release"
# Name "net - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\convertbin.cpp
# End Source File
# Begin Source File

SOURCE=.\domainclientsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\domainserversocket.cpp
# End Source File
# Begin Source File

SOURCE=.\fdsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\fhsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\isocket.cpp
# End Source File
# Begin Source File

SOURCE=.\namedpipeclientsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\namedpipeserversocket.cpp
# End Source File
# Begin Source File

SOURCE=.\netexceptions.cpp
# End Source File
# Begin Source File

SOURCE=.\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\socketadaptor.cpp
# End Source File
# Begin Source File

SOURCE=.\socketutils.cpp
# End Source File
# Begin Source File

SOURCE=.\sotimeout.cpp
# End Source File
# Begin Source File

SOURCE=.\tagutils.cpp
# End Source File
# Begin Source File

SOURCE=.\tcpclientsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\tcpserversocket.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\block.h
# End Source File
# Begin Source File

SOURCE=.\convertbin.h
# End Source File
# Begin Source File

SOURCE=.\domainclientsocket.h
# End Source File
# Begin Source File

SOURCE=.\domainserversocket.h
# End Source File
# Begin Source File

SOURCE=.\fdsocket.h
# End Source File
# Begin Source File

SOURCE=.\fhsocket.h
# End Source File
# Begin Source File

SOURCE=.\iclientsocket.h
# End Source File
# Begin Source File

SOURCE=.\idatalistener.h
# End Source File
# Begin Source File

SOURCE=.\inetsocket.h
# End Source File
# Begin Source File

SOURCE=.\isender.h
# End Source File
# Begin Source File

SOURCE=.\iserversocket.h
# End Source File
# Begin Source File

SOURCE=.\isocket.h
# End Source File
# Begin Source File

SOURCE=.\itagger.h
# End Source File
# Begin Source File

SOURCE=.\itaginterpreter.h
# End Source File
# Begin Source File

SOURCE=.\namedpipeclientsocket.h
# End Source File
# Begin Source File

SOURCE=.\namedpipeserversocket.h
# End Source File
# Begin Source File

SOURCE=.\netexceptions.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\socketadaptor.h
# End Source File
# Begin Source File

SOURCE=.\socketutils.h
# End Source File
# Begin Source File

SOURCE=.\sotimeout.h
# End Source File
# Begin Source File

SOURCE=.\tagdispatcher.h
# End Source File
# Begin Source File

SOURCE=.\tagger.h
# End Source File
# Begin Source File

SOURCE=.\tagutils.h
# End Source File
# Begin Source File

SOURCE=.\tcpclientsocket.h
# End Source File
# Begin Source File

SOURCE=.\tcpserversocket.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "net - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "net - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
