SUBDIRS = images

htmldir = $(prefix)/share/doc/gephex/html
html_DATA = documentation.html

man_MANS = gephex.1 gephex-engine.1 gephex-gui.1

DB2M=@docbooktoxman@
DBXSLDIR=@docbook_xsl_dir@

# include this prebuild stuff (and its sources) in the dist
EXTRA_DIST     =  \
	$(html_DATA)                \
	$(man_MANS)                 \
	$(srcdir)/documentation.xml \
	$(srcdir)/module-api*.xml   \
	$(srcdir)/type-api*.xml     \
	$(srcdir)/gephex.xml        \
	$(srcdir)/gephex-engine.xml \
	$(srcdir)/gephex-gui.xml

DISTCLEANFILES = documentation.html gephex.1 gephex-engine.1 gephex-gui.1

gephex.1: $(srcdir)/gephex.xml
	if test "x${DB2M}" = "x"; then  touch gephex.1; else ${DB2M} $(srcdir)/gephex.xml; fi

gephex-engine.1: $(srcdir)/gephex-engine.xml
	if test "x${DB2M}" = "x"; then  touch gephex-engine.1; else ${DB2M} $(srcdir)/gephex-engine.xml; fi

gephex-gui.1: $(srcdir)/gephex-gui.xml
	if test "x${DB2M}" = "x"; then  touch gephex-gui.1; else ${DB2M} $(srcdir)/gephex-gui.xml; fi

all-local: documentation.html gephex.1 gephex-engine.1 gephex-gui.1

documentation.html: $(srcdir)/documentation.xml  $(srcdir)/module-api*.xml  $(srcdir)/type-api*.xml $(srcdir)/images/*.png
	if test "x${DBXSLDIR}" = "x"; then touch documentation.html; else xsltproc --xinclude -o documentation.html ${DBXSLDIR}/html/docbook.xsl $(srcdir)/documentation.xml; fi

documentation.fo: $(srcdir)/documentation.xml  $(srcdir)/module-api*.xml  $(srcdir)/type-api*.xml $(srcdir)/images/*.png
	if test "x${DBXSLDIR}" = "x"; then touch documentation.fo; else xsltproc --stringparam draft.mode no --stringparam fop.extensions 1 --xinclude -o documentation.fo ${DBXSLDIR}/fo/docbook.xsl $(srcdir)/documentation.xml; fi

documentation.pdf: $(srcdir)/documentation.fo 
	if test "x${DBXSLDIR}" = "x"; then touch documentation.pdf; else fop -d documentation.fo documentation.pdf; fi
