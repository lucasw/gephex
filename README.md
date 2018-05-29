Example Build
-------------

On Ubuntu 16.04.

gephex can't be built completely out of source, running bootrap inside the source tree is needed
and will create a few m4 files and many Makefile.in files (that can be cleaned with git clean):

```
git clone https://github.com/lucasw/gephex.git
cd gephex
./bootstrap.sh
```

```
running cat_acinclude ...
running aclocal ...
running libtoolize --force ...
libtoolize: putting auxiliary files in '.'.
libtoolize: linking file './ltmain.sh'
libtoolize: Consider adding 'AC_CONFIG_MACRO_DIRS([m4])' to configure.ac,
libtoolize: and rerunning libtoolize and aclocal.
libtoolize: Consider adding '-I m4' to ACLOCAL_AMFLAGS in Makefile.am.
running autoheader ...
running automake --add-missing --copy --foreign ...
configure.ac:7: warning: AM_INIT_AUTOMAKE: two- and three-arguments forms are deprecated.  For more info, see:
configure.ac:7: http://www.gnu.org/software/automake/manual/automake.html#Modernize-AM_005fINIT_005fAUTOMAKE-invocation
configure.ac:12: installing './compile'
...
util/src/libjoystick/Makefile.am:31: warning: 'INCLUDES' is the old name for 'AM_CPPFLAGS' (or '*_CPPFLAGS')
util/src/misc/Makefile.am:14: warning: 'INCLUDES' is the old name for 'AM_CPPFLAGS' (or '*_CPPFLAGS')
running autoconf ...

./configure has been successfully built!
See './configure --help' for available options
```

Haven't even tried ffmpeg build disabling it for now:

```
cd ..
mkdir build_gephex
cd build_gephex
../gephex/configure --prefix=$HOME/other/install --with-qt-libdir=/usr/lib/x86_64-linux-gnu --with-qt-bindir=/usr/share/qt4/bin --with-qt-incdir=/usr/share/qt4/include --without-FFMPEG
```

($HOME/other/install is already set up in bashrc to be used for binaries and libraries and so on)

```
checking build system type... x86_64-pc-linux-gnu
checking host system type... x86_64-pc-linux-gnu
checking target system type... x86_64-pc-linux-gnu
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /bin/mkdir -p
...
config.status: creating util/include/Makefile
config.status: creating util/include/compatibility/Makefile
config.status: creating util/src/Makefile
config.status: creating util/src/cpuinfo/Makefile
config.status: creating util/src/joystick_midi_net/Makefile
config.status: creating util/src/libgeo/Makefile
config.status: creating util/src/libjoystick/Makefile
config.status: creating util/src/misc/Makefile
config.status: creating doc/Makefile
config.status: creating doc/images/Makefile
config.status: creating config.h
config.status: executing depfiles commands
config.status: executing libtool commands
```

config.log has a lot of useful info in it in addition to the stdout.

```
make
```

```
mv -f .deps/tcpclientsocket.Tpo .deps/tcpclientsocket.Po
g++ -DHAVE_CONFIG_H -I. -I../../.. -I ./.. -I ./../../../util/include    -g -O2 -MT fdsocket.o -MD -MP -MF .deps/fdsocket.Tpo -c -o fdsocket.o fdsocket.cpp
mv -f .deps/fdsocket.Tpo .deps/fdsocket.Po
g++ -DHAVE_CONFIG_H -I. -I../../.. -I ./.. -I ./../../../util/include    -g -O2 -MT socketadaptor.o -MD -MP -MF .deps/socketadaptor.Tpo -c -o socketadaptor.o socketadaptor.cpp
mv -f .deps/socketadaptor.Tpo .deps/socketadaptor.Po
g++ -DHAVE_CONFIG_H -I. -I../../.. -I ./.. -I ./../../../util/include    -g -O2 -MT convertbin.o -MD -MP -MF .deps/convertbin.Tpo -c -o convertbin.o convertbin.cpp
mv -f .deps/convertbin.Tpo .deps/convertbin.Po
...
    </para>
      </refsect1>

      </refentry>

      if test "x" = "x"; then touch documentation.html; else xsltproc --xinclude -o documentation.html /html/docbook.xsl ./documentation.xml; fi
      make[3]: Leaving directory '/home/lucasw/own/github/gephex/doc'
      make[2]: Leaving directory '/home/lucasw/own/github/gephex/doc'
      make[2]: Entering directory '/home/lucasw/own/github/gephex'
      make[2]: Leaving directory '/home/lucasw/own/github/gephex'
      make[1]: Leaving directory '/home/lucasw/own/github/gephex'
```

```
make install
```

Install ends with manual pages getting displayed, and failing to be installed?

