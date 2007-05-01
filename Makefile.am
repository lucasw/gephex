AUTOMAKE_OPTIONS = 1.6
SUBDIRS = contrib base build engine types util modules effectvmodules qtgui data examples doc
EXTRA_DIST = BUGS NEWS README COPYING README.win32 README.macosx config_h.win32

# Strip binaries
install-exec-hook:
	strip $(DESTDIR)@bindir@/gephex-engine-real
	strip $(DESTDIR)@bindir@/gephex-gui-real