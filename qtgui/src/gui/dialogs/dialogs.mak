# Microsoft Developer Studio Generated NMAKE File, Based on dialogs.dsp
!IF "$(CFG)" == ""
CFG=dialogs - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. dialogs - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "dialogs - Win32 Release" && "$(CFG)" != "dialogs - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dialogs.mak" CFG="dialogs - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "dialogs - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "dialogs - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "dialogs - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\dialogs.lib"


CLEAN :
	-@erase "$(INTDIR)\aboutdialog.obj"
	-@erase "$(INTDIR)\aboutdialog_moc.obj"
	-@erase "$(INTDIR)\aboutdialogimpl.obj"
	-@erase "$(INTDIR)\changesdialog.obj"
	-@erase "$(INTDIR)\changesdialog_moc.obj"
	-@erase "$(INTDIR)\changesdialogimpl.obj"
	-@erase "$(INTDIR)\newgraphdialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dialogs.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /GR /GX /O2 /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dialogs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dialogs.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\dialogs.lib" 
LIB32_OBJS= \
	"$(INTDIR)\aboutdialog.obj" \
	"$(INTDIR)\aboutdialogimpl.obj" \
	"$(INTDIR)\changesdialog.obj" \
	"$(INTDIR)\changesdialogimpl.obj" \
	"$(INTDIR)\newgraphdialog.obj" \
	"$(INTDIR)\aboutdialog_moc.obj" \
	"$(INTDIR)\changesdialog_moc.obj"

"$(OUTDIR)\dialogs.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dialogs - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\changesdialog_moc.cpp" ".\changesdialog.h" ".\changesdialog.cpp" ".\aboutdialog_moc.cpp" ".\aboutdialog.h" ".\aboutdialog.cpp" "$(OUTDIR)\gui_dialogs.lib"


CLEAN :
	-@erase "$(INTDIR)\aboutdialog.obj"
	-@erase "$(INTDIR)\aboutdialog_moc.obj"
	-@erase "$(INTDIR)\aboutdialogimpl.obj"
	-@erase "$(INTDIR)\changesdialog.obj"
	-@erase "$(INTDIR)\changesdialog_moc.obj"
	-@erase "$(INTDIR)\changesdialogimpl.obj"
	-@erase "$(INTDIR)\newgraphdialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\gui_dialogs.lib"
	-@erase ".\aboutdialog.cpp"
	-@erase ".\aboutdialog.h"
	-@erase ".\aboutdialog_moc.cpp"
	-@erase ".\changesdialog.cpp"
	-@erase ".\changesdialog.h"
	-@erase ".\changesdialog_moc.cpp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "$(QTDIR)/include" /I "../../../../base/src" /I "../" /I "../../../../" /I "../../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dialogs.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\gui_dialogs.lib" 
LIB32_OBJS= \
	"$(INTDIR)\aboutdialog.obj" \
	"$(INTDIR)\aboutdialogimpl.obj" \
	"$(INTDIR)\changesdialog.obj" \
	"$(INTDIR)\changesdialogimpl.obj" \
	"$(INTDIR)\newgraphdialog.obj" \
	"$(INTDIR)\aboutdialog_moc.obj" \
	"$(INTDIR)\changesdialog_moc.obj"

"$(OUTDIR)\gui_dialogs.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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
!IF EXISTS("dialogs.dep")
!INCLUDE "dialogs.dep"
!ELSE 
!MESSAGE Warning: cannot find "dialogs.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dialogs - Win32 Release" || "$(CFG)" == "dialogs - Win32 Debug"
SOURCE=.\aboutdialog.cpp

"$(INTDIR)\aboutdialog.obj" : $(SOURCE) "$(INTDIR)" ".\aboutdialog.h"


SOURCE=.\aboutdialogimpl.cpp

"$(INTDIR)\aboutdialogimpl.obj" : $(SOURCE) "$(INTDIR)" ".\aboutdialog.h"


SOURCE=.\changesdialog.cpp

"$(INTDIR)\changesdialog.obj" : $(SOURCE) "$(INTDIR)" ".\changesdialog.h"


SOURCE=.\changesdialogimpl.cpp

"$(INTDIR)\changesdialogimpl.obj" : $(SOURCE) "$(INTDIR)" ".\changesdialog.h"


SOURCE=.\newgraphdialog.cpp

"$(INTDIR)\newgraphdialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\aboutdialog_moc.cpp

"$(INTDIR)\aboutdialog_moc.obj" : $(SOURCE) "$(INTDIR)" ".\aboutdialog.h"


SOURCE=.\changesdialog_moc.cpp

"$(INTDIR)\changesdialog_moc.obj" : $(SOURCE) "$(INTDIR)" ".\changesdialog.h"


SOURCE=.\aboutdialog.ui

!IF  "$(CFG)" == "dialogs - Win32 Release"

InputDir=.
InputPath=.\aboutdialog.ui
InputName=aboutdialog

".\aboutdialog.h"	".\aboutdialog.cpp"	".\aboutdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h 
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName)_moc.cpp
<< 
	

!ELSEIF  "$(CFG)" == "dialogs - Win32 Debug"

InputDir=.
InputPath=.\aboutdialog.ui
InputName=aboutdialog

".\aboutdialog.h"	".\aboutdialog.cpp"	".\aboutdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h 
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName)_moc.cpp
<< 
	

!ENDIF 

SOURCE=.\changesdialog.ui

!IF  "$(CFG)" == "dialogs - Win32 Release"

InputDir=.
InputPath=.\changesdialog.ui
InputName=changesdialog

".\changesdialog.h"	".\changesdialog.cpp"	".\changesdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h 
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName)_moc.cpp
<< 
	

!ELSEIF  "$(CFG)" == "dialogs - Win32 Debug"

InputDir=.
InputPath=.\changesdialog.ui
InputName=changesdialog

".\changesdialog.h"	".\changesdialog.cpp"	".\changesdialog_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h 
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName)_moc.cpp
<< 
	

!ENDIF 


!ENDIF 

