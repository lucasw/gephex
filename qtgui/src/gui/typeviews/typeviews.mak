# Microsoft Developer Studio Generated NMAKE File, Based on typeviews.dsp
!IF "$(CFG)" == ""
CFG=typeviews - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. typeviews - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "typeviews - Win32 Release" && "$(CFG)" != "typeviews - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "typeviews.mak" CFG="typeviews - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "typeviews - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "typeviews - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "typeviews - Win32 Release"

OUTDIR=.\../../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../../lib
# End Custom Macros

ALL : "$(OUTDIR)\typeviews.lib"


CLEAN :
	-@erase "$(INTDIR)\boundednumberview.obj"
	-@erase "$(INTDIR)\checkboxnumberview.obj"
	-@erase "$(INTDIR)\colorview.obj"
	-@erase "$(INTDIR)\comboboxstringview.obj"
	-@erase "$(INTDIR)\dialnumberview.obj"
	-@erase "$(INTDIR)\filestringview.obj"
	-@erase "$(INTDIR)\fontview.obj"
	-@erase "$(INTDIR)\frameview.obj"
	-@erase "$(INTDIR)\positionview.obj"
	-@erase "$(INTDIR)\radionumberview.obj"
	-@erase "$(INTDIR)\slidernumberview.obj"
	-@erase "$(INTDIR)\stringview.obj"
	-@erase "$(INTDIR)\unboundednumberview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\typeviews.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /I "../../../" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D "QT_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\typeviews.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\typeviews.lib" 
LIB32_OBJS= \
	"$(INTDIR)\boundednumberview.obj" \
	"$(INTDIR)\checkboxnumberview.obj" \
	"$(INTDIR)\colorview.obj" \
	"$(INTDIR)\comboboxstringview.obj" \
	"$(INTDIR)\dialnumberview.obj" \
	"$(INTDIR)\filestringview.obj" \
	"$(INTDIR)\fontview.obj" \
	"$(INTDIR)\frameview.obj" \
	"$(INTDIR)\positionview.obj" \
	"$(INTDIR)\radionumberview.obj" \
	"$(INTDIR)\slidernumberview.obj" \
	"$(INTDIR)\stringview.obj" \
	"$(INTDIR)\unboundednumberview.obj"

"$(OUTDIR)\typeviews.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

OUTDIR=.\../../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../../lib
# End Custom Macros

ALL : ".\unboundednumberview_moc_cpp.cpp" ".\stringview_moc_cpp.cpp" ".\slidernumberview_moc_cpp.cpp" ".\radionumberview_moc_cpp.cpp" ".\positionview_moc_cpp.cpp" ".\frameview_moc_cpp.cpp" ".\fontview_moc_cpp.cpp" ".\filestringview_moc_cpp.cpp" ".\dialnumberview_moc_cpp.cpp" ".\comboboxstringview_moc_cpp.cpp" ".\colorview_moc_cpp.cpp" ".\checkboxnumberview_moc_cpp.cpp" ".\boundednumberview_moc_cpp.cpp" "..\..\..\config.h" "$(OUTDIR)\typeviews.lib"


CLEAN :
	-@erase "$(INTDIR)\boundednumberview.obj"
	-@erase "$(INTDIR)\checkboxnumberview.obj"
	-@erase "$(INTDIR)\colorview.obj"
	-@erase "$(INTDIR)\comboboxstringview.obj"
	-@erase "$(INTDIR)\dialnumberview.obj"
	-@erase "$(INTDIR)\filestringview.obj"
	-@erase "$(INTDIR)\fontview.obj"
	-@erase "$(INTDIR)\frameview.obj"
	-@erase "$(INTDIR)\positionview.obj"
	-@erase "$(INTDIR)\radionumberview.obj"
	-@erase "$(INTDIR)\slidernumberview.obj"
	-@erase "$(INTDIR)\stringview.obj"
	-@erase "$(INTDIR)\unboundednumberview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\typeviews.lib"
	-@erase "..\..\..\config.h"
	-@erase "boundednumberview_moc_cpp.cpp"
	-@erase "checkboxnumberview_moc_cpp.cpp"
	-@erase "colorview_moc_cpp.cpp"
	-@erase "comboboxstringview_moc_cpp.cpp"
	-@erase "dialnumberview_moc_cpp.cpp"
	-@erase "filestringview_moc_cpp.cpp"
	-@erase "fontview_moc_cpp.cpp"
	-@erase "frameview_moc_cpp.cpp"
	-@erase "positionview_moc_cpp.cpp"
	-@erase "radionumberview_moc_cpp.cpp"
	-@erase "slidernumberview_moc_cpp.cpp"
	-@erase "stringview_moc_cpp.cpp"
	-@erase "unboundednumberview_moc_cpp.cpp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../../../base/src" /I "../../" /I "$(QTDIR)/include" /I "../../../" /D "QT_DLL" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\typeviews.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\typeviews.lib" 
LIB32_OBJS= \
	"$(INTDIR)\boundednumberview.obj" \
	"$(INTDIR)\checkboxnumberview.obj" \
	"$(INTDIR)\colorview.obj" \
	"$(INTDIR)\comboboxstringview.obj" \
	"$(INTDIR)\dialnumberview.obj" \
	"$(INTDIR)\filestringview.obj" \
	"$(INTDIR)\fontview.obj" \
	"$(INTDIR)\frameview.obj" \
	"$(INTDIR)\positionview.obj" \
	"$(INTDIR)\radionumberview.obj" \
	"$(INTDIR)\slidernumberview.obj" \
	"$(INTDIR)\stringview.obj" \
	"$(INTDIR)\unboundednumberview.obj"

