baseincludedir = @includedir@/gephex
includedir = $(baseincludedir)/guimodel
libdir = @libdir@/gephex

INCLUDES= -I $(baseincludedir)

noinst_LIBRARIES = libguimodel.a
libguimodel_a_SOURCES = controlmodel.cpp moduleinfo.cpp moduleclassmodel.cpp point.cpp graphmodel.cpp xpm.cpp controlvaluedispatcher.cpp moduledatadispatcher.cpp enginewrapper.cpp actionsequencerwrapper.cpp controlmodel.h controlvaluedispatcher.h enginewrapper.h graphmodel.h icontrolconnectview.h  icontrolview.h igraphview.h  imoduleclassview.h moduleclassmodel.h moduledatadispatcher.h moduleinfo.h pluginfo.h point.h xpm.h actionsequencerwrapper.h  iscenesequencer.h iscenechangelistener.h




noinst_PROGRAMS = guimodeltest
guimodeltest_SOURCES = testmain.cpp actionsequencerwrapper.cpp actionsequencerwrappertest.cpp actionsequencerwrappertest.h

guimodeltest_LDADD = -L$(libdir) -ltestframework -lutils
