EXTRA_DIST = dllloader.vcproj dllloader.dsp dllloader.mak dllloader.dep

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
	gephex_type_plugin.cpp \
	gephex_module_class.cpp \
	gephex_module_plugin.cpp \
	gephex_module_plugin.h \
	frei0r_module_class.cpp \
	dllloader.cpp \
	nameresolver.cpp \
	gephex_module.cpp \
	frei0r_module.cpp \
	frei0r_module.h \
	c_input.cpp \
	c_output.cpp \
	c_typeclass.cpp \
	moduleclassspec.cpp \
	c_outputplug.cpp \
	c_type.cpp \
	moduleinfoutils.cpp \
	gephex_type_plugin.h \
	c_functiontypes.h \
	c_input.h \
	gephex_module_class.h \
	frei0r_module_class.h \
	gephex_module.h \
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
	frei0r_module_plugin.cpp \
	frei0r_module_plugin.h \
	frei0r.h \
	frei0r.xpm




