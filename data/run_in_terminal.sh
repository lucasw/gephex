#!/bin/sh

DEFAULT_TERM=`which x-terminal-emulator`
XTERM=`which xterm`

if test "x$GEPHEX_XTERM" != "x";
then
  TERM_CMD=$GEPHEX_XTERM
  EXEC_FLAG="-e"
  OPT_FLAGS=$GEPHEX_XTERM_FLAGS
elif test "x$DEFAULT_TERM" != "x";
then
  TERM_CMD=$DEFAULT_TERM
  EXEC_FLAG="-e"
  OPT_FLAGS=
elif test "x$XTERM" != "x";
then
  TERM_CMD=$XTERM
  EXEC_FLAG="-e"
  OPT_FLAGS="-bg black -fg white"
else
  TERM_CMD=
  EXEC_FLAG=
  OPT_FLAGS=
  echo "Could not find a working x terminal."
  echo "Starting $* as a background job."
fi

$TERM_CMD $OPT_FLAGS $EXEC_FLAG $*
