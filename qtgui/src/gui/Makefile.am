SUBDIRS= controlwidgets propertywidgets

baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex

INCLUDES=  -I.. -I$(QTDIR)/include -I/usr/include/qt/ -I$(baseincludedir)

MOC = moc

bin_PROGRAMS = gui

CPP_FILES = treeview.cpp treeviewitem.cpp  nodewidget.cpp connectionwidget.cpp main.cpp grapheditor.cpp vjmainwindow.cpp controlwidget.cpp controleditor.cpp controlwidgetfactory.cpp moduleclassview.cpp editorwidget.cpp propertywidgetfactory.cpp propertywidget.cpp picswitch.cpp propertyview.cpp nodeproperty.cpp propertywidgetconstructor.cpp grapheditorwindow.cpp controleditorwindow.cpp hidebuttonconstructor.cpp hidebutton.cpp plugwidget.cpp inputplugwidget.cpp outputplugwidget.cpp sequenceeditor.cpp dllselectordialog.cpp sequencewidget.cpp scenewidget.cpp graphnameview.cpp sequencenameview.cpp askforstringdialog.cpp logwindow.cpp playlist.cpp playlistnameview.cpp moduleclasstabview.cpp uebertab.cpp modulebutton.cpp videowallcontrollwidget.cpp

MOCED_FILES = playlist_moc.cpp askforstringdialog_moc.cpp dllselectordialog_moc.cpp sequenceeditor_moc.cpp plugwidget_moc.cpp sequencewidget_moc.cpp outputplugwidget_moc.cpp inputplugwidget_moc.cpp moduleclassview_moc.cpp vjmainwindow_moc.cpp controlwidget_moc.cpp graphnameview_moc.cpp videowallcontrollwidget_moc.cpp picswitch_moc.cpp hidebutton_moc.cpp sequencenameview_moc.cpp editorwidget_moc.cpp controleditor_moc.cpp grapheditor_moc.cpp nodewidget_moc.cpp playlistnameview_moc.cpp modulebutton_moc.cpp moduleclasstabview_moc.cpp

HEADER_FILES = askforstringdialog.h connectionwidget.h controleditor.h controleditorwindow.h controlwidgetfactory.h controlwidget.h dllselectordialog.h editorwidget.h grapheditor.h grapheditorwindow.h graphnameview.h hidebuttonconstructor.h hidebutton.h imoduleinfobasestation.h inputplugwidget.h ipropertydescription.h iwidgetconstructor.h  logwindow.h modulebutton.h moduleclassview.h nodeproperty.h nodewidget.h outputplugwidget.h ownstyle.h picswitch.h plugwidget.h propertyview.h  propertywidgetconstructor.h propertywidgetfactory.h propertywidget.h scenewidget.h sequenceeditor.h sequencenameview.h sequencewidget.h videowallcontrollwidget.h vjmainwindow.h playlist.h treeview.h treeviewitem.h playlistnameview.h moduleclasstabview.h uebertab.h

EXTRA_DIST=  node.xpm inplugfree.xpm inplugbusy.xpm outplugfree.xpm outplugbusy.xpm rot_klein.xpm gruen_klein.xpm

gui_SOURCES =  $(CPP_FILES) $(MOCED_FILES) $(HEADER_FILES)

treeview.o: treeview_moc.cpp
treeview_moc.cpp: treeview.cpp
	$(MOC) -o treeview_moc.cpp treeview.cpp

%_moc.cpp: %.h
	$(MOC) -o $@ $<

clean:
	rm -f *_moc.cpp


gui_LDFLAGS = -L$(QTDIR)/lib -L$(libdir) -L../guimodel
gui_LDADD = -lqt  -lguimodel -lnetwork -lnetinterfaces controlwidgets/libcontrolwidgets.a propertywidgets/libpropertywidgets.a -lutils





