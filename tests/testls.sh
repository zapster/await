#! /bin/bash

set -u
set -e

TESTNAME=await-test-ls
TESTCMD="echo \"test\""

$TESTCMD > $TESTNAME.out
$CMD $TESTNAME $TESTCMD > $TESTNAME.myout

diff $TESTNAME.out $TESTNAME.myout
rm $TESTNAME.out $TESTNAME.myout
