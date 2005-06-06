# Microsoft Developer Studio Generated NMAKE File, Based on dummy.dsp
!IF "$(CFG)" == ""
CFG=dummy - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. dummy - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "dummy - Win32 Release" && "$(CFG)" != "dummy - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dummy.mak" CFG="dummy - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "dummy - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "dummy - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "dummy - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dummy.exe"

!ELSE 

ALL : "effectv1dmodule - Win32 Release" "effectvwarpmodule - Win32 Release" "effectvwarholmodule - Win32 Release" "effectvtransformmodule - Win32 Release" "effectvstreakmodule - Win32 Release" "effectvspiralmodule - Win32 Release" "effectvsimuramodule - Win32 Release" "effectvshagadelicmodule - Win32 Release" "effectvscrollmodule - Win32 Release" "effectvrndmmodule - Win32 Release" "effectvripplemodule - Win32 Release" "effectvrevmodule - Win32 Release" "effectvrdsmodule - Win32 Release" "effectvpupmodule - Win32 Release" "effectvnoisemodule - Win32 Release" "effectvnervousmodule - Win32 Release" "effectvmosaicmodule - Win32 Release" "effectvmatrixmodule - Win32 Release" "effectvdizzymodule - Win32 Release" "effectvdiffmodule - Win32 Release" "effectvdicemodule - Win32 Release" "effectvchameleonmodule - Win32 Release" "effectvblurzoommodule - Win32 Release" "effectvbaltanmodule - Win32 Release" "timesourcemodule - Win32 Release" "centermodule - Win32 Release" "signalplotmodule - Win32 Release" "pongmodule - Win32 Release" "ffmpegoutmodule - Win32 Release" "y4moutputmodule - Win32 Release" "y4minmodule - Win32 Release" "noisemodule - Win32 Release" "chromakeymodule - Win32 Release"\
 "dplmodule - Win32 Release" "xfademodule - Win32 Release" "twolayermodule - Win32 Release" "tunnelmodule - Win32 Release" "stringtype - Win32 Release" "stringtokenizermodule - Win32 Release" "staticcolormodule - Win32 Release" "signalgenmodule - Win32 Release" "sdlfontmodule - Win32 Release" "rotozoommodule - Win32 Release" "rgbtype - Win32 Release" "resultmodule - Win32 Release" "rangeconvertmodule - Win32 Release" "posnummodule - Win32 Release" "positiontype - Win32 Release" "plasmamodule - Win32 Release" "planemodule - Win32 Release" "pixelizemodule - Win32 Release" "overlaymodule - Win32 Release" "numxfadermodule - Win32 Release" "numposmodule - Win32 Release" "numlfomodule - Win32 Release" "numenvmodule - Win32 Release" "numbertype - Win32 Release" "numbermodule - Win32 Release" "number2colormodule - Win32 Release" "numarithmodule - Win32 Release" "netcontrolmodule - Win32 Release" "miditype - Win32 Release" "midiinmodule - Win32 Release" "lfotype - Win32 Release" "jumpmodule - Win32 Release" "joystickmodule - Win32 Release" "isingnoizemodule - Win32 Release" "imgarithmodule - Win32 Release" "imagebuffermodule - Win32 Release" "ifsxfadermodule - Win32 Release"\
 "ifstype - Win32 Release" "ifsmodule - Win32 Release" "ifsgenmodule - Win32 Release" "gradnormmodule - Win32 Release" "funparsemodule - Win32 Release" "frboutmodule - Win32 Release" "frbinmodule - Win32 Release" "framebuffertype - Win32 Release" "fpsmodule - Win32 Release" "fonttype - Win32 Release" "font3Dmodule - Win32 Release" "flipflopmodule - Win32 Release" "flashmodule - Win32 Release" "envtype - Win32 Release" "effectvsparkmodule - Win32 Release" "effectvquarkmodule - Win32 Release" "effectvpuzzlemodule - Win32 Release" "effectvlifemodule - Win32 Release" "effectvlensmodule - Win32 Release" "effectvfiremodule - Win32 Release" "effectvedgemodule - Win32 Release" "effectvdotmodule - Win32 Release" "effectvcyclemodule - Win32 Release" "effectvburnmodule - Win32 Release" "effectvagingmodule - Win32 Release" "doepfermodule - Win32 Release" "diffmodule - Win32 Release" "color2numbermodule - Win32 Release" "capturemodule - Win32 Release" "bwmodule - Win32 Release" "blurmodule - Win32 Release" "audiowavegenmodule - Win32 Release" "audiovismodule - Win32 Release" "audiotype - Win32 Release" "audiosynthmodule - Win32 Release" "audiospecmodule - Win32 Release"\
 "audiooutmodule - Win32 Release" "audioinmodule - Win32 Release" "audioenergymodule - Win32 Release" "audiobdmodule - Win32 Release" "audioaddmodule - Win32 Release" "$(OUTDIR)\dummy.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"audioaddmodule - Win32 ReleaseCLEAN" "audiobdmodule - Win32 ReleaseCLEAN" "audioenergymodule - Win32 ReleaseCLEAN" "audioinmodule - Win32 ReleaseCLEAN" "audiooutmodule - Win32 ReleaseCLEAN" "audiospecmodule - Win32 ReleaseCLEAN" "audiosynthmodule - Win32 ReleaseCLEAN" "audiotype - Win32 ReleaseCLEAN" "audiovismodule - Win32 ReleaseCLEAN" "audiowavegenmodule - Win32 ReleaseCLEAN" "blurmodule - Win32 ReleaseCLEAN" "bwmodule - Win32 ReleaseCLEAN" "capturemodule - Win32 ReleaseCLEAN" "color2numbermodule - Win32 ReleaseCLEAN" "diffmodule - Win32 ReleaseCLEAN" "doepfermodule - Win32 ReleaseCLEAN" "effectvagingmodule - Win32 ReleaseCLEAN" "effectvburnmodule - Win32 ReleaseCLEAN" "effectvcyclemodule - Win32 ReleaseCLEAN" "effectvdotmodule - Win32 ReleaseCLEAN" "effectvedgemodule - Win32 ReleaseCLEAN" "effectvfiremodule - Win32 ReleaseCLEAN" "effectvlensmodule - Win32 ReleaseCLEAN" "effectvlifemodule - Win32 ReleaseCLEAN" "effectvpuzzlemodule - Win32 ReleaseCLEAN" "effectvquarkmodule - Win32 ReleaseCLEAN" "effectvsparkmodule - Win32 ReleaseCLEAN" "envtype - Win32 ReleaseCLEAN" "flashmodule - Win32 ReleaseCLEAN" "flipflopmodule - Win32 ReleaseCLEAN"\
 "font3Dmodule - Win32 ReleaseCLEAN" "fonttype - Win32 ReleaseCLEAN" "fpsmodule - Win32 ReleaseCLEAN" "framebuffertype - Win32 ReleaseCLEAN" "frbinmodule - Win32 ReleaseCLEAN" "frboutmodule - Win32 ReleaseCLEAN" "funparsemodule - Win32 ReleaseCLEAN" "gradnormmodule - Win32 ReleaseCLEAN" "ifsgenmodule - Win32 ReleaseCLEAN" "ifsmodule - Win32 ReleaseCLEAN" "ifstype - Win32 ReleaseCLEAN" "ifsxfadermodule - Win32 ReleaseCLEAN" "imagebuffermodule - Win32 ReleaseCLEAN" "imgarithmodule - Win32 ReleaseCLEAN" "isingnoizemodule - Win32 ReleaseCLEAN" "joystickmodule - Win32 ReleaseCLEAN" "jumpmodule - Win32 ReleaseCLEAN" "lfotype - Win32 ReleaseCLEAN" "midiinmodule - Win32 ReleaseCLEAN" "miditype - Win32 ReleaseCLEAN" "netcontrolmodule - Win32 ReleaseCLEAN" "numarithmodule - Win32 ReleaseCLEAN" "number2colormodule - Win32 ReleaseCLEAN" "numbermodule - Win32 ReleaseCLEAN" "numbertype - Win32 ReleaseCLEAN" "numenvmodule - Win32 ReleaseCLEAN" "numlfomodule - Win32 ReleaseCLEAN" "numposmodule - Win32 ReleaseCLEAN" "numxfadermodule - Win32 ReleaseCLEAN" "overlaymodule - Win32 ReleaseCLEAN" "pixelizemodule - Win32 ReleaseCLEAN" "planemodule - Win32 ReleaseCLEAN" "plasmamodule - Win32 ReleaseCLEAN"\
 "positiontype - Win32 ReleaseCLEAN" "posnummodule - Win32 ReleaseCLEAN" "rangeconvertmodule - Win32 ReleaseCLEAN" "resultmodule - Win32 ReleaseCLEAN" "rgbtype - Win32 ReleaseCLEAN" "rotozoommodule - Win32 ReleaseCLEAN" "sdlfontmodule - Win32 ReleaseCLEAN" "signalgenmodule - Win32 ReleaseCLEAN" "staticcolormodule - Win32 ReleaseCLEAN" "stringtokenizermodule - Win32 ReleaseCLEAN" "stringtype - Win32 ReleaseCLEAN" "tunnelmodule - Win32 ReleaseCLEAN" "twolayermodule - Win32 ReleaseCLEAN" "xfademodule - Win32 ReleaseCLEAN" "dplmodule - Win32 ReleaseCLEAN" "chromakeymodule - Win32 ReleaseCLEAN" "noisemodule - Win32 ReleaseCLEAN" "y4minmodule - Win32 ReleaseCLEAN" "y4moutputmodule - Win32 ReleaseCLEAN" "ffmpegoutmodule - Win32 ReleaseCLEAN" "pongmodule - Win32 ReleaseCLEAN" "signalplotmodule - Win32 ReleaseCLEAN" "centermodule - Win32 ReleaseCLEAN" "timesourcemodule - Win32 ReleaseCLEAN" "effectvbaltanmodule - Win32 ReleaseCLEAN" "effectvblurzoommodule - Win32 ReleaseCLEAN" "effectvchameleonmodule - Win32 ReleaseCLEAN" "effectvdicemodule - Win32 ReleaseCLEAN" "effectvdiffmodule - Win32 ReleaseCLEAN" "effectvdizzymodule - Win32 ReleaseCLEAN" "effectvmatrixmodule - Win32 ReleaseCLEAN"\
 "effectvmosaicmodule - Win32 ReleaseCLEAN" "effectvnervousmodule - Win32 ReleaseCLEAN" "effectvnoisemodule - Win32 ReleaseCLEAN" "effectvpupmodule - Win32 ReleaseCLEAN" "effectvrdsmodule - Win32 ReleaseCLEAN" "effectvrevmodule - Win32 ReleaseCLEAN" "effectvripplemodule - Win32 ReleaseCLEAN" "effectvrndmmodule - Win32 ReleaseCLEAN" "effectvscrollmodule - Win32 ReleaseCLEAN" "effectvshagadelicmodule - Win32 ReleaseCLEAN" "effectvsimuramodule - Win32 ReleaseCLEAN" "effectvspiralmodule - Win32 ReleaseCLEAN" "effectvstreakmodule - Win32 ReleaseCLEAN" "effectvtransformmodule - Win32 ReleaseCLEAN" "effectvwarholmodule - Win32 ReleaseCLEAN" "effectvwarpmodule - Win32 ReleaseCLEAN" "effectv1dmodule - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dummy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\dummy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dummy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\dummy.pdb" /machine:I386 /out:"$(OUTDIR)\dummy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\..\modules\src\audioaddmodule\Release\audioaddmodule.lib" \
	"..\..\modules\src\audiobdmodule\Release\audiobdmodule.lib" \
	"..\..\modules\src\audioenergymodule\Release\audioenergymodule.lib" \
	"..\..\modules\src\audioinmodule\Release\audioinmodule.lib" \
	"..\..\modules\src\audiooutmodule\Release\audiooutmodule.lib" \
	"..\..\modules\src\audiospecmodule\Release\audiospecmodule.lib" \
	"..\..\modules\src\audiosynthmodule\Release\audiosynthmodule.lib" \
	"..\..\types\src\audiotype\Release\audiotype.lib" \
	"..\..\modules\src\audiovismodule\Release\audiovismodule.lib" \
	"..\..\modules\src\audiowavegenmodule\Release\audiowavegenmodule.lib" \
	"..\..\modules\src\capturemodule\Release\capturemodule.lib" \
	"..\..\modules\src\color2numbermodule\Release\color2numbermodule.lib" \
	"..\..\modules\src\diffmodule\Release\diffmodule.lib" \
	"..\..\modules\src\doepfermodule\Release\doepfermodule.lib" \
	"..\..\effectvmodules\src\effectvagingmodule\Release\effectvagingmodule.lib" \
	"..\..\effectvmodules\src\effectvburnmodule\Release\effectvburnmodule.lib" \
	"..\..\effectvmodules\src\effectvcyclemodule\Release\effectvcyclemodule.lib" \
	"..\..\effectvmodules\src\effectvdotmodule\Release\effectvdotmodule.lib" \
	"..\..\effectvmodules\src\effectvedgemodule\Release\effectvedgemodule.lib" \
	"..\..\effectvmodules\src\effectvfiremodule\Release\effectvfiremodule.lib" \
	"..\..\effectvmodules\src\effectvlensmodule\Release\effectvlensmodule.lib" \
	"..\..\effectvmodules\src\effectvlifemodule\Release\effectvlifemodule.lib" \
	"..\..\effectvmodules\src\effectvpuzzlemodule\Release\effectvpuzzlemodule.lib" \
	"..\..\effectvmodules\src\effectvquarkmodule\Release\effectvquarkmodule.lib" \
	"..\..\effectvmodules\src\effectvsparkmodule\Release\effectvsparkmodule.lib" \
	"..\..\types\src\envtype\Release\envtype.lib" \
	"..\..\modules\src\flashmodule\Release\flashmodule.lib" \
	"..\..\modules\src\flipflopmodule\Release\flipflopmodule.lib" \
	"..\..\modules\src\font3Dmodule\Release\font3Dmodule.lib" \
	"..\..\types\src\fonttype\Release\fonttype.lib" \
	"..\..\modules\src\fpsmodule\Release\fpsmodule.lib" \
	"..\..\types\src\framebuffertype\Release\framebuffertype.lib" \
	"..\..\modules\src\frbinmodule\Release\frbinmodule.lib" \
	"..\..\modules\src\frboutmodule\Release\frboutmodule.lib" \
	"..\..\modules\src\funparsemodule\Release\funparsemodule.lib" \
	"..\..\modules\src\gradnormmodule\Release\gradnormmodule.lib" \
	"..\..\modules\src\ifsgenmodule\Release\ifsgenmodule.lib" \
	"..\..\modules\src\ifsmodule\Release\ifsmodule.lib" \
	"..\..\types\src\ifstype\Release\ifstype.lib" \
	"..\..\modules\src\ifsxfadermodule\Release\ifsxfadermodule.lib" \
	"..\..\modules\src\imagebuffermodule\Release\imagebuffermodule.lib" \
	"..\..\modules\src\imgarithmodule\Release\imgarithmodule.lib" \
	"..\..\modules\src\isingnoizemodule\Release\isingnoizemodule.lib" \
	"..\..\modules\src\joystickmodule\Release\joystickmodule.lib" \
	"..\..\types\src\lfotype\Release\lfotype.lib" \
	"..\..\modules\src\midiinmodule\Release\midiinmodule.lib" \
	"..\..\types\src\miditype\Release\miditype.lib" \
	"..\..\modules\src\netcontrolmodule\Release\netcontrolmodule.lib" \
	"..\..\modules\src\numarithmodule\Release\numarithmodule.lib" \
	"..\..\modules\src\number2colormodule\Release\number2colormodule.lib" \
	"..\..\types\src\numbertype\Release\numbertype.lib" \
	"..\..\modules\src\numenvmodule\Release\numenvmodule.lib" \
	"..\..\modules\src\numlfomodule\Release\numlfomodule.lib" \
	"..\..\modules\src\overlaymodule\Release\overlaymodule.lib" \
	"..\..\modules\src\pixelizemodule\Release\pixelizemodule.lib" \
	"..\..\modules\src\planemodule\Release\planemodule.lib" \
	"..\..\types\src\positiontype\Release\positiontype.lib" \
	"..\..\modules\src\rangeconvertmodule\Release\rangeconvertmodule.lib" \
	"..\..\types\src\rgbtype\Release\rgbtype.lib" \
	"..\..\modules\src\rotozoommodule\Release\rotozoommodule.lib" \
	"..\..\modules\src\sdlfontmodule\Release\sdlfontmodule.lib" \
	"..\..\modules\src\stringtokenizermodule\Release\stringtokenizermodule.lib" \
	"..\..\types\src\stringtype\Release\stringtype.lib" \
	"..\..\modules\src\twolayermodule\Release\twolayermodule.lib" \
	"..\..\modules\src\xfademodule\Release\xfademodule.lib" \
	"..\..\modules\src\dplmodule\Release\dplmodule.lib" \
	"..\..\modules\src\chromakeymodule\Release\chromakeymodule.lib" \
	"..\..\modules\src\noisemodule\Release\noisemodule.lib" \
	"..\..\modules\src\y4minmodule\Release\y4minmodule.lib" \
	"..\..\modules\src\yuv4mpeg2module\Release\y4moutputmodule.lib" \
	"..\..\modules\src\ffmpegoutmodule\Release\ffmpegoutmodule.lib" \
	"..\..\modules\src\pongmodule\Release\pongmodule.lib" \
	"..\..\modules\src\signalplotmodule\Release\signalplotmodule.lib" \
	"..\..\modules\src\centermodule\Release\centermodule.lib" \
	"..\..\modules\src\timesourcemodule\Release\timesourcemodule.lib" \
	"..\..\effectvmodules\src\effectvbaltanmodule\Release\effectvbaltanmodule.lib" \
	"..\..\effectvmodules\src\effectvblurzoommodule\Release\effectvblurzoommodule.lib" \
	"..\..\effectvmodules\src\effectvchameleonmodule\Release\effectvchameleonmodule.lib" \
	"..\..\effectvmodules\src\effectvdicemodule\Release\effectvdicemodule.lib" \
	"..\..\effectvmodules\src\effectvdiffmodule\Release\effectvdiffmodule.lib" \
	"..\..\effectvmodules\src\effectvdizzymodule\Release\effectvdizzymodule.lib" \
	"..\..\effectvmodules\src\effectvmatrixmodule\Release\effectvmatrixmodule.lib" \
	"..\..\effectvmodules\src\effectvmosaicmodule\Release\effectvmosaicmodule.lib" \
	"..\..\effectvmodules\src\effectvnervousmodule\Release\effectvnervousmodule.lib" \
	"..\..\effectvmodules\src\effectvnoisemodule\Release\effectvnoisemodule.lib" \
	"..\..\effectvmodules\src\effectvpupmodule\Release\effectvpupmodule.lib" \
	"..\..\effectvmodules\src\effectvrdsmodule\Release\effectvrdsmodule.lib" \
	"..\..\effectvmodules\src\effectvrevmodule\Release\effectvrevmodule.lib" \
	"..\..\effectvmodules\src\effectvripplemodule\Release\effectvripplemodule.lib" \
	"..\..\effectvmodules\src\effectvrndmmodule\Release\effectvrndmmodule.lib" \
	"..\..\effectvmodules\src\effectvscrollmodule\Release\effectvscrollmodule.lib" \
	"..\..\effectvmodules\src\effectvshagadelicmodule\Release\effectvshagadelicmodule.lib" \
	"..\..\effectvmodules\src\effectvsimuramodule\Release\effectvsimuramodule.lib" \
	"..\..\effectvmodules\src\effectvspiralmodule\Release\effectvspiralmodule.lib" \
	"..\..\effectvmodules\src\effectvstreakmodule\Release\effectvstreakmodule.lib" \
	"..\..\effectvmodules\src\effectvtransformmodule\Release\effectvtransformmodule.lib" \
	"..\..\effectvmodules\src\effectvwarholmodule\Release\effectvwarholmodule.lib" \
	"..\..\effectvmodules\src\effectvwarpmodule\Release\effectvwarpmodule.lib" \
	"..\..\effectvmodules\src\effectv1dmodule\Release\effectv1dmodule.lib"

