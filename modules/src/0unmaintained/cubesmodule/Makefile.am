libdir = @gphx_module_lib_dir@
cubesmodule_auto.c: cubesmodule.spec cubesmodule.h
	python ../../pluc.py c cubesmodule.spec

cubesmodule.h: cubesmodule.spec
	python ../../pluc.py h cubesmodule.spec

lib_LTLIBRARIES = cubesmodule.la
cubesmodule_la_SOURCES = cubesmodule_auto.c cubesmodule.cpp cubesmodule.h cubesmodule.spec cubesmodule.xpm cube_table.h basicmath.h


cubesmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I$(baseincludedir) -I$(baseincludedir)/types -I$(baseincludedir)/engine -I../../../engine/src/engine -I../../../util/include -I../../../types/src/numbertype -I../../../types/src/framebuffertype 
