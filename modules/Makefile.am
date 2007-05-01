libdir = @gphx_module_lib_dir@
SUBDIRS = src
EXTRA_DIST = pluc.py

# Remove unneeded static and libtool libs after installation
# of subdirs has finished
install-exec-hook:
	rm $(DESTDIR)@gphx_module_lib_dir@/*.la
	rm $(DESTDIR)@gphx_module_lib_dir@/*.a
	strip $(DESTDIR)@gphx_module_lib_dir@/*.so 2>&1 > /dev/null | true

# Necessary because libtool uninstall won't work correctly without the .la
# files. This will also remove the effectvmodules and any other modules
# the user might have copied there.
uninstall-hook:
	rm $(DESTDIR)@gphx_module_lib_dir@/*.so