```
if test "xman" = "x"; then  touch gephex-gui.1; else man ./gephex-gui.xml; fi
 /bin/mkdir -p '/home/lucasw/other/install/share/man/man1'
  /usr/bin/install -c -m 644 ./gephex.1 ./gephex-engine.1 ./gephex-gui.1 '/home/lucasw/other/install/share/man/man1'
  /usr/bin/install: cannot stat './gephex.1': No such file or directory
  /usr/bin/install: cannot stat './gephex-engine.1': No such file or directory
  /usr/bin/install: cannot stat './gephex-gui.1': No such file or directory
  Makefile:437: recipe for target 'install-man1' failed
  make[3]: *** [install-man1] Error 1
  make[3]: Leaving directory '/home/lucasw/own/github/gephex/doc'
  Makefile:669: recipe for target 'install-am' failed
  make[2]: *** [install-am] Error 2
  make[2]: Leaving directory '/home/lucasw/own/github/gephex/doc'
  Makefile:508: recipe for target 'install-recursive' failed
  make[1]: *** [install-recursive] Error 1
  make[1]: Leaving directory '/home/lucasw/own/github/gephex/doc'
  Makefile:442: recipe for target 'install-recursive' failed
  make: *** [install-recursive] Error 1
```

gephex.conf
-----------

There needs to be a ~/.gephex/0.4/gephex.conf file of the form:

```
common {
    media_path           = [/home/lucasw/other/install/share/gephex]
}

engine {
    type_path            = [/home/lucasw/Desktop/gephex/types/;/home/lucasw/other/install/lib/gephex-0.4/types/]
    module_path          = [/home/lucasw/Desktop/gephex/modules/;/home/lucasw/other/install/lib/gephex-0.4/modules/]
    frei0r_path          = [/home/lucasw/.frei0r-1/lib/;/usr/local/lib/frei0r-1/;/usr/lib/frei0r-1/]
    graph_path           = [/home/lucasw/Desktop/gephex/graphs/]
    ipc_unix_node_prefix = [/tmp/gephex_socket_]
    ipc_type             = [inet]
    ipc_port             = [6666]
    renderer_interval    = [40]
    net_interval         = [40]
}

gui {
    ipc_type             = [inet]
    ipc_inet_hostname    = [localhost]
    ipc_port             = [6666]
    ipc_unix_node_prefix = [/tmp/gephex_socket_]
    engine_binary        = [/home/lucasw/other/install/bin/gephex-engine]
}
```

Running
-------

Run the executable:

```
gephex
```

```
  media_path	= /home/lucasw/other/install/share/gephex
  ipc_type	= inet
  ipc_inet_hostname	= localhost
  ipc_namedpipe_servername	= .
  ipc_unix_node_prefix	= /tmp/gephex_socket_
  ipc_port	= 6666
  engine_binary	= /home/lucasw/other/install/bin/gephex-engine
```

It will launch a server in a new terminal (unless it is already running?):

```
       ---             _           ---
    ----              | |            ----
  ----   __ _ ___ _ __| |  ___ _  __  ----
 -----  / _' | - \ '_ \ |_/ - \ \/ /  -----
------ | (_| | --/ |_) |  \ --/>  <   ------
 -----  \__. | \_| .__/ |' |\_/ /\ \  -----
  ----   ._' |\__/ |  |_||_|__//  \_| ----
   ----  |__/    |_|                 ----
      ---                          ---

[version:    "0.4.5"]
[build time: "May 28 2018 - 21:39:02"]
  media_path	= /home/lucasw/other/install/share/gephex
  graph_path	= /home/lucasw/Desktop/gephex/graphs/
  module_path	= /home/lucasw/Desktop/gephex/modules/;/home/lucasw/other/install/lib/gephex-0.4/modules/
  frei0r_path	= /home/lucasw/.frei0r-1/lib/;/usr/local/lib/frei0r-1/;/usr/lib/frei0r-1/
  type_path	= /home/lucasw/Desktop/gephex/types/;/home/lucasw/other/install/lib/gephex-0.4/types/
  ipc_type	= inet
  ipc_port	= 6666
  renderer_interval	= 40
  net_interval	= 40
  ipc_unix_node_prefix	= /tmp/gephex_socket_
  autostart	= 0
  render_graph_id	= default
  render_snap_id	= default
  ttl	= 0
```

Old README
----------

Where to get the source
------------------------

If this is a binary release, you can get the source at http://www.gephex.org.

ffmpeg
-------

The source release contains the ffmpeg sources in contrib/ffmpeg.
It's a recent cvs snapshot, and has not been modified.

Check http://ffmpeg.sf.net for details on ffmpeg.


EffecTV
--------

This release contains effects that have been ported from EffecTV
(http://effectv.sf.net).
The sources are in './effectvmodules'.

Thanks to the EffecTV people for their cool effects!


Important note:
---------------

  On unix platforms, the layout of the ~/.gephex directory has
  changed with 0.4.1. All files that previously have been
  in "~/.gephex/" are now moved to the new directory
  "~/.gephex/0.4/". This change is done automatically when you first
  start gephex-0.4.1. Note that after that, you cannot simply start
  an older version of gephex, because it cannot find the config files
  and will create new ones.


For documentation, please have a look at doc/documentation.html
or http://www.gephex.org.
