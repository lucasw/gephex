baseincludedir = @includedir@/gephex
includedir = @includedir@/gephex/netinterfaces
libdir = @libdir@/gephex

# bin_PROGRAMS = netinterfacetest
lib_LIBRARIES = libnetinterfaces.a

libnetinterfaces_a_SOURCES = \
		sequencercontrolsendernet.cpp \
		sequencercontrolreceivernet.cpp \
		enginecontrolsendernet.cpp \
		enginecontrolreceivernet.cpp \
		moduleclassloadercontrolsendernet.cpp \
		moduleclassloadercontrolreceivernet.cpp \
		renderercontrolreceivernet.cpp \
		renderercontrolsendernet.cpp \
		modelcontrolreceivernet.cpp \
		moduledatareceivernet.cpp \
		moduledatasendernet.cpp \
		moduleclassnamereceivernet.cpp \
		moduleclassnamesendernet.cpp \
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
		sequenceupdatereceivernet.cpp \
		sequenceupdatesendernet.cpp \
		sequencenamesendernet.cpp \
		sequencenamereceivernet.cpp \
		sequencerstatussendernet.cpp \
		sequencerstatusreceivernet.cpp \
		modelstatusreceivernet.cpp \
		modelstatussendernet.cpp \
		rendererstatusreceivernet.cpp \
		rendererstatussendernet.cpp

include_HEADERS = \
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
		moduleclassloadercontrolreceivernet.h \
		moduleclassloadercontrolsendernet.h \
		moduleclassnamereceivernet.h \
		moduleclassnamesendernet.h \
		moduleconstructiondumbreceivernet.h \
		moduleconstructiondumbsendernet.h \
		moduledatareceivernet.h \
		moduledatasendernet.h \
		modulestatisticsreceivernet.h \
		modulestatisticssendernet.h \
		nodelcontrolreceivertest.h \
		renderercontrolreceivernet.h \
		renderercontrolsendernet.h \
		sequencenamereceivernet.h \
		sequencenamesendernet.h \
		sequencercontrolreceivernet.h \
		sequencercontrolsendernet.h \
		sequenceupdatereceivernet.h \
		sequenceupdatesendernet.h \
		sequencerstatussendernet.h \
		sequencerstatusreceivernet.h \
		modelstatusreceivernet.h \
		modelstatussendernet.h \
		rendererstatusreceivernet.h \
		rendererstatussendernet.h

INCLUDES= -I .. #-I $(baseincludedir)

#classinfotest.h

# netinterfacetest_SOURCES = testmain.cpp classinfotest.cpp nodelcontrolreceivertest.cpp

# netinterfacetest_LDADD = ../TestFramework/libtestframework.la libnetinterfaces.a ../utils/libutils.a


%receivernet.h: ../interfaces/%.if
	python $(top_builddir)/nic.py nrh . $<

%receivernet.cpp: ../interfaces/%.if %receivernet.h
	python $(top_builddir)/nic.py nrc . $<

%sendernet.h: ../interfaces/%.if
	python $(top_builddir)/nic.py nsh . $<

%sendernet.cpp: ../interfaces/%.if %sendernet.h
	python $(top_builddir)/nic.py nsc . $<

clean:
	rm -f *sendernet.cpp *sendernet.h *receivernet.cpp *receivernet.h