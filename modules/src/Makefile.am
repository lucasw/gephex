libdir = @gphx_module_lib_dir@

if WITH_SDL

if WITH_SDL_TTF
SDL_TTF_DIRS = sdlfontmodule
endif

endif

if WITH_JOYSTICK
JOYSTICK_DIRS = joystickmodule
endif

if WITH_LIBPNG
PNG_DIRS = imagewritermodule
endif

if WITH_ANY_AUDIO_SUPPORT
AUDIO_DIRS = audioinmodule audiooutmodule midiinmodule
endif

if WITH_V4L
V4L_DIRS = capturemodule
endif

if WITH_FFMPEG
FFMPEG_DIRS = ffmpegoutmodule
endif

if OS_WINDOWS
  PLT_DRS =
else
  PLT_DRS = oscinmodule \
            oscoutmodule \
            y4minmodule \
            yuv4mpeg2module
endif

SUBDIRS = libgrid \
	libmidi \
	libscale \
	libdshow \
	libcolorconv \
	audioaddmodule \
	audiobdmodule \
	audioenergymodule \
	audiospecmodule \
	audiosynthmodule \
	audiovismodule \
	audiowavegenmodule \
	blurmodule \
	bwmodule \
	centermodule \
	chromakeymodule \
	color2numbermodule \
	colorizemodule \
	diffmodule \
	doepfermodule \
        dplmodule \
	flashmodule \
	flipflopmodule \
	font3Dmodule \
	fpsmodule \
	frbinmodule \
	frboutmodule \
	funparsemodule \
	gradnormmodule \
	ifsgenmodule \
	ifsmodule \
	ifsxfadermodule \
	imagebuffermodule \
	imgarithmodule \
	isingnoizemodule \
	jumpmodule \
	midiccdecmodule \
	midinotedecmodule \
	midikeyrangedecmodule \
	midiprgchdecmodule \
	midipitchwdecmodule \
	mirrormodule \
	netcontrolmodule \
	noisemodule \
	numarithmodule \
	number2colormodule \
	numbermodule \
	numenvmodule \
	numlfomodule \
	numposmodule \
	numxfadermodule \
	oscnummodule \
	numoscmodule \
	oscmergemodule \
	overlaymodule \
	pixelizemodule \
	planemodule \
	plasmamodule \
	pongmodule \
	posnummodule \
	rangeconvertmodule \
	resultmodule \
	rotozoommodule \
	signalgenmodule \
	signalplotmodule \
	staticcolormodule \
	stringtokenizermodule \
	timesourcemodule \
	tunnelmodule \
	twolayermodule \
	xfademodule $(PLT_DRS) $(JOYSTICK_DIRS) $(SDL_TTF_DIRS) $(V4L_DIRS) $(PNG_DIRS) $(AUDIO_DIRS) $(FFMPEG_DIRS)

EXTRA_DIST = modules.sln
