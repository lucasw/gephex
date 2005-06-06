EXTRA_DIST = dialogs.dsp dialogs.mak dialogs.dep

baseincludedir = @includedir@/gephex

noinst_LIBRARIES = libdialogs.a

BUILT_SOURCES = \
	aboutdialog.cpp \
	aboutdialog.h \
	aboutdialog_h_moc.cpp \
	changesdialog.cpp \
	changesdialog.h \
	changesdialog_h_moc.cpp \
	newgraphdialog_h_moc.cpp

libdialogs_a_SOURCES = \
	aboutdialog.ui \
	aboutdialogimpl.cpp \
	aboutdialogimpl.h \
	changesdialog.ui \
	changesdialogimpl.cpp \
	changesdialogimpl.h \
	newgraphdialog.cpp \
	newgraphdialog.h

nodist_libdialogs_a_SOURCES = $(BUILT_SOURCES)

%_h_moc.cpp: %.h
	$(MOC) -o $@ $<

aboutdialog.h: aboutdialog.ui
	$(UIC) @srcdir@/aboutdialog.ui > @builddir@/aboutdialog.h
changesdialog.h: changesdialog.ui
	$(UIC) @srcdir@/changesdialog.ui > @builddir@/changesdialog.h

aboutdialog.cpp: aboutdialog.ui
	$(UIC) -impl @builddir@/aboutdialog.h @srcdir@/aboutdialog.ui > @builddir@/aboutdialog.cpp

changesdialog.cpp: changesdialog.ui
	$(UIC) -impl @builddir@/changesdialog.h @srcdir@/changesdialog.ui > @builddir@/changesdialog.cpp

INCLUDES = \
	-I @srcdir@/../.. \
	-I @srcdir@/../../../../base/src/ \
	-I @builddir@/../../../../base/src/ \
        -I @top_srcdir@/util/include \
        -I @top_builddir@/util/include \
	$(QT_CXXFLAGS)

CLEANFILES = $(BUILT_SOURCES)