"$(OUTDIR)\dummy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dummy.exe"

!ELSE 

ALL : "effectv1dmodule - Win32 Debug" "effectvwarpmodule - Win32 Debug" "effectvwarholmodule - Win32 Debug" "effectvtransformmodule - Win32 Debug" "effectvstreakmodule - Win32 Debug" "effectvspiralmodule - Win32 Debug" "effectvsimuramodule - Win32 Debug" "effectvshagadelicmodule - Win32 Debug" "effectvscrollmodule - Win32 Debug" "effectvrndmmodule - Win32 Debug" "effectvripplemodule - Win32 Debug" "effectvrevmodule - Win32 Debug" "effectvrdsmodule - Win32 Debug" "effectvpupmodule - Win32 Debug" "effectvnoisemodule - Win32 Debug" "effectvnervousmodule - Win32 Debug" "effectvmosaicmodule - Win32 Debug" "effectvmatrixmodule - Win32 Debug" "effectvdizzymodule - Win32 Debug" "effectvdiffmodule - Win32 Debug" "effectvdicemodule - Win32 Debug" "effectvchameleonmodule - Win32 Debug" "effectvblurzoommodule - Win32 Debug" "effectvbaltanmodule - Win32 Debug" "timesourcemodule - Win32 Debug" "centermodule - Win32 Debug" "signalplotmodule - Win32 Debug" "pongmodule - Win32 Debug" "ffmpegoutmodule - Win32 Debug" "y4moutputmodule - Win32 Debug" "y4minmodule - Win32 Debug" "noisemodule - Win32 Debug" "chromakeymodule - Win32 Debug" "dplmodule - Win32 Debug" "xfademodule - Win32 Debug"\
 "twolayermodule - Win32 Debug" "tunnelmodule - Win32 Debug" "stringtype - Win32 Debug" "stringtokenizermodule - Win32 Debug" "staticcolormodule - Win32 Debug" "signalgenmodule - Win32 Debug" "sdlfontmodule - Win32 Debug" "rotozoommodule - Win32 Debug" "rgbtype - Win32 Debug" "resultmodule - Win32 Debug" "rangeconvertmodule - Win32 Debug" "posnummodule - Win32 Debug" "positiontype - Win32 Debug" "plasmamodule - Win32 Debug" "planemodule - Win32 Debug" "pixelizemodule - Win32 Debug" "overlaymodule - Win32 Debug" "numxfadermodule - Win32 Debug" "numposmodule - Win32 Debug" "numlfomodule - Win32 Debug" "numenvmodule - Win32 Debug" "numbertype - Win32 Debug" "numbermodule - Win32 Debug" "number2colormodule - Win32 Debug" "numarithmodule - Win32 Debug" "netcontrolmodule - Win32 Debug" "miditype - Win32 Debug" "midiinmodule - Win32 Debug" "lfotype - Win32 Debug" "jumpmodule - Win32 Debug" "joystickmodule - Win32 Debug" "isingnoizemodule - Win32 Debug" "imgarithmodule - Win32 Debug" "imagebuffermodule - Win32 Debug" "ifsxfadermodule - Win32 Debug" "ifstype - Win32 Debug" "ifsmodule - Win32 Debug" "ifsgenmodule - Win32 Debug" "gradnormmodule - Win32 Debug" "funparsemodule - Win32 Debug"\
 "frboutmodule - Win32 Debug" "frbinmodule - Win32 Debug" "framebuffertype - Win32 Debug" "fpsmodule - Win32 Debug" "fonttype - Win32 Debug" "font3Dmodule - Win32 Debug" "flipflopmodule - Win32 Debug" "flashmodule - Win32 Debug" "envtype - Win32 Debug" "effectvsparkmodule - Win32 Debug" "effectvquarkmodule - Win32 Debug" "effectvpuzzlemodule - Win32 Debug" "effectvlifemodule - Win32 Debug" "effectvlensmodule - Win32 Debug" "effectvfiremodule - Win32 Debug" "effectvedgemodule - Win32 Debug" "effectvdotmodule - Win32 Debug" "effectvcyclemodule - Win32 Debug" "effectvburnmodule - Win32 Debug" "effectvagingmodule - Win32 Debug" "doepfermodule - Win32 Debug" "diffmodule - Win32 Debug" "color2numbermodule - Win32 Debug" "capturemodule - Win32 Debug" "bwmodule - Win32 Debug" "blurmodule - Win32 Debug" "audiowavegenmodule - Win32 Debug" "audiovismodule - Win32 Debug" "audiotype - Win32 Debug" "audiosynthmodule - Win32 Debug" "audiospecmodule - Win32 Debug" "audiooutmodule - Win32 Debug" "audioinmodule - Win32 Debug" "audioenergymodule - Win32 Debug" "audiobdmodule - Win32 Debug" "audioaddmodule - Win32 Debug" "$(OUTDIR)\dummy.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"audioaddmodule - Win32 DebugCLEAN" "audiobdmodule - Win32 DebugCLEAN" "audioenergymodule - Win32 DebugCLEAN" "audioinmodule - Win32 DebugCLEAN" "audiooutmodule - Win32 DebugCLEAN" "audiospecmodule - Win32 DebugCLEAN" "audiosynthmodule - Win32 DebugCLEAN" "audiotype - Win32 DebugCLEAN" "audiovismodule - Win32 DebugCLEAN" "audiowavegenmodule - Win32 DebugCLEAN" "blurmodule - Win32 DebugCLEAN" "bwmodule - Win32 DebugCLEAN" "capturemodule - Win32 DebugCLEAN" "color2numbermodule - Win32 DebugCLEAN" "diffmodule - Win32 DebugCLEAN" "doepfermodule - Win32 DebugCLEAN" "effectvagingmodule - Win32 DebugCLEAN" "effectvburnmodule - Win32 DebugCLEAN" "effectvcyclemodule - Win32 DebugCLEAN" "effectvdotmodule - Win32 DebugCLEAN" "effectvedgemodule - Win32 DebugCLEAN" "effectvfiremodule - Win32 DebugCLEAN" "effectvlensmodule - Win32 DebugCLEAN" "effectvlifemodule - Win32 DebugCLEAN" "effectvpuzzlemodule - Win32 DebugCLEAN" "effectvquarkmodule - Win32 DebugCLEAN" "effectvsparkmodule - Win32 DebugCLEAN" "envtype - Win32 DebugCLEAN" "flashmodule - Win32 DebugCLEAN" "flipflopmodule - Win32 DebugCLEAN" "font3Dmodule - Win32 DebugCLEAN" "fonttype - Win32 DebugCLEAN"\
 "fpsmodule - Win32 DebugCLEAN" "framebuffertype - Win32 DebugCLEAN" "frbinmodule - Win32 DebugCLEAN" "frboutmodule - Win32 DebugCLEAN" "funparsemodule - Win32 DebugCLEAN" "gradnormmodule - Win32 DebugCLEAN" "ifsgenmodule - Win32 DebugCLEAN" "ifsmodule - Win32 DebugCLEAN" "ifstype - Win32 DebugCLEAN" "ifsxfadermodule - Win32 DebugCLEAN" "imagebuffermodule - Win32 DebugCLEAN" "imgarithmodule - Win32 DebugCLEAN" "isingnoizemodule - Win32 DebugCLEAN" "joystickmodule - Win32 DebugCLEAN" "jumpmodule - Win32 DebugCLEAN" "lfotype - Win32 DebugCLEAN" "midiinmodule - Win32 DebugCLEAN" "miditype - Win32 DebugCLEAN" "netcontrolmodule - Win32 DebugCLEAN" "numarithmodule - Win32 DebugCLEAN" "number2colormodule - Win32 DebugCLEAN" "numbermodule - Win32 DebugCLEAN" "numbertype - Win32 DebugCLEAN" "numenvmodule - Win32 DebugCLEAN" "numlfomodule - Win32 DebugCLEAN" "numposmodule - Win32 DebugCLEAN" "numxfadermodule - Win32 DebugCLEAN" "overlaymodule - Win32 DebugCLEAN" "pixelizemodule - Win32 DebugCLEAN" "planemodule - Win32 DebugCLEAN" "plasmamodule - Win32 DebugCLEAN" "positiontype - Win32 DebugCLEAN" "posnummodule - Win32 DebugCLEAN" "rangeconvertmodule - Win32 DebugCLEAN"\
 "resultmodule - Win32 DebugCLEAN" "rgbtype - Win32 DebugCLEAN" "rotozoommodule - Win32 DebugCLEAN" "sdlfontmodule - Win32 DebugCLEAN" "signalgenmodule - Win32 DebugCLEAN" "staticcolormodule - Win32 DebugCLEAN" "stringtokenizermodule - Win32 DebugCLEAN" "stringtype - Win32 DebugCLEAN" "tunnelmodule - Win32 DebugCLEAN" "twolayermodule - Win32 DebugCLEAN" "xfademodule - Win32 DebugCLEAN" "dplmodule - Win32 DebugCLEAN" "chromakeymodule - Win32 DebugCLEAN" "noisemodule - Win32 DebugCLEAN" "y4minmodule - Win32 DebugCLEAN" "y4moutputmodule - Win32 DebugCLEAN" "ffmpegoutmodule - Win32 DebugCLEAN" "pongmodule - Win32 DebugCLEAN" "signalplotmodule - Win32 DebugCLEAN" "centermodule - Win32 DebugCLEAN" "timesourcemodule - Win32 DebugCLEAN" "effectvbaltanmodule - Win32 DebugCLEAN" "effectvblurzoommodule - Win32 DebugCLEAN" "effectvchameleonmodule - Win32 DebugCLEAN" "effectvdicemodule - Win32 DebugCLEAN" "effectvdiffmodule - Win32 DebugCLEAN" "effectvdizzymodule - Win32 DebugCLEAN" "effectvmatrixmodule - Win32 DebugCLEAN" "effectvmosaicmodule - Win32 DebugCLEAN" "effectvnervousmodule - Win32 DebugCLEAN" "effectvnoisemodule - Win32 DebugCLEAN" "effectvpupmodule - Win32 DebugCLEAN"\
 "effectvrdsmodule - Win32 DebugCLEAN" "effectvrevmodule - Win32 DebugCLEAN" "effectvripplemodule - Win32 DebugCLEAN" "effectvrndmmodule - Win32 DebugCLEAN" "effectvscrollmodule - Win32 DebugCLEAN" "effectvshagadelicmodule - Win32 DebugCLEAN" "effectvsimuramodule - Win32 DebugCLEAN" "effectvspiralmodule - Win32 DebugCLEAN" "effectvstreakmodule - Win32 DebugCLEAN" "effectvtransformmodule - Win32 DebugCLEAN" "effectvwarholmodule - Win32 DebugCLEAN" "effectvwarpmodule - Win32 DebugCLEAN" "effectv1dmodule - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dummy.exe"
	-@erase "$(OUTDIR)\dummy.ilk"
	-@erase "$(OUTDIR)\dummy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\dummy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dummy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\dummy.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dummy.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\..\modules\src\audioaddmodule\Debug\audioaddmodule.lib" \
	"..\..\modules\src\audiobdmodule\Debug\audiobdmodule.lib" \
	"..\..\modules\src\audioenergymodule\Debug\audioenergymodule.lib" \
	"..\..\modules\src\audioinmodule\Debug\audioinmodule.lib" \
	"..\..\modules\src\audiooutmodule\Debug\audiooutmodule.lib" \
	"..\..\modules\src\audiospecmodule\Debug\audiospecmodule.lib" \
	"..\..\modules\src\audiosynthmodule\Debug\audiosynthmodule.lib" \
	"..\..\types\src\audiotype\Debug\audiotype.lib" \
	"..\..\modules\src\audiovismodule\Debug\audiovismodule.lib" \
	"..\..\modules\src\audiowavegenmodule\Debug\audiowavegenmodule.lib" \
	"..\..\modules\src\blurmodule\Debug\blurmodule.lib" \
	"..\..\modules\src\bwmodule\Debug\bwmodule.lib" \
	"..\..\modules\src\capturemodule\Debug\capturemodule.lib" \
	"..\..\modules\src\color2numbermodule\Debug\color2numbermodule.lib" \
	"..\..\modules\src\diffmodule\Debug\diffmodule.lib" \
	"..\..\modules\src\doepfermodule\Debug\doepfermodule.lib" \
	"..\..\effectvmodules\src\effectvagingmodule\Debug\effectvagingmodule.lib" \
	"..\..\effectvmodules\src\effectvburnmodule\Debug\effectvburnmodule.lib" \
	"..\..\effectvmodules\src\effectvcyclemodule\Debug\effectvcyclemodule.lib" \
	"..\..\effectvmodules\src\effectvdotmodule\Debug\effectvdotmodule.lib" \
	"..\..\effectvmodules\src\effectvedgemodule\Debug\effectvedgemodule.lib" \
	"..\..\effectvmodules\src\effectvfiremodule\Debug\effectvfiremodule.lib" \
	"..\..\effectvmodules\src\effectvlensmodule\Debug\effectvlensmodule.lib" \
	"..\..\effectvmodules\src\effectvlifemodule\Debug\effectvlifemodule.lib" \
	"..\..\effectvmodules\src\effectvpuzzlemodule\Debug\effectvpuzzlemodule.lib" \
	"..\..\effectvmodules\src\effectvquarkmodule\Debug\effectvquarkmodule.lib" \
	"..\..\effectvmodules\src\effectvsparkmodule\Debug\effectvsparkmodule.lib" \
	"..\..\types\src\envtype\Debug\envtype.lib" \
	"..\..\modules\src\flashmodule\Debug\flashmodule.lib" \
	"..\..\modules\src\flipflopmodule\Debug\flipflopmodule.lib" \
	"..\..\modules\src\font3Dmodule\Debug\font3Dmodule.lib" \
	"..\..\types\src\fonttype\Debug\fonttype.lib" \
	"..\..\modules\src\fpsmodule\Debug\fpsmodule.lib" \
	"..\..\types\src\framebuffertype\Debug\framebuffertype.lib" \
	"..\..\modules\src\frbinmodule\Debug\frbinmodule.lib" \
	"..\..\modules\src\frboutmodule\Debug\frboutmodule.lib" \
	"..\..\modules\src\funparsemodule\Debug\funparsemodule.lib" \
	"..\..\modules\src\gradnormmodule\Debug\gradnormmodule.lib" \
	"..\..\modules\src\ifsgenmodule\Debug\ifsgenmodule.lib" \
	"..\..\modules\src\ifsmodule\Debug\ifsmodule.lib" \
	"..\..\types\src\ifstype\Debug\ifstype.lib" \
	"..\..\modules\src\ifsxfadermodule\Debug\ifsxfadermodule.lib" \
	"..\..\modules\src\imagebuffermodule\Debug\imagebuffermodule.lib" \
	"..\..\modules\src\imgarithmodule\Debug\imgarithmodule.lib" \
	"..\..\modules\src\isingnoizemodule\Debug\isingnoizemodule.lib" \
	"..\..\modules\src\joystickmodule\Debug\joystickmodule.lib" \
	"..\..\modules\src\jumpmodule\Debug\jumpmodule.lib" \
	"..\..\types\src\lfotype\Debug\lfotype.lib" \
	"..\..\modules\src\midiinmodule\Debug\midiinmodule.lib" \
	"..\..\types\src\miditype\Debug\miditype.lib" \
	"..\..\modules\src\netcontrolmodule\Debug\netcontrolmodule.lib" \
	"..\..\modules\src\numarithmodule\Debug\numarithmodule.lib" \
	"..\..\modules\src\number2colormodule\Debug\number2colormodule.lib" \
	"..\..\modules\src\numbermodule\Debug\numbermodule.lib" \
	"..\..\types\src\numbertype\Debug\numbertype.lib" \
	"..\..\modules\src\numenvmodule\Debug\numenvmodule.lib" \
	"..\..\modules\src\numlfomodule\Debug\numlfomodule.lib" \
	"..\..\modules\src\numposmodule\Debug\numposmodule.lib" \
	"..\..\modules\src\numxfadermodule\Debug\numxfadermodule.lib" \
	"..\..\modules\src\overlaymodule\Debug\overlaymodule.lib" \
	"..\..\modules\src\pixelizemodule\Debug\pixelizemodule.lib" \
	"..\..\modules\src\planemodule\Debug\planemodule.lib" \
	"..\..\modules\src\plasmamodule\Debug\plasmamodule.lib" \
	"..\..\types\src\positiontype\Debug\positiontype.lib" \
	"..\..\modules\src\posnummodule\Debug\posnummodule.lib" \
	"..\..\modules\src\rangeconvertmodule\Debug\rangeconvertmodule.lib" \
	"..\..\modules\src\resultmodule\Debug\resultmodule.lib" \
	"..\..\types\src\rgbtype\Debug\rgbtype.lib" \
	"..\..\modules\src\rotozoommodule\Debug\rotozoommodule.lib" \
	"..\..\modules\src\sdlfontmodule\Debug\sdlfontmodule.lib" \
	"..\..\modules\src\signalgenmodule\Debug\signalgenmodule.lib" \
	"..\..\modules\src\staticcolormodule\Debug\staticcolormodule.lib" \
	"..\..\modules\src\stringtokenizermodule\Debug\stringtokenizermodule.lib" \
	"..\..\types\src\stringtype\Debug\stringtype.lib" \
	"..\..\modules\src\tunnelmodule\Debug\tunnelmodule.lib" \
	"..\..\modules\src\twolayermodule\Debug\twolayermodule.lib" \
	"..\..\modules\src\xfademodule\Debug\xfademodule.lib" \
	"..\..\modules\src\dplmodule\Debug\dplmodule.lib" \
	"..\..\modules\src\chromakeymodule\Debug\chromakeymodule.lib" \
	"..\..\modules\src\noisemodule\Debug\noisemodule.lib" \
	"..\..\modules\src\y4minmodule\Debug\y4minmodule.lib" \
	"..\..\modules\src\yuv4mpeg2module\Debug\y4moutputmodule.lib" \
	"..\..\modules\src\ffmpegoutmodule\Debug\ffmpegoutmodule.lib" \
	"..\..\modules\src\pongmodule\Debug\pongmodule.lib" \
	"..\..\modules\src\signalplotmodule\Debug\signalplotmodule.lib" \
	"..\..\modules\src\centermodule\Debug\centermodule.lib" \
	"..\..\modules\src\timesourcemodule\Debug\timesourcemodule.lib" \
	"..\..\effectvmodules\src\effectvbaltanmodule\Debug\effectvbaltanmodule.lib" \
	"..\..\effectvmodules\src\effectvblurzoommodule\Debug\effectvblurzoommodule.lib" \
	"..\..\effectvmodules\src\effectvchameleonmodule\Debug\effectvchameleonmodule.lib" \
	"..\..\effectvmodules\src\effectvdicemodule\Debug\effectvdicemodule.lib" \
	"..\..\effectvmodules\src\effectvdiffmodule\Debug\effectvdiffmodule.lib" \
	"..\..\effectvmodules\src\effectvdizzymodule\Debug\effectvdizzymodule.lib" \
	"..\..\effectvmodules\src\effectvmatrixmodule\Debug\effectvmatrixmodule.lib" \
	"..\..\effectvmodules\src\effectvmosaicmodule\Debug\effectvmosaicmodule.lib" \
	"..\..\effectvmodules\src\effectvnervousmodule\Debug\effectvnervousmodule.lib" \
	"..\..\effectvmodules\src\effectvnoisemodule\Debug\effectvnoisemodule.lib" \
	"..\..\effectvmodules\src\effectvpupmodule\Debug\effectvpupmodule.lib" \
	"..\..\effectvmodules\src\effectvrdsmodule\Debug\effectvrdsmodule.lib" \
	"..\..\effectvmodules\src\effectvrevmodule\Debug\effectvrevmodule.lib" \
	"..\..\effectvmodules\src\effectvripplemodule\Debug\effectvripplemodule.lib" \
	"..\..\effectvmodules\src\effectvrndmmodule\Debug\effectvrndmmodule.lib" \
	"..\..\effectvmodules\src\effectvscrollmodule\Debug\effectvscrollmodule.lib" \
	"..\..\effectvmodules\src\effectvshagadelicmodule\Debug\effectvshagadelicmodule.lib" \
	"..\..\effectvmodules\src\effectvsimuramodule\Debug\effectvsimuramodule.lib" \
	"..\..\effectvmodules\src\effectvspiralmodule\Debug\effectvspiralmodule.lib" \
	"..\..\effectvmodules\src\effectvstreakmodule\Debug\effectvstreakmodule.lib" \
	"..\..\effectvmodules\src\effectvtransformmodule\Debug\effectvtransformmodule.lib" \
	"..\..\effectvmodules\src\effectvwarholmodule\Debug\effectvwarholmodule.lib" \
	"..\..\effectvmodules\src\effectvwarpmodule\Debug\effectvwarpmodule.lib" \
	"..\..\effectvmodules\src\effectv1dmodule\Debug\effectv1dmodule.lib"

