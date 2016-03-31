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

echo "Testing program $programName files in $testFilesDir/"

testID=1

if [[ ${debugMode} == 0 ]]
then
    for input in ${testFilesDir}/*.in; do
        echo "${input%.*}"
        ./${programName%.*} < ${input} > temp.out
        diff -q "${input%.*}.out" temp.out 1>/dev/null
        if [[ $? == "0" ]]
        then
            echo "Test ${testID} passed."
        else
            echo "Test ${testID} did not pass."
        fi
        ((testID++))
    done
else
    for input in ${testFilesDir}/*.in; do
        echo "${input%.*}"
        ./${programName%.*} < ${input} > temp.out
        diff -q "${input%.*}.out" temp.out 1>/dev/null
        if [[ $? == "0" ]]
        then
            echo "Test ${testID} passed."
        else
            echo "Test ${testID} did not pass."
        fi
        ((testID++))
    done
fi