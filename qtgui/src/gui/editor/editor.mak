# Microsoft Developer Studio Generated NMAKE File, Based on editor.dsp
!IF "$(CFG)" == ""
CFG=editor - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. editor - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "editor - Win32 Release" && "$(CFG)" != "editor - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "editor.mak" CFG="editor - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "editor - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "editor - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "editor - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "..\..\..\..\config.h" "$(OUTDIR)\editor.lib"


CLEAN :
	-@erase "$(INTDIR)\controleditor.obj"
	-@erase "$(INTDIR)\controleditor_moc.obj"
	-@erase "$(INTDIR)\controleditorwindow.obj"
	-@erase "$(INTDIR)\editorwidget.obj"
	-@erase "$(INTDIR)\editorwidget_moc.obj"
	-@erase "$(INTDIR)\grapheditor.obj"
	-@erase "$(INTDIR)\grapheditor_moc.obj"
	-@erase "$(INTDIR)\grapheditorwindow.obj"
	-@erase "$(INTDIR)\labelwidget.obj"
	-@erase "$(INTDIR)\labelwidget_moc.obj"
	-@erase "$(INTDIR)\mouseover.obj"
	-@erase "$(INTDIR)\mouseover_moc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\editor.lib"
	-@erase "..\..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /GR /GX /O2 /I "../../" /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /Fp"$(INTDIR)\editor.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\editor.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\editor.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controleditor.obj" \
	"$(INTDIR)\controleditorwindow.obj" \
	"$(INTDIR)\editorwidget.obj" \
	"$(INTDIR)\grapheditor.obj" \
	"$(INTDIR)\grapheditorwindow.obj" \
	"$(INTDIR)\labelwidget.obj" \
	"$(INTDIR)\mouseover.obj" \
	"$(INTDIR)\controleditor_moc.obj" \
	"$(INTDIR)\editorwidget_moc.obj" \
	"$(INTDIR)\grapheditor_moc.obj" \
	"$(INTDIR)\labelwidget_moc.obj" \
	"$(INTDIR)\mouseover_moc.obj"

"$(OUTDIR)\editor.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\mouseover_moc_cpp.cpp" ".\mouseover_moc.cpp" "..\..\..\..\config.h" "$(OUTDIR)\editor.lib"


CLEAN :
	-@erase "$(INTDIR)\controleditor.obj"
	-@erase "$(INTDIR)\controleditor_moc.obj"
	-@erase "$(INTDIR)\controleditorwindow.obj"
	-@erase "$(INTDIR)\editorwidget.obj"
	-@erase "$(INTDIR)\editorwidget_moc.obj"
	-@erase "$(INTDIR)\grapheditor.obj"
	-@erase "$(INTDIR)\grapheditor_moc.obj"
	-@erase "$(INTDIR)\grapheditorwindow.obj"
	-@erase "$(INTDIR)\labelwidget.obj"
	-@erase "$(INTDIR)\labelwidget_moc.obj"
	-@erase "$(INTDIR)\mouseover.obj"
	-@erase "$(INTDIR)\mouseover_moc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\editor.lib"
	-@erase "..\..\..\..\config.h"
	-@erase "mouseover_moc.cpp"
	-@erase "mouseover_moc_cpp.cpp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../" /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\editor.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\editor.lib" 
LIB32_OBJS= \
	"$(INTDIR)\controleditor.obj" \
	"$(INTDIR)\controleditorwindow.obj" \
	"$(INTDIR)\editorwidget.obj" \
	"$(INTDIR)\grapheditor.obj" \
	"$(INTDIR)\grapheditorwindow.obj" \
	"$(INTDIR)\labelwidget.obj" \
	"$(INTDIR)\mouseover.obj" \
	"$(INTDIR)\controleditor_moc.obj" \
	"$(INTDIR)\editorwidget_moc.obj" \
	"$(INTDIR)\grapheditor_moc.obj" \
	"$(INTDIR)\labelwidget_moc.obj" \
	"$(INTDIR)\mouseover_moc.obj"

