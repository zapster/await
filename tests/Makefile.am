# tests/Makefile.am: Makefile
#
#    Copyright 2012 Josef Eisl <zapster@zapster.cc>
#
#    This file is part of await.
#
#    await is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    await is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with await.  If not, see <http://www.gnu.org/licenses/>.
#

AM_TESTS_ENVIRONMENT = CMD='$(top_builddir)/src/await'; export CMD;
TESTS_ENVIRONMENT = $(AM_TESTS_ENVIRONMENT)
TESTS = testls.sh test-order.sh