"$(OUTDIR)\typeviews.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("typeviews.dep")
!INCLUDE "typeviews.dep"
!ELSE 
!MESSAGE Warning: cannot find "typeviews.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "typeviews - Win32 Release" || "$(CFG)" == "typeviews - Win32 Debug"
SOURCE=.\boundednumberview.cpp

"$(INTDIR)\boundednumberview.obj" : $(SOURCE) "$(INTDIR)" ".\boundednumberview.h" ".\boundednumberview_moc_cpp.cpp"


SOURCE=.\checkboxnumberview.cpp

"$(INTDIR)\checkboxnumberview.obj" : $(SOURCE) "$(INTDIR)" ".\checkboxnumberview.h" ".\checkboxnumberview_moc_cpp.cpp"


SOURCE=.\colorview.cpp

"$(INTDIR)\colorview.obj" : $(SOURCE) "$(INTDIR)" ".\colorview.h" ".\colorview_moc_cpp.cpp"


SOURCE=.\comboboxstringview.cpp

"$(INTDIR)\comboboxstringview.obj" : $(SOURCE) "$(INTDIR)" ".\comboboxstringview_moc_cpp.cpp" ".\comboboxstringview.h"


SOURCE=.\dialnumberview.cpp

"$(INTDIR)\dialnumberview.obj" : $(SOURCE) "$(INTDIR)" ".\dialnumberview_moc_cpp.cpp" ".\dialnumberview.h"


SOURCE=.\filestringview.cpp

"$(INTDIR)\filestringview.obj" : $(SOURCE) "$(INTDIR)" ".\filestringview_moc_cpp.cpp" ".\filestringview.h" "..\..\..\config.h"


SOURCE=.\fontview.cpp

"$(INTDIR)\fontview.obj" : $(SOURCE) "$(INTDIR)" ".\fontview.h" ".\fontview_moc_cpp.cpp"


SOURCE=.\frameview.cpp

"$(INTDIR)\frameview.obj" : $(SOURCE) "$(INTDIR)" ".\frameview_moc_cpp.cpp" ".\frameview.h"


SOURCE=.\positionview.cpp

"$(INTDIR)\positionview.obj" : $(SOURCE) "$(INTDIR)" ".\positionview.h" ".\positionview_moc_cpp.cpp"


SOURCE=.\radionumberview.cpp

"$(INTDIR)\radionumberview.obj" : $(SOURCE) "$(INTDIR)" ".\radionumberview_moc_cpp.cpp" ".\radionumberview.h"


SOURCE=.\slidernumberview.cpp

"$(INTDIR)\slidernumberview.obj" : $(SOURCE) "$(INTDIR)" ".\slidernumberview_moc_cpp.cpp" ".\slidernumberview.h"


SOURCE=.\stringview.cpp

"$(INTDIR)\stringview.obj" : $(SOURCE) "$(INTDIR)" ".\stringview_moc_cpp.cpp" ".\stringview.h"


SOURCE=.\unboundednumberview.cpp

"$(INTDIR)\unboundednumberview.obj" : $(SOURCE) "$(INTDIR)" ".\unboundednumberview_moc_cpp.cpp" ".\unboundednumberview.h"


SOURCE=.\boundednumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\boundednumberview.h
InputName=boundednumberview

".\boundednumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\boundednumberview.h
InputName=boundednumberview

".\boundednumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\checkboxnumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\checkboxnumberview.h
InputName=checkboxnumberview

".\checkboxnumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\checkboxnumberview.h
InputName=checkboxnumberview

".\checkboxnumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\colorview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\colorview.h
InputName=colorview

".\colorview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\colorview.h
InputName=colorview

".\colorview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\comboboxstringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\comboboxstringview.h
InputName=comboboxstringview

".\comboboxstringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\comboboxstringview.h
InputName=comboboxstringview

".\comboboxstringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\dialnumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\dialnumberview.h
InputName=dialnumberview

".\dialnumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\dialnumberview.h
InputName=dialnumberview

".\dialnumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\filestringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\filestringview.h
InputName=filestringview

".\filestringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\filestringview.h
InputName=filestringview

".\filestringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\fontview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\fontview.h
InputName=fontview

".\fontview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\fontview.h
InputName=fontview

".\fontview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\frameview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\frameview.h
InputName=frameview

".\frameview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\frameview.h
InputName=frameview

".\frameview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\positionview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\positionview.h
InputName=positionview

".\positionview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\positionview.h
InputName=positionview

".\positionview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\radionumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\radionumberview.h
InputName=radionumberview

".\radionumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\radionumberview.h
InputName=radionumberview

".\radionumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\slidernumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\slidernumberview.h
InputName=slidernumberview

".\slidernumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\slidernumberview.h
InputName=slidernumberview

".\slidernumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\stringview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\stringview.h
InputName=stringview

".\stringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\stringview.h
InputName=stringview

".\stringview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=.\unboundednumberview.h

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=.\unboundednumberview.h
InputName=unboundednumberview

".\unboundednumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=.\unboundednumberview.h
InputName=unboundednumberview

".\unboundednumberview_moc_cpp.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(QTDIR)/bin/moc -o $(InputName)_moc_cpp_.cpp $(InputName).cpp 
	python ../../../../build/postmoc.py $(InputName)_moc_cpp_.cpp > $(InputName)_moc_cpp.cpp 
	del $(InputName)_moc_cpp_.cpp 
<< 
	

!ENDIF 

SOURCE=..\..\..\..\config_h.win32

!IF  "$(CFG)" == "typeviews - Win32 Release"

InputPath=..\..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "typeviews - Win32 Debug"

InputPath=..\..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

