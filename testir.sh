#!/bin/bash

Green='\033[0;32m'
Blue='\033[0;34m'
Red='\033[0;31m'

[[ $# -ne 1 ]] && echo -e "Usage: $0 <llir-dir>\n<llir-dir> contains generated LLVM IR" && exit 1

srcdir=$1
outdir=IRtest_out

mkdir -p $outdir

file_num=`ls $srcdir | wc -l`
current_file_count=1

for file in `ls $srcdir`
do
    progress="[$current_file_count/$file_num]"
    elf=$outdir/${file::-2}elf
    out=${elf::-3}out
    err=${elf::-3}err

    clang $srcdir/$file -x ir -o $elf 2> $err

    compile_status=$?
    if [ $compile_status -eq 0 ] 
    then
        ./$elf > $out
        run_status=$?
        if [ $run_status -eq 0 ]
        then
            echo -e "${Green}${progress} ${file} passed"
            rm -f $err
            [ ! -s $out ] && rm -f $out
        else
            echo -e "${Blue}${progess} ${file} runtime error, details saved to ${err}"
        fi
    else
        echo -e "${Red}${progress} ${file} compile error, details saved to ${err}"
    fi
    current_file_count=`expr $current_file_count + 1`
done
