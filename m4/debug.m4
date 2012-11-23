dnl configure.at: configuration
dnl
dnl Copyright 2012 Josef Eisl <zapster@zapster.cc>
dnl
dnl This file is part of await.
dnl
dnl Foobar is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl Foobar is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
dnl

AC_DEFUN([AC_CHECK_ENABLE_DEBUG],[
AC_MSG_CHECKING(whether debug code generation should be enabled)
AC_ARG_ENABLE([debug],
              [AS_HELP_STRING(--enable-debug,enable debug code generation [[default=no]])],
              [case "${enableval}" in
                   yes)
                       NDEBUG=no
                       ;;
                   *)
                       NDEBUG=yes
                       ;;
               esac],
              [NDEBUG=yes])

if test x"${NDEBUG}" = "xno"; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
    AC_DEFINE([NDEBUG], 1, [disable debug code])
fi
AM_CONDITIONAL([NDEBUG], test x"${NDEBUG}" = "xyes")
])
