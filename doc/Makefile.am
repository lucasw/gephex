SUBDIRS = images

man_MANS = gephex-gui.1 gephex-engine.1

htmldir = $(prefix)/share/doc/gephex/html
html_DATA = documentation.html

SGML_FILES = \
        documentation.sgml \
        gephex-engine.sgml \
        gephex-gui.sgml

# include this stuff in the dist
EXTRA_DIST = $(man_MANS) $(html_DATA) $(SGML_FILES)

DISTCLEANFILES=gephex-gui.1 gephex-engine.1 documentation.html

all-local: documentation.html

gephex-engine.1: $(srcdir)/gephex-engine.sgml
	docbook-to-man $(srcdir)/gephex-engine.sgml > gephex-engine.1

gephex-gui.1: $(srcdir)/gephex-gui.sgml
	docbook-to-man $(srcdir)/gephex-gui.sgml > gephex-gui.1

documentation.html: $(srcdir)/documentation.sgml $(srcdir)/images/*.png
	sgmltools -b onehtml $(srcdir)/documentation.sgml



