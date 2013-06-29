#!/bin/sh

REVISION=$1
NAME=$2
DISTDIR=$3

#
# example usage: 
# > make_release.sh gephex@gephex.org--2004/gephex--release--0.4.1 \
#    gephex-0.4.1pre3 gephex-0.4.1
#

if [ -e $NAME ]
then
  echo File or directory $NAME already exists.
  exit 1
fi

tla get $REVISION $NAME

cd $NAME

tla build-config configs/release.arch

./bootstrap.sh

./configure

make

make distcheck

tar xvzf $DISTDIR.tar.gz

mv $DISTDIR $NAME

tar cv $NAME > $NAME.tar
bzip2 $NAME.tar

mv $NAME.tar.bz2 ..

cd ..

rm -rf $NAME

echo $NAME.tar.bz2 is ready
