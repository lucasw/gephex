#!/bin/sh

# perform the necessary postinstall steps

PREFIX=$HOME/gephex

PERSONAL_DIR=$HOME/.gephex

if (test -d $PERSONAL_DIR); then
    echo "$PERSONAL_DIR already exists, exiting!"
    exit;
fi

mkdir $PERSONAL_DIR
mkdir $PERSONAL_DIR/graphs
mkdir $PERSONAL_DIR/sequences
mkdir $PERSONAL_DIR/playlists

cp qtgui/gui.conf $PERSONAL_DIR/gui.conf

sed "s|XXX_MODULE_DIRS_XXX|$PREFIX/lib/gephex/modules/|" engine/engine.conf.template > $PERSONAL_DIR/engine1.conf

sed "s|XXX_TYPE_DIRS_XXX|$PREFIX/lib/gephex/types/|" $PERSONAL_DIR/engine1.conf > $PERSONAL_DIR/engine.conf

sed "s|XXX_GRAPH_DIR_XXX|$PERSONAL_DIR/graphs/|" $PERSONAL_DIR/engine.conf > $PERSONAL_DIR/engine1.conf

sed "s|XXX_SEQUENCE_DIR_XXX|$PERSONAL_DIR/sequences/|" $PERSONAL_DIR/engine1.conf > $PERSONAL_DIR/engine.conf

sed "s|XXX_PLAYLIST_DIR_XXX|$PERSONAL_DIR/playlists/|" $PERSONAL_DIR/engine.conf > $PERSONAL_DIR/engine1.conf

mv $PERSONAL_DIR/engine1.conf $PERSONAL_DIR/engine.conf
