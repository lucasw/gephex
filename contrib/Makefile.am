#if WITH_FFMPEG
#SUBDIRS = ffmpeg
#endif

# This is a proxy makefile as described in the automake manual
# ('when automake is not enough').
# It is built around the ffmpeg makefile.
# See also
# http://sources.redhat.com/ml/automake/2004-01/msg00215.html

all-local:
if WITH_FFMPEG
	cd ffmpeg && $(MAKE)
endif

#cd ${srcdir}/ffmpeg && $(MAKE) $(AM_MAKEFLAGS) all
check-local:
#if WITH_FFMPEG
#	cd ffmpeg && $(MAKE) test
#endif

clean-local:
if WITH_FFMPEG
	cd ffmpeg && $(MAKE) clean && find . -name "*.@SHAREDLIBEXT@" | xargs rm -f
endif
#	cd ${srcdir}/ffmpeg && $(MAKE) $(AM_MAKEFLAGS) clean

# Assuming the package knows how to install itself
install-data-local:
#cd subdir && $(MAKE) $(AM_MAKEFLAGS) install-data
install-exec-local:
#cd subdir && $(MAKE) $(AM_MAKEFLAGS) install-exec
uninstall-local:
#cd subdir && $(MAKE) $(AM_MAKEFLAGS) uninstall
# Distribute files from here.
#EXTRA_DIST = subdir/Makefile subdir/program.c ...

dist-hook:
if WITH_FFMPEG
	echo $(distdir)
	mkdir $(distdir)/ffmpeg
	cp -r ${srcdir}/ffmpeg $(distdir)
	SAVEDIR=`pwd` && cd $(distdir)/ffmpeg && find . -name ".svn" -o -name "*.o" -o -name "*.so" -o -name "*.so.??" -o -name "*.dylib" -o -name "*.a" -o -name "*.pc" | xargs rm -rf && rm -rf qt-faststart ffplay ffplay_g output_example ffmpeg_g ffmpeg ffserver ffserver_g .libs config.status config.h config.mak && cd ${SAVEDIR}
endif

distclean-local:
if WITH_FFMPEG
	if test "x${srcdir}" != "x."; then rm -rf ffmpeg/.depend ffmpeg/config.log ffmpeg/config.err ffmpeg/doc/Makefile ffmpeg/config.mak ffmpeg/config.h ffmpeg/qt-faststart ffmpeg/libavutil.pc ffmpeg/libavutil-uninstalled.pc ffmpeg/libavcodec.pc ffmpeg/libavcodec-uninstalled.pc ffmpeg/libavformat.pc ffmpeg/libavformat-uninstalled.pc ffmpeg/libpostproc.pc ffmpeg/libpostproc-uninstalled.pc ffmpeg/libswscale.pc ffmpeg/libswscale-uninstalled.pc; fi
endif