"$(OUTDIR)\dummy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("dummy.dep")
!INCLUDE "dummy.dep"
!ELSE 
!MESSAGE Warning: cannot find "dummy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dummy - Win32 Release" || "$(CFG)" == "dummy - Win32 Debug"
SOURCE=.\main.c

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "dummy - Win32 Release"

"audioaddmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audioaddmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioaddmodule.mak" CFG="audioaddmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audioaddmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioaddmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioaddmodule.mak" CFG="audioaddmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audioaddmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audioaddmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioaddmodule.mak" CFG="audioaddmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audioaddmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioaddmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioaddmodule.mak" CFG="audioaddmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiobdmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiobdmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiobdmodule.mak" CFG="audiobdmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiobdmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiobdmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiobdmodule.mak" CFG="audiobdmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiobdmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiobdmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiobdmodule.mak" CFG="audiobdmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiobdmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiobdmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiobdmodule.mak" CFG="audiobdmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audioenergymodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audioenergymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioenergymodule.mak" CFG="audioenergymodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audioenergymodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioenergymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioenergymodule.mak" CFG="audioenergymodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audioenergymodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audioenergymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioenergymodule.mak" CFG="audioenergymodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audioenergymodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioenergymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioenergymodule.mak" CFG="audioenergymodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audioinmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audioinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioinmodule.mak" CFG="audioinmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audioinmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioinmodule.mak" CFG="audioinmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audioinmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audioinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioinmodule.mak" CFG="audioinmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audioinmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audioinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audioinmodule.mak" CFG="audioinmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiooutmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiooutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiooutmodule.mak" CFG="audiooutmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiooutmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiooutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiooutmodule.mak" CFG="audiooutmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiooutmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiooutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiooutmodule.mak" CFG="audiooutmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiooutmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiooutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiooutmodule.mak" CFG="audiooutmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiospecmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiospecmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiospecmodule.mak" CFG="audiospecmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiospecmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiospecmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiospecmodule.mak" CFG="audiospecmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiospecmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiospecmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiospecmodule.mak" CFG="audiospecmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiospecmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiospecmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiospecmodule.mak" CFG="audiospecmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiosynthmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiosynthmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiosynthmodule.mak" CFG="audiosynthmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiosynthmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiosynthmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiosynthmodule.mak" CFG="audiosynthmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiosynthmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiosynthmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiosynthmodule.mak" CFG="audiosynthmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiosynthmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiosynthmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiosynthmodule.mak" CFG="audiosynthmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiotype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\audiotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiotype.mak" CFG="audiotype - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiotype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\audiotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiotype.mak" CFG="audiotype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiotype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\audiotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiotype.mak" CFG="audiotype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiotype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\audiotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiotype.mak" CFG="audiotype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiovismodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiovismodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiovismodule.mak" CFG="audiovismodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiovismodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiovismodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiovismodule.mak" CFG="audiovismodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiovismodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiovismodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiovismodule.mak" CFG="audiovismodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiovismodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiovismodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiovismodule.mak" CFG="audiovismodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"audiowavegenmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\audiowavegenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiowavegenmodule.mak" CFG="audiowavegenmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"audiowavegenmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiowavegenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiowavegenmodule.mak" CFG="audiowavegenmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"audiowavegenmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\audiowavegenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiowavegenmodule.mak" CFG="audiowavegenmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"audiowavegenmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\audiowavegenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\audiowavegenmodule.mak" CFG="audiowavegenmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"blurmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\blurmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\blurmodule.mak" CFG="blurmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"blurmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\blurmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\blurmodule.mak" CFG="blurmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"blurmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\blurmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\blurmodule.mak" CFG="blurmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"blurmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\blurmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\blurmodule.mak" CFG="blurmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"bwmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\bwmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\bwmodule.mak" CFG="bwmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"bwmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\bwmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\bwmodule.mak" CFG="bwmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"bwmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\bwmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\bwmodule.mak" CFG="bwmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"bwmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\bwmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\bwmodule.mak" CFG="bwmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"capturemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\capturemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\capturemodule.mak" CFG="capturemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"capturemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\capturemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\capturemodule.mak" CFG="capturemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"capturemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\capturemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\capturemodule.mak" CFG="capturemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"capturemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\capturemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\capturemodule.mak" CFG="capturemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"color2numbermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\color2numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\color2numbermodule.mak" CFG="color2numbermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"color2numbermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\color2numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\color2numbermodule.mak" CFG="color2numbermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"color2numbermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\color2numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\color2numbermodule.mak" CFG="color2numbermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"color2numbermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\color2numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\color2numbermodule.mak" CFG="color2numbermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"diffmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\diffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\diffmodule.mak" CFG="diffmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"diffmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\diffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\diffmodule.mak" CFG="diffmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"diffmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\diffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\diffmodule.mak" CFG="diffmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"diffmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\diffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\diffmodule.mak" CFG="diffmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"doepfermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\doepfermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\doepfermodule.mak" CFG="doepfermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"doepfermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\doepfermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\doepfermodule.mak" CFG="doepfermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"doepfermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\doepfermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\doepfermodule.mak" CFG="doepfermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"doepfermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\doepfermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\doepfermodule.mak" CFG="doepfermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvagingmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvagingmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvagingmodule.mak" CFG="effectvagingmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvagingmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvagingmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvagingmodule.mak" CFG="effectvagingmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvagingmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvagingmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvagingmodule.mak" CFG="effectvagingmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvagingmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvagingmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvagingmodule.mak" CFG="effectvagingmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvburnmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvburnmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvburnmodule.mak" CFG="effectvburnmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvburnmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvburnmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvburnmodule.mak" CFG="effectvburnmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvburnmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvburnmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvburnmodule.mak" CFG="effectvburnmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvburnmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvburnmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvburnmodule.mak" CFG="effectvburnmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvcyclemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvcyclemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvcyclemodule.mak" CFG="effectvcyclemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvcyclemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvcyclemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvcyclemodule.mak" CFG="effectvcyclemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvcyclemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvcyclemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvcyclemodule.mak" CFG="effectvcyclemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvcyclemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvcyclemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvcyclemodule.mak" CFG="effectvcyclemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvdotmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdotmodule.mak" CFG="effectvdotmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvdotmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdotmodule.mak" CFG="effectvdotmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvdotmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdotmodule.mak" CFG="effectvdotmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvdotmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdotmodule.mak" CFG="effectvdotmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvedgemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvedgemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvedgemodule.mak" CFG="effectvedgemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvedgemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvedgemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvedgemodule.mak" CFG="effectvedgemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvedgemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvedgemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvedgemodule.mak" CFG="effectvedgemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvedgemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvedgemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvedgemodule.mak" CFG="effectvedgemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvfiremodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvfiremodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvfiremodule.mak" CFG="effectvfiremodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvfiremodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvfiremodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvfiremodule.mak" CFG="effectvfiremodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvfiremodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvfiremodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvfiremodule.mak" CFG="effectvfiremodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvfiremodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvfiremodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvfiremodule.mak" CFG="effectvfiremodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvlensmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlensmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlensmodule.mak" CFG="effectvlensmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvlensmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlensmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlensmodule.mak" CFG="effectvlensmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvlensmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlensmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlensmodule.mak" CFG="effectvlensmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvlensmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlensmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlensmodule.mak" CFG="effectvlensmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvlifemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlifemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlifemodule.mak" CFG="effectvlifemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvlifemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlifemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlifemodule.mak" CFG="effectvlifemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvlifemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlifemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlifemodule.mak" CFG="effectvlifemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvlifemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvlifemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvlifemodule.mak" CFG="effectvlifemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvpuzzlemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpuzzlemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpuzzlemodule.mak" CFG="effectvpuzzlemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvpuzzlemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpuzzlemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpuzzlemodule.mak" CFG="effectvpuzzlemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvpuzzlemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpuzzlemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpuzzlemodule.mak" CFG="effectvpuzzlemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvpuzzlemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpuzzlemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpuzzlemodule.mak" CFG="effectvpuzzlemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvquarkmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvquarkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvquarkmodule.mak" CFG="effectvquarkmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvquarkmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvquarkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvquarkmodule.mak" CFG="effectvquarkmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvquarkmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvquarkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvquarkmodule.mak" CFG="effectvquarkmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvquarkmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvquarkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvquarkmodule.mak" CFG="effectvquarkmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvsparkmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsparkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsparkmodule.mak" CFG="effectvsparkmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvsparkmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsparkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsparkmodule.mak" CFG="effectvsparkmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvsparkmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsparkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsparkmodule.mak" CFG="effectvsparkmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvsparkmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsparkmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsparkmodule.mak" CFG="effectvsparkmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"envtype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\envtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\envtype.mak" CFG="envtype - Win32 Release" 
   cd "..\..\..\build\dummy"

