# Microsoft Developer Studio Generated NMAKE File, Based on gui.dsp
!IF "$(CFG)" == ""
CFG=gui - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. gui - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "gui - Win32 Release" && "$(CFG)" != "gui - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak" CFG="gui - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "gui - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "gui - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gui - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"

!ELSE 

ALL : "typeviews - Win32 Release" "guimodel - Win32 Release" "editor - Win32 Release" "dialogs - Win32 Release" "base - Win32 Release" "netinterfaces - Win32 Release" "net - Win32 Release" "interfaces - Win32 Release" "utils - Win32 Release" "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"utils - Win32 ReleaseCLEAN" "interfaces - Win32 ReleaseCLEAN" "net - Win32 ReleaseCLEAN" "netinterfaces - Win32 ReleaseCLEAN" "base - Win32 ReleaseCLEAN" "dialogs - Win32 ReleaseCLEAN" "editor - Win32 ReleaseCLEAN" "guimodel - Win32 ReleaseCLEAN" "typeviews - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\connectionwidget.obj"
	-@erase "$(INTDIR)\controlwidget.obj"
	-@erase "$(INTDIR)\controlwidget_moc.obj"
	-@erase "$(INTDIR)\graphnameview.obj"
	-@erase "$(INTDIR)\graphnameview_moc.obj"
	-@erase "$(INTDIR)\hidebutton.obj"
	-@erase "$(INTDIR)\hidebutton_moc.obj"
	-@erase "$(INTDIR)\hidebuttonconstructor.obj"
	-@erase "$(INTDIR)\inputplugwidget.obj"
	-@erase "$(INTDIR)\inputplugwidget_moc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\modulebutton.obj"
	-@erase "$(INTDIR)\modulebutton_moc.obj"
	-@erase "$(INTDIR)\moduleclassview.obj"
	-@erase "$(INTDIR)\moduleclassview_moc.obj"
	-@erase "$(INTDIR)\nodeproperty.obj"
	-@erase "$(INTDIR)\nodewidget.obj"
	-@erase "$(INTDIR)\nodewidget_moc.obj"
	-@erase "$(INTDIR)\outputplugwidget.obj"
	-@erase "$(INTDIR)\outputplugwidget_moc.obj"
	-@erase "$(INTDIR)\picswitch.obj"
	-@erase "$(INTDIR)\picswitch_moc.obj"
	-@erase "$(INTDIR)\plugwidget.obj"
	-@erase "$(INTDIR)\plugwidget_moc.obj"
	-@erase "$(INTDIR)\propertywidget.obj"
	-@erase "$(INTDIR)\propertywidget_moc.obj"
	-@erase "$(INTDIR)\propertywidgetconstructor.obj"
	-@erase "$(INTDIR)\Skript1.res"
	-@erase "$(INTDIR)\typeview.obj"
	-@erase "$(INTDIR)\typeview_moc.obj"
	-@erase "$(INTDIR)\typeviewfactory.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vjmainwindow.obj"
	-@erase "$(INTDIR)\vjmainwindow_moc.obj"
	-@erase "$(OUTDIR)\gephex-gui.exe"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../" /I "$(QTDIR)/include" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "VERBOSE_ENGINE" /D "NDEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Skript1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib wsock32.lib qt-mt230nc.lib qtmain.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\gephex-gui.pdb" /machine:I386 /out:"$(OUTDIR)\gephex-gui.exe" /libpath:"$(QTDIR)/lib" 
