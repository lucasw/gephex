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
	effectvburnmodule
endif

if HAVE_SDL
SDL_DIRS = \
	sdloutputmodule \
	joystickmodule
endif

if HAVE_AVIFILE
AVIFILE_DIRS = avifilemodule
endif

if HAVE_MPEG3
# commented out for the release (does not work on all tested computers)
MPEG3_DIRS = #libmpeg3module
endif

if HAVE_GLX
GLX_DIRS = gloutmodule
endif

if HAVE_PNG
PNG_DIRS = imagewritermodule
endif

if WITH_V4L
V4L_DIRS = v4lmodule
endif

SUBDIRS = libgrid \
	libmidi \
	addmodule \
	bwmodule \
	submodule \
	resultmodule \
	numbermodule \
	xfademodule \
	plasma \
	bmpmodule \
	rotozoommodule \
	imagebuffermodule \
	invertmodule \
	blurmodule \
	tunnelmodule \
	planemodule \
	signalgenmodules \
	imgsubmodule \
	staticcolormodule \
	functions \
	numposmodule \
	posnummodule \
	flashmodule \
	ifsgenmodule \
	ifsxfadermodule \
	netcontrolmodule \
	midiinmodule \
	doepfermodule \
	fpsmodule \
	ifsmodule \
	isingnoizemodule \
	flipflopmodule \
	diffmodule \
	number2color \
	overlaymodule \
	color2number \
	rangeconvertmodule \
        x11outmodule $(EFFECTV_DIRS) $(SDL_DIRS) $(AVIFILE_DIRS) $(MPEG3_DIRS) $(GLX_DIRS) $(V4L_DIRS) $(PNG_DIRS)
# commented out for the release because they don't work
#	imgaddmodule \
#	imgmulmodule \
#	starfield \
#	libmpeg3module

