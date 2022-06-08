#!/bin/bash

CWD=`pwd`
TESTEX="$CWD/../bin/sneakyengine_tst"
VALCMD="valgrind --leak-check=yes $TESTEX"

MAKE=`which make`
CMAKE=`which cmake`
VALGRIND=`which valgrind`

if [ "$MAKE" = "" ]; then
    echo "ERROR: make is not available in the PATH"
    exit
else
    echo "make is available"
fi

if [ "$CMAKE" = "" ]; then
    echo "ERROR: make is not available in the PATH"
    exit
else
    echo "cmake is available"
fi

if [ "$VALGRIND" = "" ]; then
    echo "ERROR: valgrind is not available in the PATH"
    exit
else
    echo "valgrind is available"
fi

    
cmake ..
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
echo "++++++++++++++"
echo "+++FINISHED+++"
echo "++++++++++++++"

sleep 2
echo "Running Valgrind leak check with command: $VALCMD"
sleep 1

$VALCMD
echo "++++++++++++++"
echo "+++FINISHED+++"
echo "++++++++++++++"