LINK32_OBJS= \
	"$(INTDIR)\connectionwidget.obj" \
	"$(INTDIR)\controlwidget.obj" \
	"$(INTDIR)\graphnameview.obj" \
	"$(INTDIR)\hidebutton.obj" \
	"$(INTDIR)\hidebuttonconstructor.obj" \
	"$(INTDIR)\inputplugwidget.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\modulebutton.obj" \
	"$(INTDIR)\moduleclassview.obj" \
	"$(INTDIR)\nodeproperty.obj" \
	"$(INTDIR)\nodewidget.obj" \
	"$(INTDIR)\outputplugwidget.obj" \
	"$(INTDIR)\picswitch.obj" \
	"$(INTDIR)\plugwidget.obj" \
	"$(INTDIR)\propertywidget.obj" \
	"$(INTDIR)\propertywidgetconstructor.obj" \
	"$(INTDIR)\typeview.obj" \
	"$(INTDIR)\typeviewfactory.obj" \
	"$(INTDIR)\vjmainwindow.obj" \
	"$(INTDIR)\controlwidget_moc.obj" \
	"$(INTDIR)\graphnameview_moc.obj" \
	"$(INTDIR)\hidebutton_moc.obj" \
	"$(INTDIR)\inputplugwidget_moc.obj" \
	"$(INTDIR)\modulebutton_moc.obj" \
	"$(INTDIR)\moduleclassview_moc.obj" \
	"$(INTDIR)\nodewidget_moc.obj" \
	"$(INTDIR)\outputplugwidget_moc.obj" \
	"$(INTDIR)\picswitch_moc.obj" \
	"$(INTDIR)\plugwidget_moc.obj" \
	"$(INTDIR)\propertywidget_moc.obj" \
	"$(INTDIR)\typeview_moc.obj" \
	"$(INTDIR)\vjmainwindow_moc.obj" \
	"$(INTDIR)\Skript1.res" \
	"..\..\..\base\lib\utils.lib" \
	"..\..\..\base\lib\net.lib" \
	"..\..\..\base\lib\netinterfaces.lib" \
	".\base\Release\base.lib" \
	".\dialogs\Release\dialogs.lib" \
	".\editor\Release\editor.lib" \
	"..\guimodel\Release\guimodel.lib" \
	"..\..\lib\typeviews.lib"

"$(OUTDIR)\gephex-gui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "typeviews - Win32 Release" "guimodel - Win32 Release" "editor - Win32 Release" "dialogs - Win32 Release" "base - Win32 Release" "netinterfaces - Win32 Release" "net - Win32 Release" "interfaces - Win32 Release" "utils - Win32 Release" "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"
   if not exist ..\..\..\bin mkdir ..\..\..\bin
	copy    .\Release\gephex-gui.exe   ..\..\..\bin
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"

!ELSE 

ALL : "typeviews - Win32 Debug" "guimodel - Win32 Debug" "editor - Win32 Debug" "dialogs - Win32 Debug" "base - Win32 Debug" "netinterfaces - Win32 Debug" "net - Win32 Debug" "interfaces - Win32 Debug" "utils - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"utils - Win32 DebugCLEAN" "interfaces - Win32 DebugCLEAN" "net - Win32 DebugCLEAN" "netinterfaces - Win32 DebugCLEAN" "base - Win32 DebugCLEAN" "dialogs - Win32 DebugCLEAN" "editor - Win32 DebugCLEAN" "guimodel - Win32 DebugCLEAN" "typeviews - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\connectionwidget.obj"
	-@erase "$(INTDIR)\controlwidget.obj"
	-@erase "$(INTDIR)\controlwidget_moc.obj"
	-@erase "$(INTDIR)\graphnameview.obj"
	-@erase "$(INTDIR)\graphnameview_moc.obj"
	-@erase "$(INTDIR)\hidebutton.obj"
	-@erase "$(INTDIR)\hidebutton_moc.obj"
	-@erase "$(INTDIR)\hidebuttonconstructor.obj"
	-@erase "$(INTDIR)\inputplugwidget.obj"
	-@erase "$(INTDIR)\inputplugwidget_moc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\modulebutton.obj"
	-@erase "$(INTDIR)\modulebutton_moc.obj"
	-@erase "$(INTDIR)\moduleclassview.obj"
	-@erase "$(INTDIR)\moduleclassview_moc.obj"
	-@erase "$(INTDIR)\nodeproperty.obj"
	-@erase "$(INTDIR)\nodewidget.obj"
	-@erase "$(INTDIR)\nodewidget_moc.obj"
	-@erase "$(INTDIR)\outputplugwidget.obj"
	-@erase "$(INTDIR)\outputplugwidget_moc.obj"
	-@erase "$(INTDIR)\picswitch.obj"
	-@erase "$(INTDIR)\picswitch_moc.obj"
	-@erase "$(INTDIR)\plugwidget.obj"
	-@erase "$(INTDIR)\plugwidget_moc.obj"
	-@erase "$(INTDIR)\propertywidget.obj"
	-@erase "$(INTDIR)\propertywidget_moc.obj"
	-@erase "$(INTDIR)\propertywidgetconstructor.obj"
	-@erase "$(INTDIR)\Skript1.res"
	-@erase "$(INTDIR)\typeview.obj"
	-@erase "$(INTDIR)\typeview_moc.obj"
	-@erase "$(INTDIR)\typeviewfactory.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vjmainwindow.obj"
	-@erase "$(INTDIR)\vjmainwindow_moc.obj"
	-@erase "$(OUTDIR)\gephex-gui.exe"
	-@erase "$(OUTDIR)\gephex-gui.ilk"
	-@erase "$(OUTDIR)\gephex-gui.pdb"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../" /I "$(QTDIR)/include" /I "../../../base/src" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "_DEBUG" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Skript1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib wsock32.lib qt-mt230nc.lib qtmain.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\gephex-gui.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"user32" /nodefaultlib:"comdlg32" /nodefaultlib:"advapi32" /nodefaultlib:"imm32" /nodefaultlib:"uuid" /out:"$(OUTDIR)\gephex-gui.exe" /pdbtype:sept /libpath:"base/Debug" /libpath:"$(QTDIR)/lib" 
