# Microsoft Developer Studio Project File - Name="gui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gui - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak" CFG="gui - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "gui - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "gui - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gui - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../" /I "$(QTDIR)/include" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "VERBOSE_ENGINE" /D "NDEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /c
# SUBTRACT CPP /X /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib wsock32.lib qt-mt230nc.lib qtmain.lib /nologo /subsystem:windows /machine:I386 /out:"Release/gephex-gui.exe" /libpath:"$(QTDIR)/lib"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
PostBuild_Cmds=if not exist ..\..\..\bin mkdir ..\..\..\bin	copy    $(OutDir)\gephex-gui.exe   ..\..\..\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../" /I "$(QTDIR)/include" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "_DEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib wsock32.lib qt-mt230nc.lib qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"user32" /nodefaultlib:"comdlg32" /nodefaultlib:"advapi32" /nodefaultlib:"imm32" /nodefaultlib:"uuid" /out:"Debug/gephex-gui.exe" /pdbtype:sept /libpath:"base/Debug" /libpath:"$(QTDIR)/lib"
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
PostBuild_Cmds=if not exist ..\..\..\bin mkdir ..\..\..\bin	copy    $(OutDir)\gephex-gui.exe   ..\..\..\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "gui - Win32 Release"
# Name "gui - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\connectionwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\controlwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\graphnameview.cpp
# End Source File
# Begin Source File

SOURCE=.\hidebutton.cpp
# End Source File
# Begin Source File

SOURCE=.\hidebuttonconstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\inputplugwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\modulebutton.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassview.cpp
# End Source File
# Begin Source File

SOURCE=.\nodeproperty.cpp
# End Source File
# Begin Source File

SOURCE=.\nodewidget.cpp
# End Source File
# Begin Source File

SOURCE=.\outputplugwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\picswitch.cpp
# End Source File
# Begin Source File

SOURCE=.\plugwidget.cpp
# End Source File
# Begin Source File

SOURCE=.\propertywidget.cpp
# End Source File
# Begin Source File

SOURCE=.\propertywidgetconstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\typeview.cpp
# End Source File
# Begin Source File

SOURCE=.\typeviewfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\vjmainwindow.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\connectionwidget.h
# End Source File
# Begin Source File

SOURCE=.\controldispatcher.h
# End Source File
# Begin Source File

SOURCE=.\datareceiverwrapper.h
# End Source File
# Begin Source File

SOURCE=.\hidebuttonconstructor.h
# End Source File
# Begin Source File

SOURCE=.\imoduleinfobasestation.h
# End Source File
# Begin Source File

SOURCE=.\iwidgetconstructor.h
# End Source File
# Begin Source File

SOURCE=.\moduleinfo.h
# End Source File
# Begin Source File

SOURCE=.\nodeproperty.h
# End Source File
# Begin Source File

SOURCE=.\ownstyle.h
# End Source File
# Begin Source File

SOURCE=.\pluginfo.h
# End Source File
# Begin Source File

SOURCE=.\propertyview.h
# End Source File
# Begin Source File

SOURCE=.\propertywidgetconstructor.h
# End Source File
# Begin Source File

SOURCE=.\typeviewfactory.h
# End Source File
# End Group
# Begin Group "MocHeader-Dateien"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\controlwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\controlwidget.h
InputName=controlwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\controlwidget.h
InputName=controlwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\graphnameview.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\graphnameview.h
InputName=graphnameview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\graphnameview.h
InputName=graphnameview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hidebutton.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\hidebutton.h
InputName=hidebutton

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\hidebutton.h
InputName=hidebutton

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\inputplugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\inputplugwidget.h
InputName=inputplugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\inputplugwidget.h
InputName=inputplugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\modulebutton.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\modulebutton.h
InputName=modulebutton

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\modulebutton.h
InputName=modulebutton

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\moduleclassview.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\moduleclassview.h
InputName=moduleclassview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\moduleclassview.h
InputName=moduleclassview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nodewidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\nodewidget.h
InputName=nodewidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\nodewidget.h
InputName=nodewidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\outputplugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\outputplugwidget.h
InputName=outputplugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\outputplugwidget.h
InputName=outputplugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\picswitch.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\picswitch.h
InputName=picswitch

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\picswitch.h
InputName=picswitch

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\plugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\plugwidget.h
InputName=plugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\plugwidget.h
InputName=plugwidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\propertywidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\propertywidget.h
InputName=propertywidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\propertywidget.h
InputName=propertywidget

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\typeview.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\typeview.h
InputName=typeview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\typeview.h
InputName=typeview

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vjmainwindow.h

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\vjmainwindow.h
InputName=vjmainwindow

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build - Mocing $(InputPath)...
InputPath=.\vjmainwindow.h
InputName=vjmainwindow

"$(InputName)_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Moc-Dateien"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\controlwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\graphnameview_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\hidebutton_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\inputplugwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\modulebutton_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\moduleclassview_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\nodewidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\outputplugwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\picswitch_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\plugwidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\propertywidget_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\typeview_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\vjmainwindow_moc.cpp
# End Source File
# End Group
# Begin Group "Resourcen"

# PROP Default_Filter "rc"
# Begin Source File

SOURCE=.\Skript1.rc
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "gui - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\logo.ico
# End Source File
# End Target
# End Project
