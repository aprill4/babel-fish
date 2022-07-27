#!/bin/bash

Green='/033[0;32m'
Blue='/033[0;34m'
Red='/033[0;31m'

srcdir=$1
outdir="IRtest_out"

for file in $(ls $srcdir)
do
    if [[ ! -d $outdir ]]
    then 
        mkdir $outdir
    fi

    out=$outdir${file::-2}out
    print=${out::-3}print

    clang $file -x ir -o $out
    compile_status=$?
    if [ $compile_status -eq 0 ]
    then 
        ./$out > $print
        run_status=$?
        if [ $run_status -eq 0 ]
        then 
            echo "${Green}${file} passed"
            if [ ! -s $print ]
            then
                rm -f $print
            fi
        else
            echo "${Blue}${file} runs failed"
        fi
    else
        echo "${Red}${file} compiles failed"
    fi
done