LINK32_OBJS= \
	"$(INTDIR)\connectionwidget.obj" \
	"$(INTDIR)\controlwidget.obj" \
	"$(INTDIR)\graphnameview.obj" \
	"$(INTDIR)\hidebutton.obj" \
	"$(INTDIR)\hidebuttonconstructor.obj" \
	"$(INTDIR)\inputplugwidget.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\modulebutton.obj" \
	"$(INTDIR)\moduleclassview.obj" \
	"$(INTDIR)\nodeproperty.obj" \
	"$(INTDIR)\nodewidget.obj" \
	"$(INTDIR)\outputplugwidget.obj" \
	"$(INTDIR)\picswitch.obj" \
	"$(INTDIR)\plugwidget.obj" \
	"$(INTDIR)\propertywidget.obj" \
	"$(INTDIR)\propertywidgetconstructor.obj" \
	"$(INTDIR)\typeview.obj" \
	"$(INTDIR)\typeviewfactory.obj" \
	"$(INTDIR)\vjmainwindow.obj" \
	"$(INTDIR)\controlwidget_moc.obj" \
	"$(INTDIR)\graphnameview_moc.obj" \
	"$(INTDIR)\hidebutton_moc.obj" \
	"$(INTDIR)\inputplugwidget_moc.obj" \
	"$(INTDIR)\modulebutton_moc.obj" \
	"$(INTDIR)\moduleclassview_moc.obj" \
	"$(INTDIR)\nodewidget_moc.obj" \
	"$(INTDIR)\outputplugwidget_moc.obj" \
	"$(INTDIR)\picswitch_moc.obj" \
	"$(INTDIR)\plugwidget_moc.obj" \
	"$(INTDIR)\propertywidget_moc.obj" \
	"$(INTDIR)\typeview_moc.obj" \
	"$(INTDIR)\vjmainwindow_moc.obj" \
	"$(INTDIR)\Skript1.res" \
	"..\..\..\base\lib\utils.lib" \
	"..\..\..\base\lib\net.lib" \
	"..\..\..\base\lib\netinterfaces.lib" \
	".\base\Debug\gui_base.lib" \
	".\dialogs\Debug\gui_dialogs.lib" \
	".\editor\Debug\editor.lib" \
	"..\guimodel\Debug\guimodel.lib" \
	"..\..\lib\typeviews.lib"

