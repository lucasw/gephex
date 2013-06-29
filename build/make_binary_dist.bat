@echo off

set TARGET_DIR=%1
set CONFIG_FILE="..\data\gephexw.conf.default"

if exist %TARGET_DIR% goto error_target_exists

mkdir %TARGET_DIR%
if errorlevel 1 goto error_cant_create

echo "- Copying stuff..."
xcopy /E /V /I ..\bin %TARGET_DIR%\bin
xcopy /E /V /I ..\dlls %TARGET_DIR%\dlls
mkdir %TARGET_DIR%\dlls\frei0rs
xcopy /E /V /I ..\examples %TARGET_DIR%\examples
xcopy /E /V /I ..\doc %TARGET_DIR%\doc

echo "- Recoding stuff..."
copy ..\AUTHORS %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\AUTHORS
copy ..\COPYING %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\COPYING
copy ..\NEWS %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\NEWS
copy ..\README %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\README
copy ..\README.win32 %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\README.win32
copy ..\BUGS %TARGET_DIR%
recode latin1..ibmpc %TARGET_DIR%\BUGS


echo "- Installing config file '%CONFIG_FILE%'"
copy %CONFIG_FILE% %TARGET_DIR%\gephex.conf
recode latin1..ibmpc %TARGET_DIR%\gephex.conf


echo "- Installing examples..."
mkdir %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\example1 %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\example2 %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\example3 %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\gephexwin32 %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\fzcam4 %TARGET_DIR%\graphs
copy %TARGET_DIR%\examples\graphs\noise %TARGET_DIR%\graphs



rem echo "- Removing arch folders and Makefiles..."
rem find $DISTDIR -name "{arch}" -o -name ".arch-ids" -o -name "Makefile.am" | xargs rm -rf

set LIB_ADD_PATH=c:\gphx_dist_data\extra_dlls\
echo "- Copying * from %LIB_ADD_PATH% to bin dir"
copy %LIB_ADD_PATH%\* %TARGET_DIR%\bin

goto end

:error_target_exists
echo "Dir %TARGET_DIR% already exists!"
goto end

:error_cant_create
echo "Cannot create %TARGET_DIR%!"
goto end


:end
