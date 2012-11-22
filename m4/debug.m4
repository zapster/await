AC_DEFUN([AC_CHECK_ENABLE_DEBUG],[
AC_MSG_CHECKING(whether debug code generation should be enabled)
AC_ARG_ENABLE([debug],
              [AS_HELP_STRING(--disable-debug,disable debug code generation [[default=enabled]])],
              [case "${enableval}" in
                   no)
                       NDEBUG=yes
                       AC_DEFINE([NDEBUG], 1, [disable debug code])
                       ;;
                   *)
                       NDEBUG=no
                       ;;
               esac],
              [NDEBUG=no])

if test x"${NDEBUG}" = "xno"; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi
AM_CONDITIONAL([NDEBUG], test x"${NDEBUG}" = "xyes")
])
