libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

funparsemodule_auto.c: funparsemodule.spec funparsemodule.h
	$(PLUC) c @srcdir@/funparsemodule.spec

funparsemodule.h: funparsemodule.spec
	$(PLUC) h @srcdir@/funparsemodule.spec

lib_LTLIBRARIES = funparsemodule.la

funparsemodule_la_SOURCES = \
        funparsemodule_auto.c \
        funparsemodule.c \
        funparsemodule.h \
        funparsemodule.spec \
        funparsemodule.xpm \
	expresso.h \
	expresso.c \
	slist.h \
	slist.c \
	env.h \
	env.c \
	expression.h \
	expression.c \
	string_copy.h \
	string_copy.c \
	parser.tab.h \
	parser.tab.c \
	scanner.c \
	parser.h \
	builtin_functions.h \
	builtin_functions.c


EXTRA_DIST = parser.y scanner.flex \
	funparsemodule.vcproj funparsemodule.dsp funparsemodule.mak funparsemodule.dep

scanner.o: parser.tab.h

scanner.c: @srcdir@/scanner.flex
	flex -oscanner.c @srcdir@/scanner.flex

parser.tab.h: @srcdir@/parser.y
	bison -d @srcdir@/parser.y

parser.tab.c: @srcdir@/parser.y
	bison -d @srcdir@/parser.y


funparsemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = funparsemodule.h funparsemodule_auto.c scanner.c parser.tab.h parser.tab.c

