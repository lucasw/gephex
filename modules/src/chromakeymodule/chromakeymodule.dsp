# Microsoft Developer Studio Project File - Name="chromakeymodule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=chromakeymodule - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "chromakeymodule.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "chromakeymodule.mak" CFG="chromakeymodule - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "chromakeymodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "chromakeymodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
TargetPath=.\Release\chromakeymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W2 /Gm /GX /ZI /Od /I "../../../types/src/stringtype" /I "../../../types/src/rgbtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../../../util/src/cpuinfo" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "chromakeymodule_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
TargetPath=.\Debug\chromakeymodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "chromakeymodule - Win32 Release"
# Name "chromakeymodule - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\chromakeymodule.c

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\chromakeymodule_auto.c
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\chromakeymodule.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\chromakeymodule.def
# End Source File
# Begin Source File

SOURCE=.\chromakeymodule.spec

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

# Begin Custom Build
InputPath=.\chromakeymodule.spec
InputName=chromakeymodule

BuildCmds= \
	python ..\..\pluc.py c $(InputName).spec \
	python ..\..\pluc.py h $(InputName).spec \
	python ..\..\pluc.py def $(InputName).spec \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_auto.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

# Begin Custom Build
InputPath=.\chromakeymodule.spec
InputName=chromakeymodule

BuildCmds= \
	python ..\..\pluc.py c $(InputName).spec \
	python ..\..\pluc.py h $(InputName).spec \
	python ..\..\pluc.py def $(InputName).spec \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_auto.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\chromakeymodule.xpm
# End Source File
# Begin Source File

SOURCE=.\chromakeymodule_x86.asm

!IF  "$(CFG)" == "chromakeymodule - Win32 Release"

# Begin Custom Build - assembling $(InputPath)
OutDir=.\Release
InputPath=.\chromakeymodule_x86.asm
InputName=chromakeymodule_x86

"$(OutDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "chromakeymodule - Win32 Debug"

# Begin Custom Build - assembling $(InputPath)
OutDir=.\Debug
InputPath=.\chromakeymodule_x86.asm
InputName=chromakeymodule_x86

"$(OutDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -f win32 -O3 -o $(OutDir)/$(InputName).obj $(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
