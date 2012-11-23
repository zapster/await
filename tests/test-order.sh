#! /bin/bash
# tests/test-order.sh: test if the commands are issued in the correct order
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

##
# IMPORTANT:
#
# This testcase ensures that the commands are issued in the correct order.
#
# Not passing this test means that the POSIX semaphores are not unlock in
# a FIFO manner. This is a design flaw of await _NOT_ of your semaphore
# implementation. In fact await abuses semaphores for things they are not
# built for. This is about to change in the future. Maybe...
#
##

set -u
set -e

TESTNAME=await-test-order
TESTCMD="echo \"test\""


# reset output files
echo "test: "$TESTNAME > $TESTNAME.out
echo "test: "$TESTNAME > $TESTNAME.myout

# delay this await group
$CMD $TESTNAME sleep 15 &
perl -e 'use Time::HiRes qw(usleep nanosleep); usleep(1000);'

echo "started await..."

echo "generation output..."
for i in `seq 500` ; do
  echo "test"$i >> $TESTNAME.out
  $CMD $TESTNAME echo "test"$i >> $TESTNAME.myout &
  perl -e 'use Time::HiRes qw(usleep nanosleep); usleep(1000);'
done

# wait for all processes to finish
echo "waiting for await..."
$CMD $TESTNAME true

diff $TESTNAME.out $TESTNAME.myout
rm $TESTNAME.out $TESTNAME.myout