"envtype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\envtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\envtype.mak" CFG="envtype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"envtype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\envtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\envtype.mak" CFG="envtype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"envtype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\envtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\envtype.mak" CFG="envtype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"flashmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\flashmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flashmodule.mak" CFG="flashmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"flashmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\flashmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flashmodule.mak" CFG="flashmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"flashmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\flashmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flashmodule.mak" CFG="flashmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"flashmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\flashmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flashmodule.mak" CFG="flashmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"flipflopmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\flipflopmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flipflopmodule.mak" CFG="flipflopmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"flipflopmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\flipflopmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flipflopmodule.mak" CFG="flipflopmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"flipflopmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\flipflopmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flipflopmodule.mak" CFG="flipflopmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"flipflopmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\flipflopmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\flipflopmodule.mak" CFG="flipflopmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"font3Dmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\font3Dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\font3Dmodule.mak" CFG="font3Dmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"font3Dmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\font3Dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\font3Dmodule.mak" CFG="font3Dmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"font3Dmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\font3Dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\font3Dmodule.mak" CFG="font3Dmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"font3Dmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\font3Dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\font3Dmodule.mak" CFG="font3Dmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"fonttype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\fonttype"
   $(MAKE) /$(MAKEFLAGS) /F ".\fonttype.mak" CFG="fonttype - Win32 Release" 
   cd "..\..\..\build\dummy"