"$(OUTDIR)\editor.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("editor.dep")
!INCLUDE "editor.dep"
!ELSE 
!MESSAGE Warning: cannot find "editor.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "editor - Win32 Release" || "$(CFG)" == "editor - Win32 Debug"
SOURCE=.\controleditor.cpp

"$(INTDIR)\controleditor.obj" : $(SOURCE) "$(INTDIR)" ".\controleditor.h" ".\mouseover.h" ".\labelwidget.h"


SOURCE=.\controleditorwindow.cpp

"$(INTDIR)\controleditorwindow.obj" : $(SOURCE) "$(INTDIR)" ".\controleditor.h"


SOURCE=.\editorwidget.cpp

"$(INTDIR)\editorwidget.obj" : $(SOURCE) "$(INTDIR)" ".\editorwidget.h" ".\grapheditor.h" ".\controleditor.h"


SOURCE=.\grapheditor.cpp

"$(INTDIR)\grapheditor.obj" : $(SOURCE) "$(INTDIR)" ".\grapheditor.h"


SOURCE=.\grapheditorwindow.cpp

"$(INTDIR)\grapheditorwindow.obj" : $(SOURCE) "$(INTDIR)" ".\grapheditor.h"


SOURCE=.\labelwidget.cpp

"$(INTDIR)\labelwidget.obj" : $(SOURCE) "$(INTDIR)" ".\labelwidget.h"


SOURCE=.\mouseover.cpp

"$(INTDIR)\mouseover.obj" : $(SOURCE) "$(INTDIR)" ".\mouseover.h" ".\mouseover_moc_cpp.cpp"


SOURCE=.\controleditor.h

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=.\controleditor.h
InputName=controleditor

".\controleditor_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=.\controleditor.h
InputName=controleditor

".\controleditor_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\editorwidget.h

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=.\editorwidget.h
InputName=editorwidget

".\editorwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=.\editorwidget.h
InputName=editorwidget

".\editorwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\grapheditor.h

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=.\grapheditor.h
InputName=grapheditor

".\grapheditor_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=.\grapheditor.h
InputName=grapheditor

".\grapheditor_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\labelwidget.h

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=.\labelwidget.h
InputName=labelwidget

".\labelwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=.\labelwidget.h
InputName=labelwidget

".\labelwidget_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\mouseover.h

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=.\mouseover.h
InputName=mouseover
USERDEP__MOUSE="mouseover.cpp"	

".\mouseover_moc.cpp"	".\mouseover_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__MOUSE)
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp.cpp $(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=.\mouseover.h
InputName=mouseover
USERDEP__MOUSE="mouseover.cpp"	

".\mouseover_moc.cpp"	".\mouseover_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__MOUSE)
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp.cpp $(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\controleditor_moc.cpp

"$(INTDIR)\controleditor_moc.obj" : $(SOURCE) "$(INTDIR)" ".\controleditor.h"


SOURCE=.\editorwidget_moc.cpp

"$(INTDIR)\editorwidget_moc.obj" : $(SOURCE) "$(INTDIR)" ".\editorwidget.h"


SOURCE=.\grapheditor_moc.cpp

"$(INTDIR)\grapheditor_moc.obj" : $(SOURCE) "$(INTDIR)" ".\grapheditor.h"


SOURCE=.\labelwidget_moc.cpp

"$(INTDIR)\labelwidget_moc.obj" : $(SOURCE) "$(INTDIR)" ".\labelwidget.h"


SOURCE=.\mouseover_moc.cpp

"$(INTDIR)\mouseover_moc.obj" : $(SOURCE) "$(INTDIR)" ".\mouseover.h"


SOURCE=.\mouseover_moc_cpp.cpp
SOURCE=..\..\..\..\config_h.win32

!IF  "$(CFG)" == "editor - Win32 Release"

InputPath=..\..\..\..\config_h.win32

"..\..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

InputPath=..\..\..\..\config_h.win32

"..\..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

