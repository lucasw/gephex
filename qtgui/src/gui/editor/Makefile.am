baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex

INCLUDES = \
	-I $(srcdir)/../.. \
	-I $(srcdir)/../../../../base/src/ \
	-I @builddir@/../../../../base/src/ \
	-I $(srcdir)/.. \
        -I $(top_srcdir)/util/include \
	$(QT_CXXFLAGS)

noinst_LIBRARIES = libguieditor.a

CPP_FILES = \
	controleditor.cpp \
	editorwidget.cpp \
	grapheditor.cpp \
	controleditorwindow.cpp \
	grapheditorwindow.cpp #\
	#combinededitor.cpp


MOCED_FILES = \
	controleditor_moc.cpp \
	editorwidget_moc.cpp \
	grapheditor_moc.cpp

BUILT_SOURCES = $(MOCED_FILES)

HEADER_FILES = \
	controleditor.h \
	grapheditor.h \
	ieditorcommandlistener.h \
	editorwidget.h \
	ieditor.h \
	ivisibleelement.h \
	controleditorwindow.h \
	grapheditorwindow.h \
	combinededitor.h

libguieditor_a_SOURCES =  $(CPP_FILES) $(HEADER_FILES) $(MOCED_FILES)

dist-hook:
	rm -f $(distdir)/*_moc.cpp

Makefile: $(BUILT_SOURCES)

%_moc.cpp: %.h
	$(MOC) -o $@ $<

CLEANFILES = $(MOCED_FILES)
