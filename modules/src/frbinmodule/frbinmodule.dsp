# Microsoft Developer Studio Project File - Name="frbinmodule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=frbinmodule - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "frbinmodule.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "frbinmodule.mak" CFG="frbinmodule - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "frbinmodule - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "frbinmodule - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "frbinmodule - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "$(DXSDK_DIR)\Include" /I "$(SDL_DIR)/include" /I "$(SDL_IMAGE_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libscale" /I "../libdshow" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /I "../../../contrib/ffmpeg/libavutil" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /YX /FD /c
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
# ADD LINK32 sdl.lib sdl_image.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib strmiids.lib quartz.lib avcodec.lib avformat.lib /nologo /dll /machine:I386 /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" /libpath:"$(DXSDK_DIR)/Lib" /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
TargetPath=.\Release\frbinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /w /W0 /Gm /GX /ZI /Od /I "$(DXSDK_DIR)\Include" /I "$(SDL_DIR)/include" /I "$(SDL_IMAGE_DIR)/include" /I "../../../types/src/stringtype" /I "../../../types/src/framebuffertype" /I "../../../types/src/numbertype" /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /I "../libscale" /I "../libdshow" /I "../../../contrib/ffmpeg/libavformat" /I "../../../contrib/ffmpeg/libavcodec" /I "../../../contrib/ffmpeg/libavutil" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "frbinmodule_EXPORTS" /D "WIN32" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 sdl.lib sdl_image.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib strmiids.lib quartz.lib avcodec.lib avformat.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /pdbtype:sept /libpath:"$(SDL_DIR)/lib" /libpath:"$(SDL_IMAGE_DIR)/lib" /libpath:"$(DXSDK_DIR)/Lib" /libpath:"../../../contrib/ffmpeg/libavformat" /libpath:"../../../contrib/ffmpeg/libavcodec"
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
TargetPath=.\Debug\frbinmodule.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "frbinmodule - Win32 Release"
# Name "frbinmodule - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bmpdriver.cpp
# End Source File
# Begin Source File

SOURCE=.\ffmpegdriver.cpp
# End Source File
# Begin Source File

SOURCE=.\framecache.cpp
# End Source File
# Begin Source File

SOURCE=.\frbinmodule.cpp
# End Source File
# Begin Source File

SOURCE=.\frbinmodule_auto.c
# End Source File
# Begin Source File

SOURCE=.\sdlimagedriver.cpp
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# Begin Source File

SOURCE=.\vfwdriver.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bmpdriver.h
# End Source File
# Begin Source File

SOURCE=.\driverfactory.h
# End Source File
# Begin Source File

SOURCE=.\ffmpegdriver.h
# End Source File
# Begin Source File

SOURCE=.\framecache.h
# End Source File
# Begin Source File

SOURCE=.\frbinmodule.h
# End Source File
# Begin Source File

SOURCE=.\sdlimagedriver.h
# End Source File
# Begin Source File

SOURCE=.\timer.h
# End Source File
# Begin Source File

SOURCE=.\vfwdriver.h
# End Source File
# Begin Source File

SOURCE=.\videofiledriver.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\frbinmodule.def
# End Source File
# Begin Source File

SOURCE=.\frbinmodule.spec

!IF  "$(CFG)" == "frbinmodule - Win32 Release"

# Begin Custom Build
InputPath=.\frbinmodule.spec
InputName=frbinmodule

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

!ELSEIF  "$(CFG)" == "frbinmodule - Win32 Debug"

# Begin Custom Build
InputPath=.\frbinmodule.spec
InputName=frbinmodule

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

SOURCE=.\frbinmodule.xpm
# End Source File
# End Target
# End Project