"$(OUTDIR)\gephex-gui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=installing ...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "typeviews - Win32 Debug" "guimodel - Win32 Debug" "editor - Win32 Debug" "dialogs - Win32 Debug" "base - Win32 Debug" "netinterfaces - Win32 Debug" "net - Win32 Debug" "interfaces - Win32 Debug" "utils - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\gephex-gui.exe"
   if not exist ..\..\..\bin mkdir ..\..\..\bin
	copy    .\Debug\gephex-gui.exe   ..\..\..\bin
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gui.dep")
!INCLUDE "gui.dep"
!ELSE 
!MESSAGE Warning: cannot find "gui.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gui - Win32 Release" || "$(CFG)" == "gui - Win32 Debug"
SOURCE=.\connectionwidget.cpp

"$(INTDIR)\connectionwidget.obj" : $(SOURCE) "$(INTDIR)" ".\inputplugwidget.h" ".\outputplugwidget.h" ".\plugwidget.h"


SOURCE=.\controlwidget.cpp

"$(INTDIR)\controlwidget.obj" : $(SOURCE) "$(INTDIR)" ".\controlwidget.h" ".\typeview.h"


SOURCE=.\graphnameview.cpp

"$(INTDIR)\graphnameview.obj" : $(SOURCE) "$(INTDIR)" ".\graphnameview.h"


SOURCE=.\hidebutton.cpp

"$(INTDIR)\hidebutton.obj" : $(SOURCE) "$(INTDIR)" ".\hidebutton.h" ".\inputplugwidget.h" ".\plugwidget.h"


SOURCE=.\hidebuttonconstructor.cpp

"$(INTDIR)\hidebuttonconstructor.obj" : $(SOURCE) "$(INTDIR)" ".\hidebutton.h"


SOURCE=.\inputplugwidget.cpp

"$(INTDIR)\inputplugwidget.obj" : $(SOURCE) "$(INTDIR)" ".\inputplugwidget.h" ".\plugwidget.h"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)" ".\vjmainwindow.h"


SOURCE=.\modulebutton.cpp

"$(INTDIR)\modulebutton.obj" : $(SOURCE) "$(INTDIR)" ".\modulebutton.h"


SOURCE=.\moduleclassview.cpp

"$(INTDIR)\moduleclassview.obj" : $(SOURCE) "$(INTDIR)" ".\moduleclassview.h"


SOURCE=.\nodeproperty.cpp

"$(INTDIR)\nodeproperty.obj" : $(SOURCE) "$(INTDIR)" ".\inputplugwidget.h" ".\plugwidget.h"


SOURCE=.\nodewidget.cpp

"$(INTDIR)\nodewidget.obj" : $(SOURCE) "$(INTDIR)" ".\nodewidget.h" ".\inputplugwidget.h" ".\outputplugwidget.h" ".\plugwidget.h"


SOURCE=.\outputplugwidget.cpp

"$(INTDIR)\outputplugwidget.obj" : $(SOURCE) "$(INTDIR)" ".\outputplugwidget.h" ".\plugwidget.h"


SOURCE=.\picswitch.cpp

"$(INTDIR)\picswitch.obj" : $(SOURCE) "$(INTDIR)" ".\picswitch.h"


SOURCE=.\plugwidget.cpp

"$(INTDIR)\plugwidget.obj" : $(SOURCE) "$(INTDIR)" ".\plugwidget.h"


SOURCE=.\propertywidget.cpp

"$(INTDIR)\propertywidget.obj" : $(SOURCE) "$(INTDIR)" ".\propertywidget.h" ".\typeview.h"


SOURCE=.\propertywidgetconstructor.cpp

"$(INTDIR)\propertywidgetconstructor.obj" : $(SOURCE) "$(INTDIR)" ".\propertywidget.h"


SOURCE=.\typeview.cpp

"$(INTDIR)\typeview.obj" : $(SOURCE) "$(INTDIR)" ".\typeview.h"


SOURCE=.\typeviewfactory.cpp

"$(INTDIR)\typeviewfactory.obj" : $(SOURCE) "$(INTDIR)" ".\typeview.h"


SOURCE=.\vjmainwindow.cpp

"$(INTDIR)\vjmainwindow.obj" : $(SOURCE) "$(INTDIR)" ".\vjmainwindow.h" ".\moduleclassview.h" ".\graphnameview.h" ".\picswitch.h"


SOURCE=.\controlwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\controlwidget.h
InputName=controlwidget

