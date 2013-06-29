dnl dx.m4
dnl set directx compiler and linker flags
dnl Note: the variable DXSDK_DIR must be set
dnl or --with-dxsdk-dir must be given
dnl
dnl AM_PATH_DX(MINIMUM_VERSION, 
dnl            [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_DX],
[
AC_CHECKING([for DirectX ...])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

saved_LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
saved_LIBRARY_PATH="$LIBRARY_PATH"
saved_CXXFLAGS="$CXXFLAGS"
saved_LDFLAGS="$LDFLAGS"
saved_LIBS="$LIBS"

HAVE_DX=no
min_dx_version=ifelse([$1], ,8.0, $1)

AC_ARG_WITH([dxsdk-dir],
  [AC_HELP_STRING([--with-dxsdk-dir=PFX],
                  [Prefix where DirectX is installed (optional, if not given, the environment variable DXSDK_DIR is used)])],
  dxsdk_dir="$withval",
  dxsdk_dir=""
)

dnl Check whether the headers can be found

if test "x$dxsdk_dir" = "x"
then
  dxsdk_dir=$DXSDK_DIR
  AC_MSG_NOTICE([using environment variable DXSDK_DIR...])
fi

AC_MSG_NOTICE([looking in $dxsdk_dir/Include ...])

if test -e $dxsdk_dir/Include/ddraw.h
then
  HAVE_DX=yes
  DX_CXXFLAGS="-I$dxsdk_dir/Include"
  DX_LIBS="-L$dxsdk_dir/Lib -lddraw"

  AC_MSG_RESULT([found in $dxsdk_dir])
else
  AC_MSG_RESULT([not found])
  HAVE_DX=no
fi

if test "x$HAVE_DX" = "xyes"
then
  ifelse([$2], , :, [$2])
else
  ifelse([$3], , :, [$3])
fi

AC_SUBST(DX_CXXFLAGS)
AC_SUBST(DX_LIBS)

AC_LANG_RESTORE()

LD_LIBRARY_PATH="$saved_LD_LIBRARY_PATH"
LIBRARY_PATH="$saved_LIBRARY_PATH"
CXXFLAGS="$saved_CXXFLAGS"
LDFLAGS="$saved_LDFLAGS"
LIBS="$saved_LIBS"
dnl rm -f conf.qttest
])
