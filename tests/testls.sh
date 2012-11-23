#! /bin/bash
# tests/testsls.sh: testcase
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

set -u
set -e

TESTNAME=await-test-ls
TESTCMD="echo \"test\""

$TESTCMD > $TESTNAME.out
$CMD $TESTNAME $TESTCMD > $TESTNAME.myout

diff $TESTNAME.out $TESTNAME.myout
rm $TESTNAME.out $TESTNAME.myout