".\controlwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\controlwidget.h
InputName=controlwidget

".\controlwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\graphnameview.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\graphnameview.h
InputName=graphnameview

".\graphnameview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\graphnameview.h
InputName=graphnameview

".\graphnameview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\hidebutton.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\hidebutton.h
InputName=hidebutton

".\hidebutton_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\hidebutton.h
InputName=hidebutton

".\hidebutton_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\inputplugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\inputplugwidget.h
InputName=inputplugwidget

".\inputplugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\inputplugwidget.h
InputName=inputplugwidget

".\inputplugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
<< 
	

!ENDIF 

SOURCE=.\modulebutton.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\modulebutton.h
InputName=modulebutton

".\modulebutton_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\modulebutton.h
InputName=modulebutton

".\modulebutton_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\moduleclassview.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\moduleclassview.h
InputName=moduleclassview

".\moduleclassview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\moduleclassview.h
InputName=moduleclassview

".\moduleclassview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\nodewidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\nodewidget.h
InputName=nodewidget

".\nodewidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\nodewidget.h
InputName=nodewidget

".\nodewidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\outputplugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\outputplugwidget.h
InputName=outputplugwidget

".\outputplugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\outputplugwidget.h
InputName=outputplugwidget

".\outputplugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_.cpp $(InputName).h 
	python ../../../build/postmoc.py $(InputName)_moc_.cpp > $(InputName)_moc.cpp 
	del $(InputName)_moc_.cpp 
<< 
	

!ENDIF 

SOURCE=.\picswitch.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\picswitch.h
InputName=picswitch

".\picswitch_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\picswitch.h
InputName=picswitch

".\picswitch_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\plugwidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\plugwidget.h
InputName=plugwidget

".\plugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\plugwidget.h
InputName=plugwidget

".\plugwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\propertywidget.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\propertywidget.h
InputName=propertywidget

".\propertywidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\propertywidget.h
InputName=propertywidget

".\propertywidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\typeview.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\typeview.h
InputName=typeview

".\typeview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\typeview.h
InputName=typeview

".\typeview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\vjmainwindow.h

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=.\vjmainwindow.h
InputName=vjmainwindow

".\vjmainwindow_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=.\vjmainwindow.h
InputName=vjmainwindow

".\vjmainwindow_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\controlwidget_moc.cpp

"$(INTDIR)\controlwidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\graphnameview_moc.cpp

"$(INTDIR)\graphnameview_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\hidebutton_moc.cpp

"$(INTDIR)\hidebutton_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\inputplugwidget_moc.cpp

"$(INTDIR)\inputplugwidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\modulebutton_moc.cpp

"$(INTDIR)\modulebutton_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassview_moc.cpp

"$(INTDIR)\moduleclassview_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\nodewidget_moc.cpp

"$(INTDIR)\nodewidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\outputplugwidget_moc.cpp

"$(INTDIR)\outputplugwidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\picswitch_moc.cpp

"$(INTDIR)\picswitch_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\plugwidget_moc.cpp

"$(INTDIR)\plugwidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\propertywidget_moc.cpp

"$(INTDIR)\propertywidget_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\typeview_moc.cpp

"$(INTDIR)\typeview_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vjmainwindow_moc.cpp

"$(INTDIR)\vjmainwindow_moc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Skript1.rc

"$(INTDIR)\Skript1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"utils - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Release" 
   cd "..\..\..\qtgui\src\gui"

"utils - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"utils - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Debug" 
   cd "..\..\..\qtgui\src\gui"

"utils - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"interfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" 
   cd "..\..\..\qtgui\src\gui"

"interfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"interfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" 
   cd "..\..\..\qtgui\src\gui"

"interfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"net - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Release" 
   cd "..\..\..\qtgui\src\gui"

"net - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"net - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Debug" 
   cd "..\..\..\qtgui\src\gui"

"net - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"netinterfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" 
   cd "..\..\..\qtgui\src\gui"

"netinterfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"netinterfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" 
   cd "..\..\..\qtgui\src\gui"

"netinterfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\qtgui\src\gui"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"base - Win32 Release" : 
   cd ".\base"
   $(MAKE) /$(MAKEFLAGS) /F ".\base.mak" CFG="base - Win32 Release" 
   cd ".."