"fonttype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\fonttype"
   $(MAKE) /$(MAKEFLAGS) /F ".\fonttype.mak" CFG="fonttype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"fonttype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\fonttype"
   $(MAKE) /$(MAKEFLAGS) /F ".\fonttype.mak" CFG="fonttype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"fonttype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\fonttype"
   $(MAKE) /$(MAKEFLAGS) /F ".\fonttype.mak" CFG="fonttype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"fpsmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\fpsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\fpsmodule.mak" CFG="fpsmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"fpsmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\fpsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\fpsmodule.mak" CFG="fpsmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"fpsmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\fpsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\fpsmodule.mak" CFG="fpsmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"fpsmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\fpsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\fpsmodule.mak" CFG="fpsmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"framebuffertype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\framebuffertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\framebuffertype.mak" CFG="framebuffertype - Win32 Release" 
   cd "..\..\..\build\dummy"

"framebuffertype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\framebuffertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\framebuffertype.mak" CFG="framebuffertype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"framebuffertype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\framebuffertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\framebuffertype.mak" CFG="framebuffertype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"framebuffertype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\framebuffertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\framebuffertype.mak" CFG="framebuffertype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"frbinmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\frbinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frbinmodule.mak" CFG="frbinmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"frbinmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\frbinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frbinmodule.mak" CFG="frbinmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"frbinmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\frbinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frbinmodule.mak" CFG="frbinmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"frbinmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\frbinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frbinmodule.mak" CFG="frbinmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"frboutmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\frboutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frboutmodule.mak" CFG="frboutmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"frboutmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\frboutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frboutmodule.mak" CFG="frboutmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"frboutmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\frboutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frboutmodule.mak" CFG="frboutmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"frboutmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\frboutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\frboutmodule.mak" CFG="frboutmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"funparsemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\funparsemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\funparsemodule.mak" CFG="funparsemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"funparsemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\funparsemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\funparsemodule.mak" CFG="funparsemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"funparsemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\funparsemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\funparsemodule.mak" CFG="funparsemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"funparsemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\funparsemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\funparsemodule.mak" CFG="funparsemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"gradnormmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\gradnormmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\gradnormmodule.mak" CFG="gradnormmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"gradnormmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\gradnormmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\gradnormmodule.mak" CFG="gradnormmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"gradnormmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\gradnormmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\gradnormmodule.mak" CFG="gradnormmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"gradnormmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\gradnormmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\gradnormmodule.mak" CFG="gradnormmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"ifsgenmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\ifsgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsgenmodule.mak" CFG="ifsgenmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"ifsgenmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsgenmodule.mak" CFG="ifsgenmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"ifsgenmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\ifsgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsgenmodule.mak" CFG="ifsgenmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"ifsgenmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsgenmodule.mak" CFG="ifsgenmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"ifsmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\ifsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsmodule.mak" CFG="ifsmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"ifsmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsmodule.mak" CFG="ifsmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"ifsmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\ifsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsmodule.mak" CFG="ifsmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"ifsmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsmodule.mak" CFG="ifsmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"ifstype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\ifstype"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifstype.mak" CFG="ifstype - Win32 Release" 
   cd "..\..\..\build\dummy"

