EXTRA_DIST = dllloader.dsp dllloader.mak dllloader.dep

baseincludedir = @includedir@/gephex
includedir = $(baseincludedir)/dllloader
libdir = @libdir@/gephex

noinst_HEADERS = dllloader.h

INCLUDES= \
	-I @srcdir@/.. \
	-I @srcdir@/../../../base/src \
	-I @builddir@/../../../base/src \
	-I @top_srcdir@/util/include \
	-I @top_builddir@/util/include

noinst_LIBRARIES = libdllloader.a

libdllloader_a_SOURCES = \
	typedllloader.cpp \
	c_moduleclass.cpp \
	dllloader.cpp \
	nameresolver.cpp \
	c_module.cpp \
	c_input.cpp \
	c_output.cpp \
	c_typeclass.cpp \
	moduleclassspec.cpp \
	c_outputplug.cpp \
	c_type.cpp \
	moduleinfoutils.cpp \
	typedllloader.h \
	c_functiontypes.h \
	c_input.h \
	c_moduleclass.h \
	c_module.h \
	c_moduletables.h \
	c_output.h \
	c_outputplug.h \
	c_typeclass.h \
	c_type.h \
	c_typetables.h \
	moduleclassspec.h \
	moduleinfoutils.h \
	nameresolver.h \
	module.h \
	frei0rwrapper.cpp \
	frei0rwrapper.h \
	frei0r.h \
	frei0r.xpm




