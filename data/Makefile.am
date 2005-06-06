datadir = $(prefix)/share/gephex/
icondir = $(prefix)/share/gephex/icon

icon_DATA    = gephex-gui.xpm gephex-engine.xpm
data_DATA    = gephex.conf.default run_in_terminal.sh
bin_SCRIPTS  = gephex-wrapper

EXTRA_DIST = $(icon_DATA) run_in_terminal.sh gephex-wrapper.in gephex.conf.default.in gephexw.conf.default

install-exec-hook:
	chmod ug+x $(DESTDIR)$(bindir)/gephex-wrapper
	rm -rf $(DESTDIR)$(bindir)/gephex-engine
	rm -rf $(DESTDIR)$(bindir)/gephex-gui
	rm -rf $(DESTDIR)$(bindir)/gephex
	ln -s $(DESTDIR)$(bindir)/gephex-wrapper $(DESTDIR)$(bindir)/gephex-engine
	ln -s $(DESTDIR)$(bindir)/gephex-wrapper $(DESTDIR)$(bindir)/gephex-gui
	ln -s $(DESTDIR)$(bindir)/gephex-wrapper $(DESTDIR)$(bindir)/gephex

install-data-hook:
	chmod u+x $(DESTDIR)$(datadir)/run_in_terminal.sh
	sed -e "s,\$$(prefix),@prefix@," < $(DESTDIR)$(datadir)/gephex.conf.default > $(DESTDIR)$(datadir)/gephex.conf.default.tmp
	mv $(DESTDIR)$(datadir)/gephex.conf.default.tmp	$(DESTDIR)$(datadir)/gephex.conf.default

uninstall-hook:
	rm -rf $(DESTDIR)$(bindir)/gephex-engine
	rm -rf $(DESTDIR)$(bindir)/gephex-gui
	rm -rf $(DESTDIR)$(bindir)/gephex

DISTCLEANFILES = gephex-wrapper gephex.conf.default
