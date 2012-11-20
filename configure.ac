AC_INIT([await], [1.0])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
AC_CONFIG_HEADERS([config.h])
AM_PROG_CC_C_O
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_SEARCH_LIBS([sem_open], [rt pthread], [], [AC_MSG_ERROR([No pthread library is available])])
AC_OUTPUT
