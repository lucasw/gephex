SUBDIRS = src

# Remove unneeded static and libtool libs after installation
# of subdirs has finished
install-exec-hook:
	rm $(DESTDIR)@gphx_module_lib_dir@/*.la
	rm $(DESTDIR)@gphx_module_lib_dir@/*.a
	strip $(DESTDIR)@gphx_module_lib_dir@/*.so 2>&1 > /dev/null | true
