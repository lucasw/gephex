baseincludedir = @includedir@/gephex

MOC = moc

noinst_LIBRARIES = libpropertywidgets.a

libpropertywidgets_a_SOURCES =colorselectorwidget.cpp comboboxwidget.cpp fileselectorwidget.cpp fontselectorwidget.cpp lineeditwidget.cpp numberselectorwidget.cpp  videowallselectorwidget.cpp colorselectorwidget_moc.cpp comboboxwidget_moc.cpp fileselectorwidget_moc.cpp fontselectorwidget_moc.cpp lineeditwidget_moc.cpp numberselectorwidget_moc.cpp videowallselectorwidget_moc.cpp radiobuttonwidget.cpp radiobuttonwidget_moc.cpp colorselectorwidget.h comboboxwidget.h fileselectorwidget.h fontselectorwidget.h lineeditwidget.h numberselectorwidget.h radiobuttonwidget.h videowallselectorwidget.h

%_moc.cpp: %.h
	$(MOC) -o $@ $<

INCLUDES = -I$(QTDIR)/include -I/usr/include/qt/ -I .. -I ../.. -I $(baseincludedir)

clean:
	rm -f *_moc.cpp


