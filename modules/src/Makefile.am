libdir = @libdir@/gephex/modules

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

SUBDIRS = libgrid \
	libmidi \
	libscale \
	libdshow \
	audioaddmodule \
	audiobdmodule \
	audioenergymodule \
	audiospecmodule \
	audiosynthmodule \
	audiovismodule \
	audiowavegenmodule \
	blurmodule \
	bwmodule \
	color2numbermodule \
	diffmodule \
	doepfermodule \
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
	netcontrolmodule \
	numarithmodule \
	number2colormodule \
	numbermodule \
	numenvmodule \
	numlfomodule \
	numposmodule \
	numxfadermodule \
	overlaymodule \
	pixelizemodule \
	planemodule \
	plasmamodule \
	posnummodule \
	rangeconvertmodule \
	resultmodule \
	rotozoommodule \
	signalgenmodule \
	staticcolormodule \
	stringtokenizermodule \
	tunnelmodule \
	twolayermodule \
	xfademodule $(JOYSTICK_DIRS) $(SDL_TTF_DIRS) $(V4L_DIRS) $(PNG_DIRS) $(AUDIO_DIRS)

