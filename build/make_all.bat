if not exist ..\dlls mkdir ..\dlls
if not exist ..\dlls\modules mkdir ..\dlls\modules
if not exist ..\dlls\types mkdir ..\dlls\types
if not exist ..\bin mkdir ..\bin
if not exist ..\graphs mkdir ..\graphs
if not exist ..\gephex.conf copy ..\data\gephexw.conf.default ..\gephex.conf
if not exist ..\config.h copy ..\config_h.win32 ..\config.h
if %1/==/ goto usage

set CONFIG=%1
set TARGET=%2
set MAKE=NMAKE
set MAKE_FLAGS=/NOLOGO Recurse=1

cd dummy
%MAKE% CFG="dummy - Win32 %CONFIG%" %MAKE_FLAGS% /F dummy.mak %TARGET%
if errorlevel 1 goto error
cd ..

cd ..\base\src\interfaces

%MAKE% CFG="interfaces - Win32 %CONFIG%" %MAKE_FLAGS% /F interfaces.mak %TARGET%
if errorlevel 1 goto error
cd ..\..\..\build


cd ..\engine\src\engine
%MAKE% CFG="engine - Win32 %CONFIG%" %MAKE_FLAGS% /F engine.mak %TARGET%
if errorlevel 1 goto error
cd ..\..\..\build

cd ..\qtgui\src\gui
%MAKE% CFG="gui - Win32 %CONFIG%" %MAKE_FLAGS% /F gui.mak %TARGET%
cd ..\..\..\build

goto end

:usage

@echo "No config specified"
@echo "Usage: make_all.bat <CONFIG> [<TARGET>]"
@echo "   <CONFIG> ::= Debug | Release"
@echo "   <TARGET> ::= CLEAN"
@echo "   If no target is given, everything is built"

goto end

:error

@echo " **** ERROR - Build not successful"

:end
