# Microsoft Developer Studio Generated NMAKE File, Based on engine.dsp
!IF "$(CFG)" == ""
CFG=engine - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. engine - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "engine - Win32 Release" && "$(CFG)" != "engine - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak" CFG="engine - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "engine - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "engine - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "engine - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\config.h" "$(OUTDIR)\gephex-engine.exe"

!ELSE 

ALL : "renderer - Win32 Release" "model - Win32 Release" "dllloader - Win32 Release" "utils - Win32 Release" "netinterfaces - Win32 Release" "net - Win32 Release" "interfaces - Win32 Release" "..\..\config.h" "$(OUTDIR)\gephex-engine.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"interfaces - Win32 ReleaseCLEAN" "net - Win32 ReleaseCLEAN" "netinterfaces - Win32 ReleaseCLEAN" "utils - Win32 ReleaseCLEAN" "dllloader - Win32 ReleaseCLEAN" "model - Win32 ReleaseCLEAN" "renderer - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bufferedsender.obj"
	-@erase "$(INTDIR)\controller.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\netlogger.obj"
	-@erase "$(INTDIR)\scheduler.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\gephex-engine.exe"
	-@erase "$(OUTDIR)\gephex-engine.map"
	-@erase "..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /w /W0 /GR /GX /O2 /Ob2 /I "../../../util/include" /I ".." /I "../../../base/src/utils" /I "../../../base/src/net" /I "../../../" /I "../../../base/src/" /I "../../../base/src/interfaces" /I "../../../base/src/netinterfaces" /I "../model" /I "../dllloader" /I "../renderer" /I "../sequencer" /D "_CONSOLE" /D "NDEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\engine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\engine.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /profile /map:"$(INTDIR)\gephex-engine.map" /machine:I386 /out:"$(OUTDIR)\gephex-engine.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bufferedsender.obj" \
	"$(INTDIR)\controller.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\netlogger.obj" \
	"$(INTDIR)\scheduler.obj" \
	"..\..\..\base\lib\net.lib" \
	"..\..\..\base\lib\netinterfaces.lib" \
	"..\..\..\base\lib\utils.lib" \
	"..\..\lib\dllloader.lib" \
	"..\..\lib\model.lib" \
	"..\..\lib\renderer.lib"

"$(OUTDIR)\gephex-engine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

$(DS_POSTBUILD_DEP) : "renderer - Win32 Release" "model - Win32 Release" "dllloader - Win32 Release" "utils - Win32 Release" "netinterfaces - Win32 Release" "net - Win32 Release" "interfaces - Win32 Release" "..\..\config.h" "$(OUTDIR)\gephex-engine.exe"
   if not exist ..\..\..\bin\ mkdir ..\..\..\bin
	copy .\Release\gephex-engine.exe ..\..\..\bin
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\config.h" "$(OUTDIR)\gephex-engine.exe"

!ELSE 

ALL : "renderer - Win32 Debug" "model - Win32 Debug" "dllloader - Win32 Debug" "utils - Win32 Debug" "netinterfaces - Win32 Debug" "net - Win32 Debug" "interfaces - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\gephex-engine.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"interfaces - Win32 DebugCLEAN" "net - Win32 DebugCLEAN" "netinterfaces - Win32 DebugCLEAN" "utils - Win32 DebugCLEAN" "dllloader - Win32 DebugCLEAN" "model - Win32 DebugCLEAN" "renderer - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bufferedsender.obj"
	-@erase "$(INTDIR)\controller.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\netlogger.obj"
	-@erase "$(INTDIR)\scheduler.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\gephex-engine.exe"
	-@erase "$(OUTDIR)\gephex-engine.ilk"
	-@erase "$(OUTDIR)\gephex-engine.pdb"
	-@erase "..\..\..\config.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "../../../util/include" /I ".." /I "../../../base/src/utils" /I "../../../base/src/net" /I "../../../" /I "../../../base/src/" /I "../../../base/src/interfaces" /I "../../../base/src/netinterfaces" /I "../model" /I "../dllloader" /I "../renderer" /I "../sequencer" /D "_CONSOLE" /D "_DEBUG" /D "_MBCS" /D for="if (0) {} else for" /D "HAVE_CONFIG_H" /Fp"$(INTDIR)\engine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\engine.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\gephex-engine.pdb" /debug /machine:I386 /out:"$(OUTDIR)\gephex-engine.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bufferedsender.obj" \
	"$(INTDIR)\controller.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\netlogger.obj" \
	"$(INTDIR)\scheduler.obj" \
	"..\..\..\base\lib\net.lib" \
	"..\..\..\base\lib\netinterfaces.lib" \
	"..\..\..\base\lib\utils.lib" \
	"..\..\lib\dllloader.lib" \
	"..\..\lib\model.lib" \
	"..\..\lib\renderer.lib"

"$(OUTDIR)\gephex-engine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

