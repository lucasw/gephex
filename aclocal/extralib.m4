
dnl 
dnl CHECK_EXTRA_LIB([LIB-NAME], [LIB-CHECK], [DEFAULT],
dnl                 [WITH_VAR_NAME], [TEST_VAR_NAME], [USE_VAR_NAME],
dnl                 [ACTION_IF_USED])
dnl
dnl Checks for a library and sets automake conditionals and C defines in
dnl config.h based on the result.
dnl
dnl LIB-NAME:  the name used for output, the AM_CONDITIONAL and the AC_DEFINE
dnl LIB-CHECK: the autoconf code to perform the check for the library.
dnl            it must set the variable TEST_VAR_NAME to yes or no
dnl DEFAULT:   yes if the library should be used by default, no if not
dnl WITH_VAR_NAME: the name of the variable that should be set to indicate
dnl                wether the user wants this library (as specified with
dnl                a --with-LIB-NAME option to configure)
dnl TEST_VAR_NAME: the name of the variable that is set by LIB-CHECK to
dnl                indicate wether the library is present
dnl USE_VAR_NAME:  the name of the variable that is set to yes if
dnl                WITH_VAR_NAME = yes and TEST_VAR_NAME = yes (otherwise
dnl                it is set to no)
dnl ACTION_IF_USED: [optional] an action to be performed if USE_VAR_NAME=yes
dnl
dnl This macro first adds a command line switch to configure (with
dnl AC_ARG_WITH) which allows the user to turn the use of the library 
dnl on or off.
dnl If the library should be used, the LIB-CHECK is performed to check
dnl wether the library is available.
dnl If this test is successful, an AC_DEFINE "WITH_<LIB-NAME>" is set to 1
dnl and the optional ACTION-IF-USED is performed.
dnl In any case, an AM_CONDITIONAL "WITH_<LIB-NAME>" is set depending on
dnl the value of USE_VAR_NAME.
dnl
AC_DEFUN([CHECK_EXTRA_LIB],
[
AC_MSG_NOTICE([checking for $1])

AC_ARG_WITH([$1],
	    [AC_HELP_STRING([--with-$1],
		            [Turn on $1 support (default=$3).])],
            [case "${withval}" in
       yes)
       	 AC_MSG_NOTICE([$1 support turned on])
         [$4]=yes
       ;;
       no)
	 AC_MSG_NOTICE([$1 support turned off])
         [$4]=no
       ;;
       *)
         AC_MSG_ERROR([bad value ${withval} for --with-$1])
       ;;
     esac],[[$4]=[$3]])


if test "x$[$4]" = "xyes"; then
  ifelse([$2], , :, [$2])
  if test "x$[$5]" = "xyes"; then
    [$6]=yes
    AC_DEFINE([WITH_$1], [1], [build with $1 support])
    ifelse([$7], , :, [$7])
    AC_MSG_NOTICE([$1 is active])
  else
    [$6]=no
    AC_MSG_WARN([No $1 support found.])
    AC_MSG_NOTICE([$1 is not active])
  fi
else
  [$6]=no
  AC_MSG_NOTICE([$1 is not active])
fi

])