"ifstype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\ifstype"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifstype.mak" CFG="ifstype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"ifstype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\ifstype"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifstype.mak" CFG="ifstype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"ifstype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\ifstype"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifstype.mak" CFG="ifstype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"ifsxfadermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\ifsxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsxfadermodule.mak" CFG="ifsxfadermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"ifsxfadermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsxfadermodule.mak" CFG="ifsxfadermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"ifsxfadermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\ifsxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsxfadermodule.mak" CFG="ifsxfadermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"ifsxfadermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ifsxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ifsxfadermodule.mak" CFG="ifsxfadermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"imagebuffermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\imagebuffermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imagebuffermodule.mak" CFG="imagebuffermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"imagebuffermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\imagebuffermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imagebuffermodule.mak" CFG="imagebuffermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"imagebuffermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\imagebuffermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imagebuffermodule.mak" CFG="imagebuffermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"imagebuffermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\imagebuffermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imagebuffermodule.mak" CFG="imagebuffermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"imgarithmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\imgarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imgarithmodule.mak" CFG="imgarithmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"imgarithmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\imgarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imgarithmodule.mak" CFG="imgarithmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"imgarithmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\imgarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imgarithmodule.mak" CFG="imgarithmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"imgarithmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\imgarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\imgarithmodule.mak" CFG="imgarithmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"isingnoizemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\isingnoizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\isingnoizemodule.mak" CFG="isingnoizemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"isingnoizemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\isingnoizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\isingnoizemodule.mak" CFG="isingnoizemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"isingnoizemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\isingnoizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\isingnoizemodule.mak" CFG="isingnoizemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"isingnoizemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\isingnoizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\isingnoizemodule.mak" CFG="isingnoizemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"joystickmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\joystickmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\joystickmodule.mak" CFG="joystickmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"joystickmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\joystickmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\joystickmodule.mak" CFG="joystickmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"joystickmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\joystickmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\joystickmodule.mak" CFG="joystickmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"joystickmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\joystickmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\joystickmodule.mak" CFG="joystickmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"jumpmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\jumpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\jumpmodule.mak" CFG="jumpmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"jumpmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\jumpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\jumpmodule.mak" CFG="jumpmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"jumpmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\jumpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\jumpmodule.mak" CFG="jumpmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"jumpmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\jumpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\jumpmodule.mak" CFG="jumpmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"lfotype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\lfotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\lfotype.mak" CFG="lfotype - Win32 Release" 
   cd "..\..\..\build\dummy"

"lfotype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\lfotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\lfotype.mak" CFG="lfotype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"lfotype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\lfotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\lfotype.mak" CFG="lfotype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"lfotype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\lfotype"
   $(MAKE) /$(MAKEFLAGS) /F ".\lfotype.mak" CFG="lfotype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"midiinmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\midiinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\midiinmodule.mak" CFG="midiinmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"midiinmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\midiinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\midiinmodule.mak" CFG="midiinmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"midiinmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\midiinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\midiinmodule.mak" CFG="midiinmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"midiinmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\midiinmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\midiinmodule.mak" CFG="midiinmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"miditype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\miditype"
   $(MAKE) /$(MAKEFLAGS) /F ".\miditype.mak" CFG="miditype - Win32 Release" 
   cd "..\..\..\build\dummy"

"miditype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\miditype"
   $(MAKE) /$(MAKEFLAGS) /F ".\miditype.mak" CFG="miditype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"miditype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\miditype"
   $(MAKE) /$(MAKEFLAGS) /F ".\miditype.mak" CFG="miditype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"miditype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\miditype"
   $(MAKE) /$(MAKEFLAGS) /F ".\miditype.mak" CFG="miditype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"netcontrolmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\netcontrolmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\netcontrolmodule.mak" CFG="netcontrolmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"netcontrolmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\netcontrolmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\netcontrolmodule.mak" CFG="netcontrolmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"netcontrolmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\netcontrolmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\netcontrolmodule.mak" CFG="netcontrolmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"netcontrolmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\netcontrolmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\netcontrolmodule.mak" CFG="netcontrolmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numarithmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numarithmodule.mak" CFG="numarithmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numarithmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numarithmodule.mak" CFG="numarithmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numarithmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numarithmodule.mak" CFG="numarithmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numarithmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numarithmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numarithmodule.mak" CFG="numarithmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"number2colormodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\number2colormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\number2colormodule.mak" CFG="number2colormodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"number2colormodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\number2colormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\number2colormodule.mak" CFG="number2colormodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"number2colormodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\number2colormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\number2colormodule.mak" CFG="number2colormodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"number2colormodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\number2colormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\number2colormodule.mak" CFG="number2colormodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numbermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbermodule.mak" CFG="numbermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numbermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbermodule.mak" CFG="numbermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numbermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbermodule.mak" CFG="numbermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numbermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numbermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbermodule.mak" CFG="numbermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numbertype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\numbertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbertype.mak" CFG="numbertype - Win32 Release" 
   cd "..\..\..\build\dummy"

