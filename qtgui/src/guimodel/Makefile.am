INCLUDES = -I @srcdir@/../../../base/src \
	   -I @builddir@/../../../base/src \
	   -I @srcdir@/../../../util/include

noinst_LIBRARIES = libguimodel.a
libguimodel_a_SOURCES = \
	controlmodel.cpp \
	moduleinfo.cpp \
	moduleclassmodel.cpp \
	point.cpp \
	graphmodel.cpp \
	xpm.cpp \
	controlvaluedispatcher.cpp \
	moduledatadispatcher.cpp \
	enginewrapper.cpp \
	actionsequencerwrapper.cpp \
	controlmodel.h \
	controlvaluedispatcher.h \
	enginewrapper.h \
	graphmodel.h \
	icontrolconnectview.h \
	icontrolview.h \
	igraphview.h \
	imoduleclassview.h \
	moduleclassmodel.h \
	moduledatadispatcher.h \
	moduleinfo.h \
	pluginfo.h \
	point.h \
	xpm.h \
	actionsequencerwrapper.h \
	iscenesequencer.h \
	iscenechangelistener.h

TESTS=guimodeltest

check_PROGRAMS = guimodeltest

guimodeltest_SOURCES = \
	testmain.cpp \
	actionsequencerwrapper.cpp \
	actionsequencerwrappertest.cpp \
	actionsequencerwrappertest.h

guimodeltest_LDADD = 	-L../../../base/src/TestFramework -ltestframework \
			-L../../../base/src/utils -lutils
