baseincludedir = @includedir@/gephex

MOC = moc

noinst_LIBRARIES = libcontrolwidgets.a

libcontrolwidgets_a_SOURCES =comboboxwidget.cpp dialwidget.cpp lineeditwidget.cpp positionwidget.cpp sliderwidget.cpp comboboxwidget_moc.cpp dialwidget_moc.cpp lineeditwidget_moc.cpp positionwidget_moc.cpp sliderwidget_moc.cpp comboboxwidget.h dialwidget.h lineeditwidget.h positionwidget.h sliderwidget.h videowallcontrolwidget.h videowallcontrolwidget.cpp

%_moc.cpp: %.h
	$(MOC) -o $@ $<

INCLUDES = -I ../.. -I$(QTDIR)/include -I/usr/include/qt/  -I $(baseincludedir)

clean:
	rm -f *_moc.cpp