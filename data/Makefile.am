datadir = $(prefix)/share/gephex/
icondir = $(prefix)/share/gephex/icon

icon_DATA    = gephex-gui.xpm gephex-engine.xpm
data_DATA    = gephex.conf.default
bin_SCRIPTS  = gephex-wrapper

EXTRA_DIST = $(icon_DATA) gephex-wrapper.template gephex.conf.default.template

gephex.conf.default: gephex.conf.default.template
	cat gephex.conf.default.template | sed s:__PREFIX__:$(prefix):g - > gephex.conf.default

gephex-wrapper: gephex-wrapper.template	
	cat gephex-wrapper.template | sed s:__PREFIX__:$(prefix):g - > gephex-wrapper
install-exec-hook:
	chmod ug+x $(bindir)/gephex-wrapper
	rm -rf $(bindir)/gephex-engine
	rm -rf $(bindir)/gephex-gui
	ln -s $(bindir)/gephex-wrapper $(bindir)/gephex-engine
	ln -s $(bindir)/gephex-wrapper $(bindir)/gephex-gui