"numbertype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\numbertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbertype.mak" CFG="numbertype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numbertype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\numbertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbertype.mak" CFG="numbertype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numbertype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\numbertype"
   $(MAKE) /$(MAKEFLAGS) /F ".\numbertype.mak" CFG="numbertype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numenvmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numenvmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numenvmodule.mak" CFG="numenvmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numenvmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numenvmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numenvmodule.mak" CFG="numenvmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numenvmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numenvmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numenvmodule.mak" CFG="numenvmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numenvmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numenvmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numenvmodule.mak" CFG="numenvmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numlfomodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numlfomodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numlfomodule.mak" CFG="numlfomodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numlfomodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numlfomodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numlfomodule.mak" CFG="numlfomodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numlfomodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numlfomodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numlfomodule.mak" CFG="numlfomodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numlfomodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numlfomodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numlfomodule.mak" CFG="numlfomodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numposmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numposmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numposmodule.mak" CFG="numposmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numposmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numposmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numposmodule.mak" CFG="numposmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numposmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numposmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numposmodule.mak" CFG="numposmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numposmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numposmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numposmodule.mak" CFG="numposmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"numxfadermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\numxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numxfadermodule.mak" CFG="numxfadermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"numxfadermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numxfadermodule.mak" CFG="numxfadermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"numxfadermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\numxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numxfadermodule.mak" CFG="numxfadermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"numxfadermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\numxfadermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\numxfadermodule.mak" CFG="numxfadermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"overlaymodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\overlaymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\overlaymodule.mak" CFG="overlaymodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"overlaymodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\overlaymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\overlaymodule.mak" CFG="overlaymodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"overlaymodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\overlaymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\overlaymodule.mak" CFG="overlaymodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"overlaymodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\overlaymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\overlaymodule.mak" CFG="overlaymodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"pixelizemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\pixelizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pixelizemodule.mak" CFG="pixelizemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"pixelizemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\pixelizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pixelizemodule.mak" CFG="pixelizemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"pixelizemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\pixelizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pixelizemodule.mak" CFG="pixelizemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"pixelizemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\pixelizemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pixelizemodule.mak" CFG="pixelizemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"planemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\planemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\planemodule.mak" CFG="planemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"planemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\planemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\planemodule.mak" CFG="planemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"planemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\planemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\planemodule.mak" CFG="planemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"planemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\planemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\planemodule.mak" CFG="planemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"plasmamodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\plasmamodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\plasmamodule.mak" CFG="plasmamodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"plasmamodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\plasmamodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\plasmamodule.mak" CFG="plasmamodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"plasmamodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\plasmamodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\plasmamodule.mak" CFG="plasmamodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"plasmamodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\plasmamodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\plasmamodule.mak" CFG="plasmamodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"positiontype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\positiontype"
   $(MAKE) /$(MAKEFLAGS) /F ".\positiontype.mak" CFG="positiontype - Win32 Release" 
   cd "..\..\..\build\dummy"

"positiontype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\positiontype"
   $(MAKE) /$(MAKEFLAGS) /F ".\positiontype.mak" CFG="positiontype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"positiontype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\positiontype"
   $(MAKE) /$(MAKEFLAGS) /F ".\positiontype.mak" CFG="positiontype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"positiontype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\positiontype"
   $(MAKE) /$(MAKEFLAGS) /F ".\positiontype.mak" CFG="positiontype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"posnummodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\posnummodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\posnummodule.mak" CFG="posnummodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"posnummodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\posnummodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\posnummodule.mak" CFG="posnummodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"posnummodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\posnummodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\posnummodule.mak" CFG="posnummodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"posnummodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\posnummodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\posnummodule.mak" CFG="posnummodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"rangeconvertmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\rangeconvertmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rangeconvertmodule.mak" CFG="rangeconvertmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"rangeconvertmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\rangeconvertmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rangeconvertmodule.mak" CFG="rangeconvertmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"rangeconvertmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\rangeconvertmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rangeconvertmodule.mak" CFG="rangeconvertmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"rangeconvertmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\rangeconvertmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rangeconvertmodule.mak" CFG="rangeconvertmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"resultmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\resultmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\resultmodule.mak" CFG="resultmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"resultmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\resultmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\resultmodule.mak" CFG="resultmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"resultmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\resultmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\resultmodule.mak" CFG="resultmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"resultmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\resultmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\resultmodule.mak" CFG="resultmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"rgbtype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\rgbtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\rgbtype.mak" CFG="rgbtype - Win32 Release" 
   cd "..\..\..\build\dummy"

"rgbtype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\rgbtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\rgbtype.mak" CFG="rgbtype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"rgbtype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\rgbtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\rgbtype.mak" CFG="rgbtype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"rgbtype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\rgbtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\rgbtype.mak" CFG="rgbtype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"rotozoommodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\rotozoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rotozoommodule.mak" CFG="rotozoommodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"rotozoommodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\rotozoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rotozoommodule.mak" CFG="rotozoommodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"rotozoommodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\rotozoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rotozoommodule.mak" CFG="rotozoommodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"rotozoommodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\rotozoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\rotozoommodule.mak" CFG="rotozoommodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"sdlfontmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\sdlfontmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\sdlfontmodule.mak" CFG="sdlfontmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"sdlfontmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\sdlfontmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\sdlfontmodule.mak" CFG="sdlfontmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"sdlfontmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\sdlfontmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\sdlfontmodule.mak" CFG="sdlfontmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"sdlfontmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\sdlfontmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\sdlfontmodule.mak" CFG="sdlfontmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"signalgenmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\signalgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalgenmodule.mak" CFG="signalgenmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"signalgenmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\signalgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalgenmodule.mak" CFG="signalgenmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"signalgenmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\signalgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalgenmodule.mak" CFG="signalgenmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"signalgenmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\signalgenmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalgenmodule.mak" CFG="signalgenmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"staticcolormodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\staticcolormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\staticcolormodule.mak" CFG="staticcolormodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"staticcolormodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\staticcolormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\staticcolormodule.mak" CFG="staticcolormodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"staticcolormodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\staticcolormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\staticcolormodule.mak" CFG="staticcolormodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"staticcolormodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\staticcolormodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\staticcolormodule.mak" CFG="staticcolormodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"stringtokenizermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\stringtokenizermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtokenizermodule.mak" CFG="stringtokenizermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"stringtokenizermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\stringtokenizermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtokenizermodule.mak" CFG="stringtokenizermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"stringtokenizermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\stringtokenizermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtokenizermodule.mak" CFG="stringtokenizermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"stringtokenizermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\stringtokenizermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtokenizermodule.mak" CFG="stringtokenizermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"stringtype - Win32 Release" : 
   cd "\code\gephex-0.4\types\src\stringtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtype.mak" CFG="stringtype - Win32 Release" 
   cd "..\..\..\build\dummy"

"stringtype - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\types\src\stringtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtype.mak" CFG="stringtype - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"stringtype - Win32 Debug" : 
   cd "\code\gephex-0.4\types\src\stringtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtype.mak" CFG="stringtype - Win32 Debug" 
   cd "..\..\..\build\dummy"

