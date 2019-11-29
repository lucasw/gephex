libdir = @gphx_module_lib_dir@

PLUC=python $(top_srcdir)/modules/pluc.py

ifsgenmodule_auto.c: ifsgenmodule.spec ifsgenmodule.h
	$(PLUC) c $(srcdir)/ifsgenmodule.spec

ifsgenmodule.h: ifsgenmodule.spec
	$(PLUC) h $(srcdir)/ifsgenmodule.spec

lib_LTLIBRARIES = ifsgenmodule.la

ifsgenmodule_la_SOURCES = ifsgenmodule_auto.c \
	                  ifsgenmodule.cpp \
			  ifsgenmodule.h \
			  ifsgenmodule.spec \
			  ifsgenmodule.xpm

ifsgenmodule_la_LDFLAGS = -module -avoid-version -no-undefined
ifsgenmodule_la_LIBADD = -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/ifstype \
           -I@srcdir@/../../../types/src/numbertype 


 

DISTCLEANFILES = ifsgenmodule.h ifsgenmodule_auto.c
EXTRA_DIST = ifsgenmodule.vcproj ifsgenmodule.dsp ifsgenmodule.mak ifsgenmodule.dep
