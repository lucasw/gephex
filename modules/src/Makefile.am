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

if WITH_ASOUNDLIB_OR_OSS
AUDIO_DIRS = audioinmodule audiooutmodule midiinmodule
endif

if WITH_V4L
V4L_DIRS = capturemodule
endif

if WITH_FFMPEG
FFMPEG_DIRS = ffmpegoutmodule
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
	netcontrolmodule \
	noisemodule \
	numarithmodule \
	number2colormodule \
	numbermodule \
	numenvmodule \
	numlfomodule \
	numposmodule \
	numxfadermodule \
	oscinmodule \
	oscoutmodule \
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
	xfademodule \
	y4minmodule \
	yuv4mpeg2module	$(JOYSTICK_DIRS) $(SDL_TTF_DIRS) $(V4L_DIRS) $(PNG_DIRS) $(AUDIO_DIRS) $(FFMPEG_DIRS)
