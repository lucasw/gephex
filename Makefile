FIRST_DIRS=base engine qtgui types
INTERMEDIATE_INSTALL_DIRS=engine/src/engine types
FINAL_INSTALL_DIRS=engine/src/engine qtgui/src/gui types modules
SECOND_DIRS=modules
SUBDIRS=$(FIRST_DIRS) $(SECOND_DIRS)


CONFIGURE_FLAGS= --prefix=$(HOME)/gephex 

BUILD_FLAGS=
.PHONY: all
all: build

.PHONY: autoconf
autoconf:
	for i in $(SUBDIRS); do  \
		temp=`pwd` && cd $$i && make -f Makefile.cvs && cd $$temp ; \
	done;

.PHONY: configure
configure:
	for i in $(SUBDIRS); do  \
		temp=`pwd` && cd $$i && rm -f config.cache && ./configure $(CONFIGURE_FLAGS) && cd $$temp ; \
	done;

.PHONY: build
build:
	for i in $(FIRST_DIRS) $(SECOND_DIRS); do  \
		temp=`pwd` && cd $$i && make $(BUILD_FLAGS) install && cd $$temp ; \
	done;


.PHONY: install
install:
	for i in $(FINAL_INSTALL_DIRS); do  \
		temp=`pwd` && cd $$i && make install && cd $$temp ; \
	done;

.PHONY: clean
clean:
	for i in $(SUBDIRS); do  \
		temp=`pwd` && cd $$i ; make clean ; cd $$temp ; \
	done;

.PHONY: deb
deb: dist
	rm -rf gephex-dists
	mkdir gephex-dists
	mv `find . -name "*.tar.gz"` gephex-dists

	/bin/sh -c "cd gephex-dists;\
		   tar xvzf gephex-base-0.0.1.tar.gz;\
		   cd gephex-base-0.0.1;\
		   fakeroot dpkg-buildpackage -us -uc" 

	su -c "dpkg -i gephex-dists/gephex-base_0.0.1-1_i386.deb \
	       gephex-dists/gephex-base-dev_0.0.1-1_i386.deb;"

	/bin/sh -c "cd gephex-dists;\
		   tar xvzf gephex-engine-0.0.1.tar.gz;\
		   cd gephex-engine-0.0.1;\
		   fakeroot dpkg-buildpackage -us -uc" 

	su -c "dpkg -i gephex-dists/gephex-engine_0.0.1-1_i386.deb;"

	/bin/sh -c "cd gephex-dists;\
		   tar xvzf gephex-types-0.0.1.tar.gz;\
		   cd gephex-types-0.0.1;\
		   fakeroot dpkg-buildpackage -us -uc" 

	su -c "dpkg -i gephex-dists/gephex-types_0.0.1-1_i386.deb;"

	/bin/sh -c "cd gephex-dists;\
		   tar xvzf gephex-modules-0.0.1.tar.gz;\
		   cd gephex-modules-0.0.1;\
		   fakeroot dpkg-buildpackage -us -uc" 

	su -c "dpkg -i gephex-dists/gephex-modules_0.0.1-1_i386.deb;"

	/bin/sh -c "cd gephex-dists;\
		   tar xvzf gephex-qtgui-0.0.1.tar.gz;\
		   cd gephex-qtgui-0.0.1;\
		   fakeroot dpkg-buildpackage -us -uc" 

	su -c "dpkg -i gephex-dists/gephex-qtgui_0.0.1-1_i386.deb;"


.PHONY: distclean
distclean:
	for i in $(SUBDIRS); do  \
		temp=`pwd` && cd $$i ; make distclean ; cd $$temp ; \
	done;

.PHONY: dist
dist:
	for i in $(SUBDIRS); do  \
		temp=`pwd` && cd $$i && make dist && cd $$temp ; \
	done;




