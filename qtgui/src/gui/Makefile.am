SUBDIRS= base editor typeviews

AM_CPPFLAGS = \
	-I $(srcdir)/.. \
	-I $(srcdir)/../.. \
	-I $(srcdir)/../../../util/include \
	-I @builddir@/../../../util/include \
	-I $(srcdir)/../../../base/src/ \
	-I $(srcdir)/../../../base/src/utils \
	-I @builddir@/../../../base/src/ \
	-I $(srcdir)/../../../base/src/net \
	-I $(srcdir)/../../../base/src/netinterfaces \
	$(QT_CXXFLAGS)

bin_PROGRAMS = gephex-gui

CPP_FILES = \
	nodewidget.cpp \
	connectionwidget.cpp \
	main.cpp \
	vjmainwindow.cpp \
	controlwidget.cpp \
	moduleclassview.cpp \
	propertywidget.cpp \
	picswitch.cpp \
	nodeproperty.cpp \
	propertywidgetconstructor.cpp \
	hidebuttonconstructor.cpp \
	hidebutton.cpp \
	plugwidget.cpp \
	inputplugwidget.cpp \
	outputplugwidget.cpp \
	sequenceeditor.cpp \
	dllselectordialog.cpp \
	sequencewidget.cpp \
	scenewidget.cpp \
	graphnameview.cpp \
	sequencenameview.cpp \
	playlist.cpp \
	playlistnameview.cpp \
	moduleclasstabview.cpp \
	uebertab.cpp \
	modulebutton.cpp \
	videowallcontrollwidget.cpp \
	guiconfig.cpp \
	typeview.cpp \
	typeviewfactory.cpp \
	aboutdialog.cpp

MOCED_FILES = \
	playlist_moc.cpp \
	dllselectordialog_moc.cpp \
	sequenceeditor_moc.cpp \
	plugwidget_moc.cpp \
	sequencewidget_moc.cpp \
	outputplugwidget_moc.cpp \
	inputplugwidget_moc.cpp \
	moduleclassview_moc.cpp \
	propertywidget_moc.cpp \
	vjmainwindow_moc.cpp \
	controlwidget_moc.cpp \
	graphnameview_moc.cpp \
	videowallcontrollwidget_moc.cpp \
	picswitch_moc.cpp \
	hidebutton_moc.cpp \
	sequencenameview_moc.cpp \
	nodewidget_moc.cpp \
	playlistnameview_moc.cpp \
	modulebutton_moc.cpp \
	moduleclasstabview_moc.cpp \
	typeview_moc.cpp

BUILT_SOURCES = $(MOCED_FILES)

HEADER_FILES = \
	connectionwidget.h \
	controlwidget.h \
	dllselectordialog.h \
	graphnameview.h \
	hidebuttonconstructor.h \
	hidebutton.h \
	imoduleinfobasestation.h \
	inputplugwidget.h \
	modulebutton.h \
	moduleclassview.h \
	nodeproperty.h \
	nodewidget.h \
	outputplugwidget.h \
	ownstyle.h \
	picswitch.h \
	plugwidget.h \
	propertywidgetconstructor.h \
	propertywidget.h \
	scenewidget.h \
	sequenceeditor.h \
	sequencenameview.h \
	sequencewidget.h \
	videowallcontrollwidget.h \
	vjmainwindow.h \
	playlist.h \
	playlistnameview.h \
	moduleclasstabview.h \
	uebertab.h \
	guiconfig.h \
	typeview.h \
	typeviewfactory.h \
	aboutdialog.h

EXTRA_DIST= \
	node.xpm \
	inplugfree.xpm \
	inplugbusy.xpm \
	outplugfree.xpm \
	outplugbusy.xpm \
	rot_klein.xpm \
	gruen_klein.xpm

gephex_gui_SOURCES =  $(CPP_FILES) $(HEADER_FILES) $(MOCED_FILES)

dist-hook:
	rm -f $(distdir)/*_moc.cpp

Makefile: $(BUILT_SOURCES)

%_moc.cpp: %.h
	$(MOC) -o $@ $<

gephex_gui_LDADD = \
	$(QT_LIBS) \
	-lguimodel \
	-lgphxnetwork \
	-lnetinterfaces \
	-lguibase \
	-lguieditor \
	-ltypeviews \
	-lutils \
	-L@builddir@/../guimodel \
	-L@builddir@/../../../base/src/net \
	-L@builddir@/../../../base/src/netinterfaces \
	-L@builddir@/../../../base/src/utils \
	-L@builddir@/base \
	-L@builddir@/editor \
	-L@builddir@/typeviews

gephex_gui_DEPENDENCIES = \
	@builddir@/../guimodel/libguimodel.a \
	@builddir@/../../../base/src/net/libgphxnetwork.a \
	@builddir@/../../../base/src/netinterfaces/libnetinterfaces.a \
	@builddir@/../../../base/src/utils/libutils.a \
	@builddir@/base/libguibase.a \
	@builddir@/editor/libguieditor.a \
	@builddir@/typeviews/libtypeviews.a

CLEANFILES = $(MOCED_FILES)
