EXTRA_DIST = netinterfaces.vcproj netinterfaces.dsp netinterfaces.mak netinterfaces.dep

INCLUDES= -I @builddir@/.. -I @srcdir@/.. -I @top_srcdir@/util/include

noinst_LIBRARIES = libnetinterfaces.a

libnetinterfaces_a_SOURCES = \
	enginecontrolsendernet.cpp \
	enginecontrolreceivernet.cpp \
	renderercontrolreceivernet.cpp \
	renderercontrolsendernet.cpp \
	modelcontrolreceivernet.cpp \
	moduledatareceivernet.cpp \
	moduledatasendernet.cpp \
	moduleconstructiondumbreceivernet.cpp \
	modelcontrolsendernet.cpp \
	moduleconstructiondumbsendernet.cpp \
	moduleclassinforeceivernet.cpp \
	moduleclassinfosendernet.cpp \
	controlvaluereceivernet.cpp \
	controlvaluesendernet.cpp \
	modulestatisticsreceivernet.cpp \
	modulestatisticssendernet.cpp \
	errorsendernet.cpp \
	errorreceivernet.cpp \
	graphnamereceivernet.cpp \
	graphnamesendernet.cpp \
	modelstatusreceivernet.cpp \
	modelstatussendernet.cpp \
	rendererstatusreceivernet.cpp \
	rendererstatussendernet.cpp \
	graphdatareceivernet.cpp \
	graphdatasendernet.cpp

noinst_HEADERS = \
	controlvaluereceivernet.h \
	controlvaluesendernet.h \
	enginecontrolreceivernet.h \
	enginecontrolsendernet.h \
	errorreceivernet.h \
	errorsendernet.h \
	graphnamereceivernet.h \
	graphnamesendernet.h \
	modelcontrolreceivernet.h \
	modelcontrolsendernet.h \
	moduleclassinforeceivernet.h \
	moduleclassinfosendernet.h \
	moduleconstructiondumbreceivernet.h \
	moduleconstructiondumbsendernet.h \
	moduledatareceivernet.h \
	moduledatasendernet.h \
	modulestatisticsreceivernet.h \
	modulestatisticssendernet.h \
	nodelcontrolreceivertest.h \
	renderercontrolreceivernet.h \
	renderercontrolsendernet.h \
	modelstatusreceivernet.h \
	modelstatussendernet.h \
	rendererstatusreceivernet.h \
	rendererstatussendernet.h \
	graphdatareceivernet.h \
	graphdatasendernet.h


%receivernet.h: ../interfaces/%.if
	python @srcdir@/../../nic.py nrh . $<

%receivernet.cpp: ../interfaces/%.if %receivernet.h
	python @srcdir@/../../nic.py nrc . $<

%sendernet.h: ../interfaces/%.if
	python @srcdir@/../../nic.py nsh . $<

%sendernet.cpp: ../interfaces/%.if %sendernet.h
	python @srcdir@/../../nic.py nsc . $<

DISTCLEANFILES = *sendernet.cpp *sendernet.h *receivernet.cpp *receivernet.h

# TESTS=netinterfacetest
# check_PROGRAMS = netinterfacetest
# netinterfacetest_SOURCES = testmain.cpp classinfotest.cpp nodelcontrolreceivertest.cpp classinfotest.h
# netinterfacetest_LDADD = ../TestFramework/libtestframework.la libnetinterfaces.a ../utils/libutils.a

