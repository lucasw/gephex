# Microsoft Developer Studio Project File - Name="misc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=misc - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "misc - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\\" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "misc - Win32 Release"
# Name "misc - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cpuinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\cpuspeed.cpp
# End Source File
# Begin Source File

SOURCE=.\fastmemcpy.cpp
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cpuinfo.h

!IF  "$(CFG)" == "misc - Win32 Release"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\cpuinfo.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\cpuinfo.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cpuspeed.h

!IF  "$(CFG)" == "misc - Win32 Release"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\cpuspeed.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\cpuspeed.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fastmemcpy.h

!IF  "$(CFG)" == "misc - Win32 Release"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\fastmemcpy.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# Begin Custom Build - Kopiere Header $(InputPath) ins include Verzeichnis
InputPath=.\fastmemcpy.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\timer.h

!IF  "$(CFG)" == "misc - Win32 Release"

# Begin Custom Build
InputPath=.\timer.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# Begin Custom Build
InputPath=.\timer.h

"..\..\include\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy $(InputPath) ..\..\include

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\..\config_h.win32

!IF  "$(CFG)" == "misc - Win32 Release"

# Begin Custom Build
InputPath=..\..\config_h.win32

"..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# Begin Custom Build
InputPath=..\..\config_h.win32

"..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
