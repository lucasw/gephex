libdir = @libdir@/gephex/modules

if EFFECTV
EFFECTV_DIRS = \
	libeffectv \
	effecttvedgemodule \
	effectvfiremodule \
	effectvlensmodule \
	effectvpuzzlemodule \
	effectvlifemodule \
	effectvagingmodule \
	effectvburnmodule \
	effectvdotmodule \
	effectvsparkmodule \
	effectvcyclemodule \
	effectvquarkmodule
endif

if HAVE_SDL
SDL_DIRS = joystickmodule

if HAVE_SDL_TTF
SDL_TTF_DIRS = sdlfontmodule
endif

endif

if HAVE_PNG
PNG_DIRS = imagewritermodule
endif

if HAVE_ASOUNDLIB_OR_OSS
AUDIO_DIRS = audiooutmodule audioinmodule
endif

if HAVE_OSS
OSS_DIRS = midiinmodule
endif

if WITH_V4L
V4L_DIRS = v4lmodule
endif


SUBDIRS = libgrid \
	libmidi \
	libscale \
	numarithmodule \
        audioaddmodule \
        audiospecmodule \
        audioenergymodule \
        audiowavegenmodule \
        audiovismodule \
        audiobdmodule \
	audiosynthmodule \
	bwmodule \
	resultmodule \
	numbermodule \
	numenvmodule \
	numlfomodule \
	xfademodule \
	plasma \
	rotozoommodule \
	imagebuffermodule \
	blurmodule \
	tunnelmodule \
	planemodule \
	signalgenmodules \
	staticcolormodule \
	functions \
	numposmodule \
	posnummodule \
	flashmodule \
        imgarithmodule \
	ifsgenmodule \
	ifsxfadermodule \
	netcontrolmodule \
	doepfermodule \
	fpsmodule \
	ifsmodule \
	isingnoizemodule \
	flipflopmodule \
	diffmodule \
	number2color \
	overlaymodule \
	color2number \
	gradnormmodule \
	twolayermodule \
	rangeconvertmodule \
        frboutmodule \
	frbinmodule \
	stringtokenizermodule \
        pixelizemodule $(EFFECTV_DIRS) $(SDL_DIRS) $(SDL_TTF_DIRS) $(V4L_DIRS) $(PNG_DIRS) $(AUDIO_DIRS) $(OSS_DIRS)




