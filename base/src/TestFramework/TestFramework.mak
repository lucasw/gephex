# Microsoft Developer Studio Generated NMAKE File, Based on TestFramework.dsp
!IF "$(CFG)" == ""
CFG=TestFramework - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. TestFramework - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "TestFramework - Win32 Release" && "$(CFG)" != "TestFramework - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "TestFramework.mak" CFG="TestFramework - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "TestFramework - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "TestFramework - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TestFramework - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "$(OUTDIR)\TestFramework.lib"


CLEAN :
	-@erase "$(INTDIR)\CompositeTest.obj"
	-@erase "$(INTDIR)\easytest.obj"
	-@erase "$(INTDIR)\LeafTest.obj"
	-@erase "$(INTDIR)\Tester.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestFramework.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /Ob2 /I "../../../util/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\TestFramework.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestFramework.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\TestFramework.lib" 
LIB32_OBJS= \
	"$(INTDIR)\CompositeTest.obj" \
	"$(INTDIR)\easytest.obj" \
	"$(INTDIR)\LeafTest.obj" \
	"$(INTDIR)\Tester.obj"

"$(OUTDIR)\TestFramework.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestFramework - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "$(OUTDIR)\TestFramework.lib"


CLEAN :
	-@erase "$(INTDIR)\CompositeTest.obj"
	-@erase "$(INTDIR)\easytest.obj"
	-@erase "$(INTDIR)\LeafTest.obj"
	-@erase "$(INTDIR)\Tester.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestFramework.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /W2 /Gm /Gi /GX /ZI /Od /I "../../../util/include" /D "WIN32" /D "_DEBUG" /D for="if (0) {} else for" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\TestFramework.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestFramework.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\TestFramework.lib" 
LIB32_OBJS= \
	"$(INTDIR)\CompositeTest.obj" \
	"$(INTDIR)\easytest.obj" \
	"$(INTDIR)\LeafTest.obj" \
	"$(INTDIR)\Tester.obj"

"$(OUTDIR)\TestFramework.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TestFramework.dep")
!INCLUDE "TestFramework.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestFramework.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestFramework - Win32 Release" || "$(CFG)" == "TestFramework - Win32 Debug"
SOURCE=.\CompositeTest.cpp

"$(INTDIR)\CompositeTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\easytest.cpp

"$(INTDIR)\easytest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LeafTest.cpp

"$(INTDIR)\LeafTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Tester.cpp

"$(INTDIR)\Tester.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

