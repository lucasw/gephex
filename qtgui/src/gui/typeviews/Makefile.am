EXTRA_DIST = typeviews.dsp typeviews.mak typeviews.dep

baseincludedir = @includedir@/gephex

noinst_LIBRARIES = libtypeviews.a

BUILT_SOURCES = \
	boundednumberview_moc_cpp.cpp \
	slidernumberview_moc_cpp.cpp \
	unboundednumberview_moc_cpp.cpp \
	comboboxstringview_moc_cpp.cpp \
	radionumberview_moc_cpp.cpp \
	checkboxnumberview_moc_cpp.cpp \
	positionview_moc_cpp.cpp \
	filestringview_moc_cpp.cpp \
	colorview_moc_cpp.cpp \
	fontview_moc_cpp.cpp \
	frameview_moc_cpp.cpp \
	dialnumberview_moc_cpp.cpp \
	stringview_moc_cpp.cpp

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
	checkboxnumberview.cpp \
	checkboxnumberview.h \
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

%_moc_cpp.cpp: %.cpp
	$(MOC) -o $@ $<

INCLUDES = \
	-I @srcdir@/../.. \
	-I @srcdir@/../../../../base/src/ \
	-I @builddir@/../../../../base/src/ \
        -I @top_srcdir@/util/include \
        -I @top_builddir@/util/include \
	$(QT_CXXFLAGS)

CLEANFILES = $(BUILT_SOURCES)
