SUBDIRS= base editor typeviews dialogs

AM_CPPFLAGS = \
	-I $(srcdir)/.. \
	-I $(srcdir)/dialogs \
	-I @builddir@/dialogs \
	-I $(srcdir)/../.. \
	-I $(srcdir)/../../../util/include \
	-I @builddir@/../../../util/include \
	-I $(srcdir)/../../../base/src \
	-I $(srcdir)/../../../base/src/utils \
	-I @builddir@/../../../base/src \
	-I $(srcdir)/../../../base/src/net \
	-I $(srcdir)/../../../base/src/netinterfaces \
	$(QT_CXXFLAGS)

bin_PROGRAMS = gephex-gui-real

CPP_FILES = \
	connectionwidget.cpp \
	controlwidget.cpp \
	graphnameview.cpp \
	hidebutton.cpp \
	hidebuttonconstructor.cpp \
	inputplugwidget.cpp \
	main.cpp \
	modulebutton.cpp \
	moduleclassview.cpp \
	nodeproperty.cpp \
	nodewidget.cpp \
	outputplugwidget.cpp \
	picswitch.cpp \
	plugwidget.cpp \
	propertywidget.cpp \
	propertywidgetconstructor.cpp \
	typeview.cpp \
	typeviewfactory.cpp \
	vjmainwindow.cpp


MOCED_FILES = \
	controlwidget_moc.cpp \
	graphnameview_moc.cpp \
	hidebutton_moc.cpp \
	inputplugwidget_moc.cpp \
	modulebutton_moc.cpp \
	moduleclassview_moc.cpp \
	nodewidget_moc.cpp \
	outputplugwidget_moc.cpp \
	picswitch_moc.cpp \
	plugwidget_moc.cpp \
	propertywidget_moc.cpp \
	typeview_moc.cpp \
	vjmainwindow_moc.cpp

BUILT_SOURCES = $(MOCED_FILES) graphnameview_moc_cpp.cpp

HEADER_FILES = \
	connectionwidget.h \
	controlwidget.h \
	graphnameview.h \
	hidebutton.h \
	hidebuttonconstructor.h \
	imoduleinfobasestation.h \
	inputplugwidget.h \
	modulebutton.h \
	moduleclassview.h \
	nodeproperty.h \
	nodewidget.h \
	outputplugwidget.h \
	picswitch.h \
	plugwidget.h \
	propertywidget.h \
	propertywidgetconstructor.h \
	typeview.h \
	typeviewfactory.h \
	vjmainwindow.h


EXTRA_DIST= \
	gruen_klein.xpm \
	node.xpm \
	rot_klein.xpm \
	gui.vcproj gui.dsp gui.mak gui.dep \
	logo.ico \
	Skript1.rc resource.h

gephex_gui_real_SOURCES =  $(CPP_FILES) $(HEADER_FILES)
nodist_gephex_gui_real_SOURCES = $(MOCED_FILES)

#dist-hook:
#	rm -f $(distdir)/*_moc.cpp

%_moc.cpp: %.h
	$(MOC) -o $@ $<

%_moc_cpp.cpp: %.cpp
	$(MOC) -o $@ $<

gephex_gui_real_LDADD = \
	-lguimodel \
	-lgphxnetwork \
	-lnetinterfaces \
	-lguibase \
	-lguieditor \
	-ltypeviews \
	-lutils \
	-ldialogs \
	-L@builddir@/../guimodel \
	-L@builddir@/../../../base/src/net \
	-L@builddir@/../../../base/src/netinterfaces \
	-L@builddir@/../../../base/src/utils \
	-L@builddir@/base \
	-L@builddir@/editor \
	-L@builddir@/typeviews \
	-L@builddir@/dialogs \
	-L. $(QT_LIBS) $(LIB_SOCKET_FLAGS)

gephex_gui_real_DEPENDENCIES = \
	@builddir@/../guimodel/libguimodel.a \
	@builddir@/../../../base/src/net/libgphxnetwork.a \
	@builddir@/../../../base/src/netinterfaces/libnetinterfaces.a \
	@builddir@/../../../base/src/utils/libutils.a \
	@builddir@/base/libguibase.a \
	@builddir@/editor/libguieditor.a \
	@builddir@/dialogs/libdialogs.a \
	@builddir@/typeviews/libtypeviews.a

CLEANFILES = $(BUILT_SOURCES)

