dnl tests wether the v4l videodev header exists
dnl AM_PATH_V4L([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_V4L],
[
AC_MSG_CHECKING(for v4l header...)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

dnl AC_CHECK_HEADER([modules/src/v4lmodule/videodev.h],have_videodev_header=yes,have_videodev_header=no)

dnl if test "x$have_videodev_header" = "xyes"
dnl then
  AC_MSG_CHECKING(found header, checking wether it compiles)
  AC_TRY_COMPILE([#include <cstdlib>
                #include <linux/types.h>],[],
               videodev_h_compiles=yes,videodev_h_compiles=no)

  if test "x$videodev_h_compiles" = "xyes"
  then
    AC_MSG_RESULT(ok)
    ifelse([$1], , :, [$1])
  else
    AC_MSG_RESULT(does not compile)
    ifelse([$2], , :, [$2])
  fi
dnl else
dnl   AC_MSG_RESULT(missing)
dnl   ifelse([$2], , :, [$2])
dnl fi

AC_LANG_RESTORE()
])
