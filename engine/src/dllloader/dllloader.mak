# Microsoft Developer Studio Generated NMAKE File, Based on dllloader.dsp
!IF "$(CFG)" == ""
CFG=dllloader - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. dllloader - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "dllloader - Win32 Release" && "$(CFG)" != "dllloader - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dllloader.mak" CFG="dllloader - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "dllloader - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "dllloader - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dllloader - Win32 Release"

OUTDIR=.\../../lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\../../lib/
# End Custom Macros

ALL : "$(OUTDIR)\dllloader.lib"


CLEAN :
	-@erase "$(INTDIR)\c_input.obj"
	-@erase "$(INTDIR)\c_output.obj"
	-@erase "$(INTDIR)\c_outputplug.obj"
	-@erase "$(INTDIR)\c_type.obj"
	-@erase "$(INTDIR)\c_typeclass.obj"
	-@erase "$(INTDIR)\dllloader.obj"
	-@erase "$(INTDIR)\frei0r_module.obj"
	-@erase "$(INTDIR)\frei0r_module_class.obj"
	-@erase "$(INTDIR)\frei0r_module_plugin.obj"
	-@erase "$(INTDIR)\gephex_module.obj"
	-@erase "$(INTDIR)\gephex_module_class.obj"
	-@erase "$(INTDIR)\gephex_module_plugin.obj"
	-@erase "$(INTDIR)\gephex_type_plugin.obj"
	-@erase "$(INTDIR)\moduleclassspec.obj"
	-@erase "$(INTDIR)\moduleinfoutils.obj"
	-@erase "$(INTDIR)\nameresolver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dllloader.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I ".." /I "../../../base/src" /I "../../../" /I "../../../util/include" /I "compat_vs6" /D "_LIB" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\dllloader.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dllloader.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\dllloader.lib" 
LIB32_OBJS= \
	"$(INTDIR)\c_input.obj" \
	"$(INTDIR)\c_output.obj" \
	"$(INTDIR)\c_outputplug.obj" \
	"$(INTDIR)\c_type.obj" \
	"$(INTDIR)\c_typeclass.obj" \
	"$(INTDIR)\dllloader.obj" \
	"$(INTDIR)\frei0r_module.obj" \
	"$(INTDIR)\frei0r_module_class.obj" \
	"$(INTDIR)\frei0r_module_plugin.obj" \
	"$(INTDIR)\gephex_module.obj" \
	"$(INTDIR)\gephex_module_class.obj" \
	"$(INTDIR)\gephex_module_plugin.obj" \
	"$(INTDIR)\gephex_type_plugin.obj" \
	"$(INTDIR)\moduleclassspec.obj" \
	"$(INTDIR)\moduleinfoutils.obj" \
	"$(INTDIR)\nameresolver.obj"

"$(OUTDIR)\dllloader.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dllloader - Win32 Debug"

OUTDIR=.\../../lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\../../lib
# End Custom Macros

ALL : "..\..\..\config.h" "$(OUTDIR)\dllloader.lib"


CLEAN :
	-@erase "$(INTDIR)\c_input.obj"
	-@erase "$(INTDIR)\c_output.obj"
	-@erase "$(INTDIR)\c_outputplug.obj"
	-@erase "$(INTDIR)\c_type.obj"
	-@erase "$(INTDIR)\c_typeclass.obj"
	-@erase "$(INTDIR)\dllloader.obj"
	-@erase "$(INTDIR)\frei0r_module.obj"
	-@erase "$(INTDIR)\frei0r_module_class.obj"
	-@erase "$(INTDIR)\frei0r_module_plugin.obj"
	-@erase "$(INTDIR)\gephex_module.obj"
	-@erase "$(INTDIR)\gephex_module_class.obj"
	-@erase "$(INTDIR)\gephex_module_plugin.obj"
	-@erase "$(INTDIR)\gephex_type_plugin.obj"
	-@erase "$(INTDIR)\moduleclassspec.obj"
	-@erase "$(INTDIR)\moduleinfoutils.obj"
	-@erase "$(INTDIR)\nameresolver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dllloader.lib"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I ".." /I "../../../base/src" /I "../../../" /I "../../../util/include" /I "compat_vs6" /D "_LIB" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /D ENGINE_VERBOSITY=0 /Fp"$(INTDIR)\dllloader.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dllloader.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\dllloader.lib" 
LIB32_OBJS= \
	"$(INTDIR)\c_input.obj" \
	"$(INTDIR)\c_output.obj" \
	"$(INTDIR)\c_outputplug.obj" \
	"$(INTDIR)\c_type.obj" \
	"$(INTDIR)\c_typeclass.obj" \
	"$(INTDIR)\dllloader.obj" \
	"$(INTDIR)\frei0r_module.obj" \
	"$(INTDIR)\frei0r_module_class.obj" \
	"$(INTDIR)\frei0r_module_plugin.obj" \
	"$(INTDIR)\gephex_module.obj" \
	"$(INTDIR)\gephex_module_class.obj" \
	"$(INTDIR)\gephex_module_plugin.obj" \
	"$(INTDIR)\gephex_type_plugin.obj" \
	"$(INTDIR)\moduleclassspec.obj" \
	"$(INTDIR)\moduleinfoutils.obj" \
	"$(INTDIR)\nameresolver.obj"

"$(OUTDIR)\dllloader.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("dllloader.dep")
!INCLUDE "dllloader.dep"
!ELSE 
!MESSAGE Warning: cannot find "dllloader.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dllloader - Win32 Release" || "$(CFG)" == "dllloader - Win32 Debug"
SOURCE=.\c_input.cpp

"$(INTDIR)\c_input.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\c_output.cpp

"$(INTDIR)\c_output.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\c_outputplug.cpp

"$(INTDIR)\c_outputplug.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\c_type.cpp

"$(INTDIR)\c_type.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\c_typeclass.cpp

"$(INTDIR)\c_typeclass.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dllloader.cpp

"$(INTDIR)\dllloader.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\frei0r_module.cpp

"$(INTDIR)\frei0r_module.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\frei0r_module_class.cpp

"$(INTDIR)\frei0r_module_class.obj" : $(SOURCE) "$(INTDIR)" "..\..\..\config.h"


SOURCE=.\frei0r_module_plugin.cpp

"$(INTDIR)\frei0r_module_plugin.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gephex_module.cpp

"$(INTDIR)\gephex_module.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gephex_module_class.cpp

"$(INTDIR)\gephex_module_class.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gephex_module_plugin.cpp

"$(INTDIR)\gephex_module_plugin.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gephex_type_plugin.cpp

"$(INTDIR)\gephex_type_plugin.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleclassspec.cpp

"$(INTDIR)\moduleclassspec.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\moduleinfoutils.cpp

"$(INTDIR)\moduleinfoutils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\nameresolver.cpp

"$(INTDIR)\nameresolver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "dllloader - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "dllloader - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