"stringtype - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\types\src\stringtype"
   $(MAKE) /$(MAKEFLAGS) /F ".\stringtype.mak" CFG="stringtype - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"tunnelmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\tunnelmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\tunnelmodule.mak" CFG="tunnelmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"tunnelmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\tunnelmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\tunnelmodule.mak" CFG="tunnelmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"tunnelmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\tunnelmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\tunnelmodule.mak" CFG="tunnelmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"tunnelmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\tunnelmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\tunnelmodule.mak" CFG="tunnelmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"twolayermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\twolayermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\twolayermodule.mak" CFG="twolayermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"twolayermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\twolayermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\twolayermodule.mak" CFG="twolayermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"twolayermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\twolayermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\twolayermodule.mak" CFG="twolayermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"twolayermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\twolayermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\twolayermodule.mak" CFG="twolayermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"xfademodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\xfademodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\xfademodule.mak" CFG="xfademodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"xfademodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\xfademodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\xfademodule.mak" CFG="xfademodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"xfademodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\xfademodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\xfademodule.mak" CFG="xfademodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"xfademodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\xfademodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\xfademodule.mak" CFG="xfademodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"dplmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\dplmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\dplmodule.mak" CFG="dplmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"dplmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\dplmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\dplmodule.mak" CFG="dplmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"dplmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\dplmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\dplmodule.mak" CFG="dplmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"dplmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\dplmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\dplmodule.mak" CFG="dplmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"chromakeymodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\chromakeymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\chromakeymodule.mak" CFG="chromakeymodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"chromakeymodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\chromakeymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\chromakeymodule.mak" CFG="chromakeymodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"chromakeymodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\chromakeymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\chromakeymodule.mak" CFG="chromakeymodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"chromakeymodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\chromakeymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\chromakeymodule.mak" CFG="chromakeymodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"noisemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\noisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\noisemodule.mak" CFG="noisemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"noisemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\noisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\noisemodule.mak" CFG="noisemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"noisemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\noisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\noisemodule.mak" CFG="noisemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"noisemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\noisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\noisemodule.mak" CFG="noisemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"y4minmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\y4minmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4minmodule.mak" CFG="y4minmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"y4minmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\y4minmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4minmodule.mak" CFG="y4minmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"y4minmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\y4minmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4minmodule.mak" CFG="y4minmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"y4minmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\y4minmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4minmodule.mak" CFG="y4minmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"y4moutputmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\yuv4mpeg2module"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4moutputmodule.mak" CFG="y4moutputmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"y4moutputmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\yuv4mpeg2module"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4moutputmodule.mak" CFG="y4moutputmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"y4moutputmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\yuv4mpeg2module"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4moutputmodule.mak" CFG="y4moutputmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"y4moutputmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\yuv4mpeg2module"
   $(MAKE) /$(MAKEFLAGS) /F ".\y4moutputmodule.mak" CFG="y4moutputmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"ffmpegoutmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\ffmpegoutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ffmpegoutmodule.mak" CFG="ffmpegoutmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"ffmpegoutmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ffmpegoutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ffmpegoutmodule.mak" CFG="ffmpegoutmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"ffmpegoutmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\ffmpegoutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ffmpegoutmodule.mak" CFG="ffmpegoutmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"ffmpegoutmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\ffmpegoutmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\ffmpegoutmodule.mak" CFG="ffmpegoutmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"pongmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\pongmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pongmodule.mak" CFG="pongmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"pongmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\pongmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pongmodule.mak" CFG="pongmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"pongmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\pongmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pongmodule.mak" CFG="pongmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"pongmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\pongmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\pongmodule.mak" CFG="pongmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"signalplotmodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\signalplotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalplotmodule.mak" CFG="signalplotmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"signalplotmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\signalplotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalplotmodule.mak" CFG="signalplotmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"signalplotmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\signalplotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalplotmodule.mak" CFG="signalplotmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"signalplotmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\signalplotmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\signalplotmodule.mak" CFG="signalplotmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"centermodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\centermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\centermodule.mak" CFG="centermodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"centermodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\centermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\centermodule.mak" CFG="centermodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"centermodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\centermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\centermodule.mak" CFG="centermodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"centermodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\centermodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\centermodule.mak" CFG="centermodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"timesourcemodule - Win32 Release" : 
   cd "\code\gephex-0.4\modules\src\timesourcemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\timesourcemodule.mak" CFG="timesourcemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"timesourcemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\modules\src\timesourcemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\timesourcemodule.mak" CFG="timesourcemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"timesourcemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\modules\src\timesourcemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\timesourcemodule.mak" CFG="timesourcemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"timesourcemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\modules\src\timesourcemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\timesourcemodule.mak" CFG="timesourcemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvbaltanmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvbaltanmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvbaltanmodule.mak" CFG="effectvbaltanmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvbaltanmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvbaltanmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvbaltanmodule.mak" CFG="effectvbaltanmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvbaltanmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvbaltanmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvbaltanmodule.mak" CFG="effectvbaltanmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvbaltanmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvbaltanmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvbaltanmodule.mak" CFG="effectvbaltanmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvblurzoommodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvblurzoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvblurzoommodule.mak" CFG="effectvblurzoommodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvblurzoommodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvblurzoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvblurzoommodule.mak" CFG="effectvblurzoommodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvblurzoommodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvblurzoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvblurzoommodule.mak" CFG="effectvblurzoommodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvblurzoommodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvblurzoommodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvblurzoommodule.mak" CFG="effectvblurzoommodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvchameleonmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvchameleonmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvchameleonmodule.mak" CFG="effectvchameleonmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvchameleonmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvchameleonmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvchameleonmodule.mak" CFG="effectvchameleonmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvchameleonmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvchameleonmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvchameleonmodule.mak" CFG="effectvchameleonmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvchameleonmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvchameleonmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvchameleonmodule.mak" CFG="effectvchameleonmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvdicemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdicemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdicemodule.mak" CFG="effectvdicemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvdicemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdicemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdicemodule.mak" CFG="effectvdicemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvdicemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdicemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdicemodule.mak" CFG="effectvdicemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvdicemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdicemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdicemodule.mak" CFG="effectvdicemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvdiffmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdiffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdiffmodule.mak" CFG="effectvdiffmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvdiffmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdiffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdiffmodule.mak" CFG="effectvdiffmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvdiffmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdiffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdiffmodule.mak" CFG="effectvdiffmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvdiffmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdiffmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdiffmodule.mak" CFG="effectvdiffmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvdizzymodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdizzymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdizzymodule.mak" CFG="effectvdizzymodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvdizzymodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdizzymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdizzymodule.mak" CFG="effectvdizzymodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvdizzymodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdizzymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdizzymodule.mak" CFG="effectvdizzymodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvdizzymodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvdizzymodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvdizzymodule.mak" CFG="effectvdizzymodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvmatrixmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmatrixmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmatrixmodule.mak" CFG="effectvmatrixmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvmatrixmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmatrixmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmatrixmodule.mak" CFG="effectvmatrixmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvmatrixmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmatrixmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmatrixmodule.mak" CFG="effectvmatrixmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvmatrixmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmatrixmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmatrixmodule.mak" CFG="effectvmatrixmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvmosaicmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmosaicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmosaicmodule.mak" CFG="effectvmosaicmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvmosaicmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmosaicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmosaicmodule.mak" CFG="effectvmosaicmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvmosaicmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmosaicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmosaicmodule.mak" CFG="effectvmosaicmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvmosaicmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvmosaicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvmosaicmodule.mak" CFG="effectvmosaicmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvnervousmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnervousmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnervousmodule.mak" CFG="effectvnervousmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvnervousmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnervousmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnervousmodule.mak" CFG="effectvnervousmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvnervousmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnervousmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnervousmodule.mak" CFG="effectvnervousmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvnervousmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnervousmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnervousmodule.mak" CFG="effectvnervousmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvnoisemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnoisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnoisemodule.mak" CFG="effectvnoisemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvnoisemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnoisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnoisemodule.mak" CFG="effectvnoisemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvnoisemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnoisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnoisemodule.mak" CFG="effectvnoisemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvnoisemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvnoisemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvnoisemodule.mak" CFG="effectvnoisemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvpupmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpupmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpupmodule.mak" CFG="effectvpupmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvpupmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpupmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpupmodule.mak" CFG="effectvpupmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvpupmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpupmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpupmodule.mak" CFG="effectvpupmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvpupmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvpupmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvpupmodule.mak" CFG="effectvpupmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvrdsmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrdsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrdsmodule.mak" CFG="effectvrdsmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvrdsmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrdsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrdsmodule.mak" CFG="effectvrdsmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvrdsmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrdsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrdsmodule.mak" CFG="effectvrdsmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvrdsmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrdsmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrdsmodule.mak" CFG="effectvrdsmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvrevmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrevmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrevmodule.mak" CFG="effectvrevmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvrevmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrevmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrevmodule.mak" CFG="effectvrevmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvrevmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrevmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrevmodule.mak" CFG="effectvrevmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvrevmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrevmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrevmodule.mak" CFG="effectvrevmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvripplemodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvripplemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvripplemodule.mak" CFG="effectvripplemodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvripplemodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvripplemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvripplemodule.mak" CFG="effectvripplemodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvripplemodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvripplemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvripplemodule.mak" CFG="effectvripplemodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvripplemodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvripplemodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvripplemodule.mak" CFG="effectvripplemodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvrndmmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrndmmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrndmmodule.mak" CFG="effectvrndmmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvrndmmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrndmmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrndmmodule.mak" CFG="effectvrndmmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvrndmmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrndmmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrndmmodule.mak" CFG="effectvrndmmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvrndmmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvrndmmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvrndmmodule.mak" CFG="effectvrndmmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvscrollmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvscrollmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvscrollmodule.mak" CFG="effectvscrollmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvscrollmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvscrollmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvscrollmodule.mak" CFG="effectvscrollmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvscrollmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvscrollmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvscrollmodule.mak" CFG="effectvscrollmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvscrollmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvscrollmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvscrollmodule.mak" CFG="effectvscrollmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvshagadelicmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvshagadelicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvshagadelicmodule.mak" CFG="effectvshagadelicmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvshagadelicmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvshagadelicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvshagadelicmodule.mak" CFG="effectvshagadelicmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvshagadelicmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvshagadelicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvshagadelicmodule.mak" CFG="effectvshagadelicmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvshagadelicmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvshagadelicmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvshagadelicmodule.mak" CFG="effectvshagadelicmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvsimuramodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsimuramodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsimuramodule.mak" CFG="effectvsimuramodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvsimuramodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsimuramodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsimuramodule.mak" CFG="effectvsimuramodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvsimuramodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsimuramodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsimuramodule.mak" CFG="effectvsimuramodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvsimuramodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvsimuramodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvsimuramodule.mak" CFG="effectvsimuramodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvspiralmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvspiralmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvspiralmodule.mak" CFG="effectvspiralmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvspiralmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvspiralmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvspiralmodule.mak" CFG="effectvspiralmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvspiralmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvspiralmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvspiralmodule.mak" CFG="effectvspiralmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvspiralmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvspiralmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvspiralmodule.mak" CFG="effectvspiralmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvstreakmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvstreakmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvstreakmodule.mak" CFG="effectvstreakmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvstreakmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvstreakmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvstreakmodule.mak" CFG="effectvstreakmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvstreakmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvstreakmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvstreakmodule.mak" CFG="effectvstreakmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvstreakmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvstreakmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvstreakmodule.mak" CFG="effectvstreakmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvtransformmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvtransformmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvtransformmodule.mak" CFG="effectvtransformmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvtransformmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvtransformmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvtransformmodule.mak" CFG="effectvtransformmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvtransformmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvtransformmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvtransformmodule.mak" CFG="effectvtransformmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvtransformmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvtransformmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvtransformmodule.mak" CFG="effectvtransformmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvwarholmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarholmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarholmodule.mak" CFG="effectvwarholmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvwarholmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarholmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarholmodule.mak" CFG="effectvwarholmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvwarholmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarholmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarholmodule.mak" CFG="effectvwarholmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvwarholmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarholmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarholmodule.mak" CFG="effectvwarholmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectvwarpmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarpmodule.mak" CFG="effectvwarpmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectvwarpmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarpmodule.mak" CFG="effectvwarpmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectvwarpmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarpmodule.mak" CFG="effectvwarpmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectvwarpmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectvwarpmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectvwarpmodule.mak" CFG="effectvwarpmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 

!IF  "$(CFG)" == "dummy - Win32 Release"

"effectv1dmodule - Win32 Release" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectv1dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectv1dmodule.mak" CFG="effectv1dmodule - Win32 Release" 
   cd "..\..\..\build\dummy"

"effectv1dmodule - Win32 ReleaseCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectv1dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectv1dmodule.mak" CFG="effectv1dmodule - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ELSEIF  "$(CFG)" == "dummy - Win32 Debug"

"effectv1dmodule - Win32 Debug" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectv1dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectv1dmodule.mak" CFG="effectv1dmodule - Win32 Debug" 
   cd "..\..\..\build\dummy"

"effectv1dmodule - Win32 DebugCLEAN" : 
   cd "\code\gephex-0.4\effectvmodules\src\effectv1dmodule"
   $(MAKE) /$(MAKEFLAGS) /F ".\effectv1dmodule.mak" CFG="effectv1dmodule - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\build\dummy"

!ENDIF 


!ENDIF 

