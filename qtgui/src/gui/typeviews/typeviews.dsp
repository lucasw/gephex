# Microsoft Developer Studio Project File - Name="typeviews" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=typeviews - Win32 Debug
!MESSAGE Dies ist kein gltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und fhren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "typeviews.mak".
!MESSAGE 
!MESSAGE Sie k”nnen beim Ausfhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "typeviews.mak" CFG="typeviews - Win32 Debug"
!MESSAGE 
!MESSAGE Fr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "typeviews - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "typeviews - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "typeviews - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /w /W0 /GR /GX /O2 /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /I "../../../" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D "QT_DLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

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
# ADD CPP /nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /I "../../../" /D "QT_DLL" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /FD /GZ /c
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

# Name "typeviews - Win32 Release"
# Name "typeviews - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\boundednumberview.cpp
# End Source File
# Begin Source File

SOURCE=.\checkboxnumberview.cpp
# End Source File
# Begin Source File

SOURCE=.\colorview.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxstringview.cpp
# End Source File
# Begin Source File

SOURCE=.\dialnumberview.cpp
# End Source File
# Begin Source File

SOURCE=.\filestringview.cpp
# End Source File
# Begin Source File

SOURCE=.\fontview.cpp
# End Source File
# Begin Source File

SOURCE=.\frameview.cpp
# End Source File
# Begin Source File

SOURCE=.\positionview.cpp
# End Source File
# Begin Source File

SOURCE=.\radionumberview.cpp
# End Source File
# Begin Source File

SOURCE=.\slidernumberview.cpp
# End Source File
# Begin Source File

SOURCE=.\stringview.cpp
# End Source File
# Begin Source File

SOURCE=.\unboundednumberview.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\boundednumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\boundednumberview.h
InputName=boundednumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\boundednumberview.h
InputName=boundednumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\checkboxnumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\checkboxnumberview.h
InputName=checkboxnumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\checkboxnumberview.h
InputName=checkboxnumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\colorview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\colorview.h
InputName=colorview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\colorview.h
InputName=colorview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\comboboxstringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\comboboxstringview.h
InputName=comboboxstringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\comboboxstringview.h
InputName=comboboxstringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dialnumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\dialnumberview.h
InputName=dialnumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\dialnumberview.h
InputName=dialnumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\filestringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\filestringview.h
InputName=filestringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\filestringview.h
InputName=filestringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fontview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\fontview.h
InputName=fontview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\fontview.h
InputName=fontview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\frameview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\frameview.h
InputName=frameview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\frameview.h
InputName=frameview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\positionview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\positionview.h
InputName=positionview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\positionview.h
InputName=positionview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\radionumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\radionumberview.h
InputName=radionumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\radionumberview.h
InputName=radionumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\slidernumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\slidernumberview.h
InputName=slidernumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\slidernumberview.h
InputName=slidernumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\stringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\stringview.h
InputName=stringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\stringview.h
InputName=stringview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\unboundednumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\unboundednumberview.h
InputName=unboundednumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build - Mocing and postmocing $(InputPath) ...
InputPath=.\unboundednumberview.h
InputName=unboundednumberview

"$(InputName)_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\config_h.win32

!IF  "$(CFG)" == "typeviews - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
