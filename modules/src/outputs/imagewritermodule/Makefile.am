libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

imagewritermodule_auto.c: imagewritermodule.spec imagewritermodule.h
	$(PLUC) c $(srcdir)/imagewritermodule.spec

imagewritermodule.h: imagewritermodule.spec
	$(PLUC) h $(srcdir)/imagewritermodule.spec

lib_LTLIBRARIES = imagewritermodule.la

imagewritermodule_la_SOURCES = 	imagewritermodule_auto.c \
	                     	imagewritermodule.cpp \
				imagewritermodule.h \
				imagewritermodule.spec \
				imagewritermodule.xpm

imagewritermodule_la_LDFLAGS = -module -avoid-version -no-undefined
imagewritermodule_la_LIBADD = -lpng -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/numbertype 

DISTCLEANFILES = imagewritermodule.h imagewritermodule_auto.c