"base - Win32 ReleaseCLEAN" : 
   cd ".\base"
   $(MAKE) /$(MAKEFLAGS) /F ".\base.mak" CFG="base - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"base - Win32 Debug" : 
   cd ".\base"
   $(MAKE) /$(MAKEFLAGS) /F ".\base.mak" CFG="base - Win32 Debug" 
   cd ".."

"base - Win32 DebugCLEAN" : 
   cd ".\base"
   $(MAKE) /$(MAKEFLAGS) /F ".\base.mak" CFG="base - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"dialogs - Win32 Release" : 
   cd ".\dialogs"
   $(MAKE) /$(MAKEFLAGS) /F ".\dialogs.mak" CFG="dialogs - Win32 Release" 
   cd ".."

"dialogs - Win32 ReleaseCLEAN" : 
   cd ".\dialogs"
   $(MAKE) /$(MAKEFLAGS) /F ".\dialogs.mak" CFG="dialogs - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"dialogs - Win32 Debug" : 
   cd ".\dialogs"
   $(MAKE) /$(MAKEFLAGS) /F ".\dialogs.mak" CFG="dialogs - Win32 Debug" 
   cd ".."

"dialogs - Win32 DebugCLEAN" : 
   cd ".\dialogs"
   $(MAKE) /$(MAKEFLAGS) /F ".\dialogs.mak" CFG="dialogs - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"editor - Win32 Release" : 
   cd ".\editor"
   $(MAKE) /$(MAKEFLAGS) /F ".\editor.mak" CFG="editor - Win32 Release" 
   cd ".."

"editor - Win32 ReleaseCLEAN" : 
   cd ".\editor"
   $(MAKE) /$(MAKEFLAGS) /F ".\editor.mak" CFG="editor - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"editor - Win32 Debug" : 
   cd ".\editor"
   $(MAKE) /$(MAKEFLAGS) /F ".\editor.mak" CFG="editor - Win32 Debug" 
   cd ".."

"editor - Win32 DebugCLEAN" : 
   cd ".\editor"
   $(MAKE) /$(MAKEFLAGS) /F ".\editor.mak" CFG="editor - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"guimodel - Win32 Release" : 
   cd "\code\gephex-0.4\qtgui\src\guimodel"
   $(MAKE) /$(MAKEFLAGS) /F ".\guimodel.mak" CFG="guimodel - Win32 Release" 
   cd "..\gui"

"guimodel - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\qtgui\src\guimodel"
   $(MAKE) /$(MAKEFLAGS) /F ".\guimodel.mak" CFG="guimodel - Win32 Release" RECURSE=1 CLEAN 
   cd "..\gui"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"guimodel - Win32 Debug" : 
   cd "\code\gephex-0.4\qtgui\src\guimodel"
   $(MAKE) /$(MAKEFLAGS) /F ".\guimodel.mak" CFG="guimodel - Win32 Debug" 
   cd "..\gui"

"guimodel - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\qtgui\src\guimodel"
   $(MAKE) /$(MAKEFLAGS) /F ".\guimodel.mak" CFG="guimodel - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\gui"

!ENDIF 

!IF  "$(CFG)" == "gui - Win32 Release"

"typeviews - Win32 Release" : 
   cd ".\typeviews"
   $(MAKE) /$(MAKEFLAGS) /F ".\typeviews.mak" CFG="typeviews - Win32 Release" 
   cd ".."

"typeviews - Win32 ReleaseCLEAN" : 
   cd ".\typeviews"
   $(MAKE) /$(MAKEFLAGS) /F ".\typeviews.mak" CFG="typeviews - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

"typeviews - Win32 Debug" : 
   cd ".\typeviews"
   $(MAKE) /$(MAKEFLAGS) /F ".\typeviews.mak" CFG="typeviews - Win32 Debug" 
   cd ".."

"typeviews - Win32 DebugCLEAN" : 
   cd ".\typeviews"
   $(MAKE) /$(MAKEFLAGS) /F ".\typeviews.mak" CFG="typeviews - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "gui - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