$(DS_POSTBUILD_DEP) : "renderer - Win32 Debug" "model - Win32 Debug" "dllloader - Win32 Debug" "utils - Win32 Debug" "netinterfaces - Win32 Debug" "net - Win32 Debug" "interfaces - Win32 Debug" "..\..\..\config.h" "$(OUTDIR)\gephex-engine.exe"
   if not exist ..\..\..\bin\ mkdir ..\..\..\bin
	copy .\Debug\gephex-engine.exe ..\..\..\bin
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
!IF EXISTS("engine.dep")
!INCLUDE "engine.dep"
!ELSE 
!MESSAGE Warning: cannot find "engine.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "engine - Win32 Release" || "$(CFG)" == "engine - Win32 Debug"
SOURCE=.\bufferedsender.cpp

"$(INTDIR)\bufferedsender.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\controller.cpp

"$(INTDIR)\controller.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\netlogger.cpp

"$(INTDIR)\netlogger.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\scheduler.cpp

"$(INTDIR)\scheduler.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "engine - Win32 Release"

"interfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" 
   cd "..\..\..\engine\src\engine"

"interfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"interfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" 
   cd "..\..\..\engine\src\engine"

"interfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\interfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\interfaces.mak" CFG="interfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"net - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Release" 
   cd "..\..\..\engine\src\engine"

"net - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"net - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Debug" 
   cd "..\..\..\engine\src\engine"

"net - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\net"
   $(MAKE) /$(MAKEFLAGS) /F ".\net.mak" CFG="net - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"netinterfaces - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" 
   cd "..\..\..\engine\src\engine"

"netinterfaces - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"netinterfaces - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" 
   cd "..\..\..\engine\src\engine"

"netinterfaces - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\netinterfaces"
   $(MAKE) /$(MAKEFLAGS) /F ".\netinterfaces.mak" CFG="netinterfaces - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"utils - Win32 Release" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Release" 
   cd "..\..\..\engine\src\engine"

"utils - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"utils - Win32 Debug" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Debug" 
   cd "..\..\..\engine\src\engine"

"utils - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\base\src\utils"
   $(MAKE) /$(MAKEFLAGS) /F ".\utils.mak" CFG="utils - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\engine\src\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"dllloader - Win32 Release" : 
   cd "\code\gephex-0.4\engine\src\dllloader"
   $(MAKE) /$(MAKEFLAGS) /F ".\dllloader.mak" CFG="dllloader - Win32 Release" 
   cd "..\engine"

"dllloader - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\engine\src\dllloader"
   $(MAKE) /$(MAKEFLAGS) /F ".\dllloader.mak" CFG="dllloader - Win32 Release" RECURSE=1 CLEAN 
   cd "..\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"dllloader - Win32 Debug" : 
   cd "\code\gephex-0.4\engine\src\dllloader"
   $(MAKE) /$(MAKEFLAGS) /F ".\dllloader.mak" CFG="dllloader - Win32 Debug" 
   cd "..\engine"

"dllloader - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\engine\src\dllloader"
   $(MAKE) /$(MAKEFLAGS) /F ".\dllloader.mak" CFG="dllloader - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"model - Win32 Release" : 
   cd "\code\gephex-0.4\engine\src\model"
   $(MAKE) /$(MAKEFLAGS) /F ".\model.mak" CFG="model - Win32 Release" 
   cd "..\engine"

"model - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\engine\src\model"
   $(MAKE) /$(MAKEFLAGS) /F ".\model.mak" CFG="model - Win32 Release" RECURSE=1 CLEAN 
   cd "..\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"model - Win32 Debug" : 
   cd "\code\gephex-0.4\engine\src\model"
   $(MAKE) /$(MAKEFLAGS) /F ".\model.mak" CFG="model - Win32 Debug" 
   cd "..\engine"

"model - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\engine\src\model"
   $(MAKE) /$(MAKEFLAGS) /F ".\model.mak" CFG="model - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\engine"

!ENDIF 

!IF  "$(CFG)" == "engine - Win32 Release"

"renderer - Win32 Release" : 
   cd "\code\gephex-0.4\engine\src\renderer"
   $(MAKE) /$(MAKEFLAGS) /F ".\renderer.mak" CFG="renderer - Win32 Release" 
   cd "..\engine"

"renderer - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\engine\src\renderer"
   $(MAKE) /$(MAKEFLAGS) /F ".\renderer.mak" CFG="renderer - Win32 Release" RECURSE=1 CLEAN 
   cd "..\engine"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

"renderer - Win32 Debug" : 
   cd "\code\gephex-0.4\engine\src\renderer"
   $(MAKE) /$(MAKEFLAGS) /F ".\renderer.mak" CFG="renderer - Win32 Debug" 
   cd "..\engine"

"renderer - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\engine\src\renderer"
   $(MAKE) /$(MAKEFLAGS) /F ".\renderer.mak" CFG="renderer - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\engine"

!ENDIF 

SOURCE=..\..\..\config_h.win32

!IF  "$(CFG)" == "engine - Win32 Release"

InputPath=..\..\..\config_h.win32

"..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath) ..\..\config.h
<< 
	

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

InputPath=..\..\..\config_h.win32

"..\..\..\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy $(InputPath)  ..\..\..\config.h
<< 
	

!ENDIF 


!ENDIF 

