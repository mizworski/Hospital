#!/bin/bash

if [[ "$1" == "-v" ]]
then
    debugMode=1
    programName=$2
    testFilesDir=$3
else
    debugMode=0
    programName=$1
    testFilesDir=$2
fi

echo "TESTING PROGRAM: $programName WITH TEST FILES IN DIR: $testFilesDir/"
if [[ ${debugMode} == 1 ]]
then
    echo "IN DEBUG MODE."
else
    echo "."
fi
failures=0

if [[ ${debugMode} == 0 ]]
then
    for input in ${testFilesDir}/*.in; do
        echo "TESTING: ${input%.*}..."
        ./${programName%.*} < ${input} 1> temp_stdout.out
        diff -q "${input%.*}.out" temp_stdout.out 1>/dev/null
        if [[ $? == "0" ]]
        then
            echo "STANDARD   OUT: SUCCESS"
        else
            echo "STANDARD   OUT: FAILURE"
            ((failures++))
        fi
    done
    rm temp_stdout.out
else
    for input in ${testFilesDir}/*.in; do
        echo "TESTING ${input%.*}..."
        ./${programName%.*}.dbg -v < ${input} > temp_stdout.out 2>temp_stderr.out
        diff -q "${input%.*}.out" temp_stdout.out 1>/dev/null
        if [[ $? == "0" ]]
        then
            echo "STANDARD   OUT: SUCCESS"
        else
            echo "STANDARD   OUT: FAILURE"
            ((failures++))
        fi
        diff -q "${input%.*}.err" temp_stderr.out 1>/dev/null
        if [[ $? == "0" ]]
        then
            echo "DIAGNOSTIC OUT: SUCCESS"
        else
            echo "DIAGNOSTIC OUT: FAILURE"
            ((failures++))
        fi
    done
    rm temp_stdout.out
    rm temp_stderr.out
fi

echo "TESTS FAILED: ${failures}"