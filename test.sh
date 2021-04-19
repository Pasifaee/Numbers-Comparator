#!/bin/bash

cd $2
mkdir tmp
for file in *.in
do
    echo "Plik $file"
    ../$1 <"$file" >"tmp/${file%in}out" 2>"tmp/${file%in}err"

    if cmp -s "${file%in}out" "tmp/${file%in}out"
    then
        echo "output:     OK"
    else
        echo "output:     NOT OK"
    fi

    if cmp -s "${file%in}err" "tmp/${file%in}err"
    then
        echo "error file: OK"
    else
        echo "error file: NOT OK"
    fi

    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ../$1 <"$file"
    valgrind_ret_val=$?
    if (($valgrind_ret_val == 0))
    then
        echo "No memory problems"
    else
        echo "Memory problem occured"
    fi
    printf "\n\n"
done

rm -r tmp
