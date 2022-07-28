#!/bin/bash

set -u

Green='\033[0;32m'
Yellow='\033[0;33m'
Blue='\033[0;34m'
Red='\033[0;31m'

#[[ $# -ne 1 ]] && echo -e "Usage: $0 <llir-dir>\n<llir-dir> contains generated LLVM IR" && exit 1

srcdir=oldtest
IRdir=irs
TestOutDir=IRtest_out
OutDir=rigth_out


mkdir -p $OutDir
mkdir -p $TestOutDir
mkdir -p $IRdir

file_num=`ls $srcdir | wc -l | tr -d '[:space:]'`
current_file_count=1

for file in `ls $srcdir`
do
    ir=${file%.*}.ll
    ./build/check.out < $srcdir/$file > $IRdir/$ir
    
    progress="[$current_file_count/$file_num]"
    elf=$TestOutDir/${ir%.*}.elf
    out=${elf%.*}.out
    err=${elf%.*}.err

    clang -xc $srcdir/$file -o $OutDir/${file%.*}.elf 
    clang $IRdir/$ir -x ir -o $elf 2> $err

    compile_status=$?
    if [ $compile_status -eq 0 ] 
    then
        timeout 5 ./$elf > $out 2>>$err
        run_status=$?
        ./$OutDir/${file%.*}.elf > $OutDir/${file%.*}.out
        right_status=$?
        if [ $run_status -eq $right_status ]
        then
            echo -e "${Green}${progress} ${file} passed"
            rm -f $err
            [ ! -s $out ] && rm -f $out
        elif [ $run_status -eq 124 ]
        then
            echo -e "${Blue}${progress} ${file} timeout, details saved to ${err}"
        else
            echo -e "${Yellow}${progress} ${file} runtime error, details saved to ${err}"
        fi
    else
        echo -e "${Red}${progress} ${file} compile error, details saved to ${err}"
    fi
    current_file_count=`expr $current_file_count + 1`
done
