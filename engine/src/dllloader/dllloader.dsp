# Microsoft Developer Studio Project File - Name="dllloader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dllloader - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "dllloader.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dllloader.mak" CFG="dllloader - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "dllloader - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "dllloader - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dllloader - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib/"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../../base/src" /I "../../../" /I "../../../util/include" /I "compat_vs6" /D "_LIB" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dllloader - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I ".." /I "../../../base/src" /I "../../../" /I "../../../util/include" /I "compat_vs6" /D "_LIB" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D ENGINE_VERBOSITY=0 /YX /FD /GZ /c
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

# Name "dllloader - Win32 Release"
# Name "dllloader - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\c_input.cpp
# End Source File
# Begin Source File

SOURCE=.\c_output.cpp
# End Source File
# Begin Source File

SOURCE=.\c_outputplug.cpp
# End Source File
# Begin Source File

SOURCE=.\c_type.cpp
# End Source File
# Begin Source File

SOURCE=.\c_typeclass.cpp
# End Source File
# Begin Source File

SOURCE=.\dllloader.cpp
# End Source File
# Begin Source File

SOURCE=.\frei0r_module.cpp
# End Source File
# Begin Source File

SOURCE=.\frei0r_module_class.cpp
# End Source File
# Begin Source File

SOURCE=.\frei0r_module_plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\gephex_module.cpp
# End Source File
# Begin Source File

SOURCE=.\gephex_module_class.cpp
# End Source File
# Begin Source File

SOURCE=.\gephex_module_plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\gephex_type_plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassspec.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleinfoutils.cpp
# End Source File
# Begin Source File

SOURCE=.\nameresolver.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\c_functiontypes.h
# End Source File
# Begin Source File

SOURCE=.\c_input.h
# End Source File
# Begin Source File

SOURCE=.\c_moduletables.h
# End Source File
# Begin Source File

SOURCE=.\c_output.h
# End Source File
# Begin Source File

SOURCE=.\c_outputplug.h
# End Source File
# Begin Source File

SOURCE=.\c_type.h
# End Source File
# Begin Source File

SOURCE=.\c_typeclass.h
# End Source File
# Begin Source File

SOURCE=.\c_typetables.h
# End Source File
# Begin Source File

SOURCE=.\dllloader.h
# End Source File
# Begin Source File

SOURCE=.\frei0r.h
# End Source File
# Begin Source File

SOURCE=.\frei0r_module.h
# End Source File
# Begin Source File

SOURCE=.\frei0r_module_class.h
# End Source File
# Begin Source File

SOURCE=.\frei0r_module_plugin.h
# End Source File
# Begin Source File

SOURCE=.\gephex_module.h
# End Source File
# Begin Source File

SOURCE=.\gephex_module_class.h
# End Source File
# Begin Source File

SOURCE=.\gephex_module_plugin.h
# End Source File
# Begin Source File

SOURCE=.\gephex_type_plugin.h
# End Source File
# Begin Source File

SOURCE=.\compat_vs6\inttypes.h
# End Source File
# Begin Source File

SOURCE=.\module.h
# End Source File
# Begin Source File

SOURCE=.\moduleclassspec.h
# End Source File
# Begin Source File

SOURCE=.\moduleinfoutils.h
# End Source File
# Begin Source File

SOURCE=.\nameresolver.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "dllloader - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath)  ..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "dllloader - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath)  ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
