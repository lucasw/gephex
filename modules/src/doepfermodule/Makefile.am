doepfermodule_auto.c: doepfermodule.spec doepfermodule.h
	python $(top_builddir)/pluc.py c doepfermodule.spec

doepfermodule.h: doepfermodule.spec
	python $(top_builddir)/pluc.py h doepfermodule.spec

lib_LTLIBRARIES = doepfermodule.la
doepfermodule_la_SOURCES = doepfermodule_auto.c doepfermodule.c doepfermodule.h doepfermodule.spec doepfermodule.xpm

doepfermodule_la_LDFLAGS = -module -avoid-version -no-undefined -L../libmidi

doepfermodule_la_LIBADD = -lmidi

#INCLUDES  =  -I$(top_builddir)/../engine/src/engine 
INCLUDES  =  -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine -I ../libmidi

.PHONY: clean
clean:
	rm -f doepfermodule.h doepfermodule_auto.c
