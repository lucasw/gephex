EXTRA_DIST = dialogs.vcproj dialogs.dsp dialogs.mak dialogs.dep

baseincludedir = @includedir@/gephex

noinst_LIBRARIES = libdialogs.a

BUILT_SOURCES = \
	aboutdialog_ui.h \
	changesdialog_ui.h

libdialogs_a_SOURCES = \
	aboutdialog.ui \
	aboutdialog.cpp \
	aboutdialog.h \
	changesdialog.ui \
	changesdialog.cpp \
	changesdialog.h \
	newgraphdialog.cpp \
	newgraphdialog.h

nodist_libdialogs_a_SOURCES = $(BUILT_SOURCES)

aboutdialog_ui.h: aboutdialog.ui
	$(UIC) @srcdir@/aboutdialog.ui > @builddir@/aboutdialog_ui.h
changesdialog_ui.h: changesdialog.ui
	$(UIC) @srcdir@/changesdialog.ui > @builddir@/changesdialog_ui.h

INCLUDES = \
	-I @srcdir@/../.. \
	-I @srcdir@/../../../../base/src/ \
	-I @builddir@/../../../../base/src/ \
        -I @top_srcdir@/util/include \
        -I @top_builddir@/util/include \
	$(QT_CXXFLAGS)

CLEANFILES = $(BUILT_SOURCES)
