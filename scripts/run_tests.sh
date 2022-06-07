#!/bin/bash

CWD=`pwd`
TESTEX="$CWD/../bin/sneakyengine_tst"
VALCMD="valgrind --leak-check=yes $TESTEX"

make

if [ -f $TESTEX ]; then
    echo "Test binary exists"
    sleep 0.5
else
    echo "ERROR: test binary does not exist"
    sleep 0.5
    exit
fi

echo "CWD: $CWD"
sleep 0.5
echo "Running basic tests from $TESTEX"
sleep 0.5

#"chmod +x $TESTEX"
$TESTEX

sleep 1
echo "Running Valgrind leak check with command: $VALCMD"
sleep 1

$VALCMD
