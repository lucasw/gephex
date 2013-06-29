dnl tests wether the sstream header exists
dnl AM_PATH_SSTREAM([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_SSTREAM],
[
AC_MSG_CHECKING(for sstream header...)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

AC_TRY_COMPILE([#include <sstream>],[std::ostringstream os; os << "hallo";],
               have_sstream=yes, have_sstream=no)

if test "x$have_sstream" = "xyes"
then
  AC_MSG_RESULT(ok)
  ifelse([$1], , :, [$1])
else
  AC_MSG_RESULT(missing)
  ifelse([$2], , :, [$2])
fi

AC_LANG_RESTORE()
])
