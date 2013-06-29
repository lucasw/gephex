EXTRA_DIST = editor.vcproj editor.dsp editor.mak editor.dep

baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex

INCLUDES = \
	-I $(srcdir)/../.. \
	-I $(srcdir)/../../../../base/src \
	-I @builddir@/../../../../base/src \
	-I $(srcdir)/.. \
        -I $(top_srcdir)/util/include \
	$(QT_CXXFLAGS)

noinst_LIBRARIES = libguieditor.a

CPP_FILES = \
	controleditor.cpp \
	editorwidget.cpp \
	grapheditor.cpp \
	controleditorwindow.cpp \
	grapheditorwindow.cpp \
	labelwidget.cpp \
	mouseover.cpp


MOCED_FILES = \
	controleditor_moc.cpp \
	editorwidget_moc.cpp \
	grapheditor_moc.cpp \
	labelwidget_moc.cpp \
	mouseover_moc.cpp

MOCED_CPP_FILES = mouseover_moc_cpp.cpp

BUILT_SOURCES = $(MOCED_FILES) $(MOCED_CPP_FILES)

HEADER_FILES = \
	controleditor.h \
	grapheditor.h \
	ieditorcommandlistener.h \
	editorwidget.h \
	ieditor.h \
	ivisibleelement.h \
	controleditorwindow.h \
	grapheditorwindow.h \
	labelwidget.h \
	mouseover.h

libguieditor_a_SOURCES = $(CPP_FILES) $(HEADER_FILES)
nodist_libguieditor_a_SOURCES = $(MOCED_FILES)

%_moc.cpp: %.h
	$(MOC) -o $@ $<

%_moc_cpp.cpp: %.cpp
	$(MOC) -o $@ $<

CLEANFILES = $(BUILT_SOURCES)
