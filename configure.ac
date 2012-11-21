AC_INIT([await], [1.0])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror])

AC_CONFIG_HEADERS([config.h])
AM_PROG_CC_C_O

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_SEARCH_LIBS([sem_open], [rt pthread], [], [AC_MSG_ERROR([No pthread library is available])])

AC_CHECK_ENABLE_DEBUG

AC_OUTPUT
