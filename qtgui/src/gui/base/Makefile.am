EXTRA_DIST = base.vcproj base.dsp base.mak base.dep
noinst_LIBRARIES = libguibase.a

CPP_FILES = \
	askforstringdialog.cpp \
	logwindow.cpp \
	treeview.cpp \
        treeviewitem.cpp \
	propertyview.cpp \
	key.cpp \
	keyboardmanager.cpp \
	picmanager.cpp

MOCED_FILES = \
	askforstringdialog_moc.cpp

BUILT_SOURCES = $(MOCED_FILES) treeview_moc.cpp

HEADER_FILES = \
	askforstringdialog.h \
	logwindow.h \
	ipropertydescription.h \
	propertyview.h \
	iwidgetconstructor.h \
	treeview.h \
	treeviewitem.h \
	key.h \
	ikeylistener.h \
	keyboardmanager.h\
	picmanager.h

libguibase_a_SOURCES =  $(CPP_FILES) $(HEADER_FILES)
nodist_libguibase_a_SOURCES =  $(MOCED_FILES)

#treeview.o: treeview_moc.cpp
treeview_moc.cpp: treeview.cpp
	$(MOC) -o treeview_moc.cpp $(srcdir)/treeview.cpp

%_moc.cpp: %.h
	$(MOC) -o $@ $<

INCLUDES = \
	-I $(srcdir)/.. \
	-I $(srcdir)/../.. \
	-I $(srcdir)/../../../../base/src \
	-I @builddir@/../../../../base/src \
	-I $(srcdir)/../../../../base/src/TestFramework \
	$(QT_CXXFLAGS)

TESTS=guibasetest

check_PROGRAMS = guibasetest

guibasetest_SOURCES = \
		testmain.cpp \
		keytest.cpp \
		keytest.h

guibasetest_INCLUDES = 

guibasetest_DEPENDENCIES = \
	@builddir@/../../../../base/src/TestFramework/libtestframework.a \
	@builddir@/libguibase.a

guibasetest_LDADD = \
	-L@builddir@/../../../../base/src/TestFramework \
	-L@builddir@ \
	-ltestframework \
	-lguibase

CLEANFILES = $(BUILT_SOURCES)
