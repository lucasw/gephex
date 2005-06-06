# Microsoft Developer Studio Generated NMAKE File, Based on base.dsp
!IF "$(CFG)" == ""
CFG=base - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. base - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "base - Win32 Release" && "$(CFG)" != "base - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "base.mak" CFG="base - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "base - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "base - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "base - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\treeview_moc.cpp" "$(OUTDIR)\base.lib"


CLEAN :
	-@erase "$(INTDIR)\askforstringdialog.obj"
	-@erase "$(INTDIR)\askforstringdialog_moc.obj"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\keyboardmanager.obj"
	-@erase "$(INTDIR)\logwindow.obj"
	-@erase "$(INTDIR)\picmanager.obj"
	-@erase "$(INTDIR)\propertyview.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\treeviewitem.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\base.lib"
	-@erase "treeview_moc.cpp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GR /GX /O2 /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\base.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\base.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\base.lib" 
LIB32_OBJS= \
	"$(INTDIR)\askforstringdialog.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\keyboardmanager.obj" \
	"$(INTDIR)\logwindow.obj" \
	"$(INTDIR)\propertyview.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\treeviewitem.obj" \
	"$(INTDIR)\askforstringdialog_moc.obj" \
	"$(INTDIR)\picmanager.obj"

"$(OUTDIR)\base.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\gui_base.lib"


CLEAN :
	-@erase "$(INTDIR)\askforstringdialog.obj"
	-@erase "$(INTDIR)\askforstringdialog_moc.obj"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\keyboardmanager.obj"
	-@erase "$(INTDIR)\logwindow.obj"
	-@erase "$(INTDIR)\picmanager.obj"
	-@erase "$(INTDIR)\propertyview.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\treeviewitem.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\gui_base.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\base.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\gui_base.lib" 
LIB32_OBJS= \
	"$(INTDIR)\askforstringdialog.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\keyboardmanager.obj" \
	"$(INTDIR)\logwindow.obj" \
	"$(INTDIR)\propertyview.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\treeviewitem.obj" \
	"$(INTDIR)\askforstringdialog_moc.obj" \
	"$(INTDIR)\picmanager.obj"

"$(OUTDIR)\gui_base.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

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
!IF EXISTS("base.dep")
!INCLUDE "base.dep"
!ELSE 
!MESSAGE Warning: cannot find "base.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "base - Win32 Release" || "$(CFG)" == "base - Win32 Debug"
SOURCE=.\askforstringdialog.cpp

"$(INTDIR)\askforstringdialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\key.cpp

"$(INTDIR)\key.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\keyboardmanager.cpp

"$(INTDIR)\keyboardmanager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\logwindow.cpp

"$(INTDIR)\logwindow.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\picmanager.cpp

"$(INTDIR)\picmanager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\propertyview.cpp

"$(INTDIR)\propertyview.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\treeview.cpp

"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\treeviewitem.cpp

"$(INTDIR)\treeviewitem.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\treeview.h

!IF  "$(CFG)" == "base - Win32 Release"

InputPath=.\treeview.h
InputName=treeview

".\treeview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

InputPath=.\treeview.h
InputName=treeview

".\treeview_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\askforstringdialog.h

!IF  "$(CFG)" == "base - Win32 Release"

InputPath=.\askforstringdialog.h
InputName=askforstringdialog

".\askforstringdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

InputPath=.\askforstringdialog.h
InputName=askforstringdialog

".\askforstringdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc.cpp $(InputName).h
<< 
	

!ENDIF 

SOURCE=.\askforstringdialog_moc.cpp

"$(INTDIR)\askforstringdialog_moc.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

