INTERFACE_FILES = \
		controlvalue.if \
		enginecontrol.if \
		error.if \
		graphname.if \
		modelcontrol.if \
		modelstatus.if \
		moduleclass.if \
		moduleclassinfo.if \
		moduleclassloadercontrol.if \
		moduleclassname.if \
		moduleclassspec.if \
		moduleconstructiondumb.if \
		moduleconstructionsmart.if \
		moduledata.if \
		modulestatistics.if \
		modulestatisticssmart.if \
		renderercontrol.if \
		rendererstatus.if \
		sequencename.if \
		sequencercontrol.if \
		sequencerstatus.if \
		sequenceupdate.if \
		serializedgraph.if \
		smartcontrolvalue.if \
		typeclass.if \
		typeclassinfo.if \
		typeclassloadercontrol.if \
		typeclassname.if

GENERATED_H =  $(INTERFACE_FILES:%.if=i%receiver.h) $(INTERFACE_FILES:%.if=i%sender.h)

noinst_HEADERS = \
		$(GENERATED_H) \
		imoduleclass.h \
		imoduleclassspec.h \
		imodule.h \
		itask.h \
		itypeclass.h \
		itypefactory.h \
		itype.h


i%receiver.h: %.if
	python @srcdir@/../../nic.py ir . $<

i%sender.h: %.if
	python @srcdir@/../../nic.py is . $<

DISTCLEANFILES = $(GENERATED_H)
