SUBDIRS = images

htmldir = $(prefix)/share/doc/gephex/html
html_DATA = documentation.html

man_MANS = gephex.1 gephex-engine.1 gephex-gui.1

# include this prebuild stuff (and its sources) in the dist
EXTRA_DIST     =  $(html_DATA)  $(man_MANS) $(srcdir)/documentation.xml $(srcdir)/module-api*.xml  $(srcdir)/type-api*.xml $(srcdir)/gephex.xml $(srcdir)/gephex-engine.xml $(srcdir)/gephex-gui.xml
DISTCLEANFILES = documentation.html gephex.1 gephex-engine.1 gephex-gui.1

gephex.1: $(srcdir)/gephex.xml
	docbook2x-man $(srcdir)/gephex.xml > gephex.1

gephex-engine.1: $(srcdir)/gephex-engine.xml
	docbook2x-man $(srcdir)/gephex-engine.xml > gephex-engine.1

gephex-gui.1: $(srcdir)/gephex-gui.xml
	docbook2x-man $(srcdir)/gephex-gui.xml > gephex-gui.1

all-local: documentation.html gephex.1 gephex-engine.1 gephex-gui.1

documentation.html: $(srcdir)/documentation.xml  $(srcdir)/module-api*.xml  $(srcdir)/type-api*.xml $(srcdir)/images/*.png
	xsltproc --xinclude --param shade.verbatim 1 -o documentation.html /usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl $(srcdir)/documentation.xml



