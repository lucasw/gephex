# This script is adapted from the script used at the alsaplayer project

#! /bin/sh
# Check Autoconf version
if [ -x `which autoconf` ]; then
	AC_VER=`autoconf --version | head -n 1 | sed 's/^[^0-9]*//'`
	AC_VER_MAJOR=`echo $AC_VER | cut -f1 -d'.'`
	AC_VER_MINOR=`echo $AC_VER | cut -f2 -d'.' | sed 's/[^0-9]*$//'`

	if [ "$AC_VER_MAJOR" -lt "2" ]; then
		echo "Autoconf 2.13 or greater needed to build configure."
		exit 1
	fi

	if [ "$AC_VER_MINOR" -lt "13" ]; then
		echo "Autoconf 2.13 or greater needed to build configure."
		exit 1
	fi

	if [ "$AC_VER_MINOR" -lt "50" ]; then
		if [ ! -e configure.in ]; then
			ln -s configure.ac configure.in
		fi
		echo "If you see some warnings about cross-compiling, don't worry; this is normal."
	else
		rm -f configure.in
	fi
else
	echo Autoconf not found. GePhex requires autoconf to bootstrap itself.
	exit 1
fi

run_cmd() {
    echo running $* ...
    if ! $*; then
	echo failed!
	exit 1
    fi
}

cat_acinclude() {
  cat aclocal/*.m4 > acinclude.m4
}

run_cmd	cat_acinclude
run_cmd	aclocal 2> /dev/null
run_cmd	libtoolize --force
run_cmd	autoheader	
run_cmd	automake --add-missing --copy --foreign
run_cmd	autoconf

echo
echo "./configure has been successfully built!"
echo "See './configure --help' for available options"
echo
