baseincludedir = @includedir@/gephex

noinst_LIBRARIES = libtypeviews.a

BUILT_SOURCES = \
	boundednumberview_moc.cpp \
	slidernumberview_moc.cpp \
	unboundednumberview_moc.cpp \
	comboboxstringview_moc.cpp \
	radionumberview_moc.cpp \
	positionview_moc.cpp \
	filestringview_moc.cpp \
	colorview_moc.cpp \
	fontview_moc.cpp \
	frameview_moc.cpp \
	dialnumberview_moc.cpp \
	stringview_moc.cpp

libtypeviews_a_SOURCES = \
	boundednumberview.cpp \
	boundednumberview.h \
	slidernumberview.cpp \
	slidernumberview.h \
	unboundednumberview.cpp \
	unboundednumberview.h \
	comboboxstringview.cpp \
	comboboxstringview.h \
	radionumberview.cpp \
	radionumberview.h \
	positionview.cpp \
	positionview.h \
	filestringview.cpp \
	filestringview.h \
	colorview.cpp \
	colorview.h \
	fontview.cpp \
	fontview.h \
	frameview.cpp \
	frameview.h \
	dialnumberview.cpp \
	dialnumberview.h \
	stringview.cpp \
	stringview.h

Makefile: $(BUILT_SOURCES)

%_moc.cpp: %.cpp
	$(MOC) -o $@ $<

INCLUDES = \
	-I @srcdir@/../.. \
	-I @srcdir@/../../../../base/src/ \
	-I @builddir@/../../../../base/src/ \
        -I @top_srcdir@/util/include \
        -I @top_builddir@/util/include \
	$(QT_CXXFLAGS)

CLEANFILES = $(BUILT_SOURCES)
