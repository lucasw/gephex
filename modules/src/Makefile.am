libdir = @libdir@/gephex/modules

if EFFECTV
EFFECTV_DIRS = \
	libeffectv \
	effecttvedgemodule \
	effectvagingmodule \
	effectvburnmodule \
	effectvcyclemodule \
	effectvdotmodule \
	effectvfiremodule \
	effectvlensmodule \
	effectvlifemodule \
	effectvpuzzlemodule \
	effectvquarkmodule \
	effectvsparkmodule 
endif

if HAVE_SDL

if HAVE_SDL_TTF
SDL_TTF_DIRS = sdlfontmodule
endif

endif

if HAVE_JOYSTICK
JOYSTICK_DIRS = joystickmodule
endif

if HAVE_PNG
PNG_DIRS = imagewritermodule
endif

if HAVE_ASOUNDLIB_OR_OSS
AUDIO_DIRS = audioinmodule audiooutmodule
endif

if HAVE_OSS
OSS_DIRS = midiinmodule
endif

if HAVE_V4L
V4L_DIRS = v4lmodule
endif


SUBDIRS = libgrid \
	libmidi \
	libscale \
	audioaddmodule \
	audiobdmodule \
	audioenergymodule \
	audiospecmodule \
	audiosynthmodule \
	audiovismodule \
	audiowavegenmodule \
	blurmodule \
	bwmodule \
	color2number \
	diffmodule \
	doepfermodule \
	flashmodule \
	flipflopmodule \
	fpsmodule \
	frbinmodule \
	frboutmodule \
	functions \
	gradnormmodule \
	ifsgenmodule \
	ifsmodule \
	ifsxfadermodule \
	imagebuffermodule \
	imgarithmodule \
	isingnoizemodule \
	netcontrolmodule \
	numarithmodule \
	number2color \
	numbermodule \
	numenvmodule \
	numlfomodule \
	numposmodule \
	overlaymodule \
	pixelizemodule \
	planemodule \
	plasma \
	posnummodule \
	rangeconvertmodule \
	resultmodule \
	rotozoommodule \
	signalgenmodules \
	staticcolormodule \
	stringtokenizermodule \
	tunnelmodule \
	twolayermodule \
	xfademodule $(EFFECTV_DIRS) $(JOYSTICK_DIRS) $(SDL_TTF_DIRS) $(V4L_DIRS) $(PNG_DIRS) $(AUDIO_DIRS) $(OSS_DIRS)




