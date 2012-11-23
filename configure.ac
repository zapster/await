# configure.at: configuration
#
#    Copyright 2012 Josef Eisl <zapster@zapster.cc>
#
#    This file is part of await.
#
#    Foobar is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
#

AC_INIT([await], [1.0])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror -Wsyntax parallel-tests])

AC_CONFIG_HEADERS([config.h])

# ugly hack because i do not want -g -O2 by default
# should check if CFLAGS is empty
CFLAGS_ORIG=${CFLAGS}
AM_PROG_CC_C_O
CFLAGS=${CFLAGS_ORIG}

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
  tests/Makefile
])
AC_SEARCH_LIBS([sem_open], [rt pthread], [], [AC_MSG_ERROR([No pthread library is available])])

AC_CHECK_ENABLE_DEBUG

AC_OUTPUT
