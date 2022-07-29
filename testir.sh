#!/bin/bash

set -u

Green='\033[0;32m'
Yellow='\033[0;33m'
Blue='\033[0;34m'
Red='\033[0;31m'

[[ $# -ne 2 ]] && echo -e "Usage: $0 <testcases-dir> -g/-t\n<testcases-dir> contains generated LLVM IR\n-g --- complie with clang/gcc to get the rigth answers\n-t --- test our compiler" && exit 1

# 
#bison -d syntax_analyzer.y
#flex lexical_analyzer.l

if [ -d "./build" ]; then
    echo "directory \"./build\" exists"
    cd build || exit
    cmake ..
    make
else 
    mkdir build
    cd build || exit
    cmake ..
    make
fi

cp check.out ../check.out
cd -

# test compiler
srcdir=$1
IRdir=irs
TestOutDir=IRtest_out

mkdir -p $TestOutDir
mkdir -p $IRdir

file_num=`ls $srcdir/*.sy | wc -l | tr -d '[:space:]'`
current_file_count=1

for file in `find $srcdir -name '*.sy' -exec basename {} \;`
do
    input=$srcdir/${file%.*}.in
    correct_out=$srcdir/${file%.*}.out
    # get correct out
    if [ $2 = "-g" ]
    then 
        correct_elf=$srcdir/${file%.*}.elf
        clang -xc $srcdir/$file -o $correct_elf
        if [ -f $input] 
        then 
            ./$correct_elf < $input > $correct_out
        else
            ./$correct_elf > $correct_out
        fi
        echo $? >> $correct_out
    elif [ $2 = "-t" ]
    then
        progress="[$current_file_count/$file_num]"

        ir=${file%.*}.ll
        ./build/check.out < $srcdir/$file > $IRdir/$ir
        
        test_elf=$TestOutDir/${ir%.*}.elf
        test_out=${test_elf%.*}.out
        test_err=${test_elf%.*}.err

        clang $IRdir/$ir -x ir -o $test_elf 2> $test_err

        compile_status=$?
        if [ $compile_status -eq 0 ] 
        then
            if [ -f $input ]
            then
                timeout 5 ./$test_elf < $input > $test_out 2>>$test_err
            else
                timeout 5 ./$test_elf > $test_out 2>>$test_err
            fi
            run_status=$?
            echo $run_status >> $test_out

            diff $test_out $correct_out > _dev_null
            diff_status=$?

            if [ $run_status -eq 124 ]
            then
                echo -e "${Blue}${progress} ${file} timeout, details saved to ${test_err}"
            elif [ $diff_status -eq 0 ]
            then
                echo -e "${Green}${progress} ${file} passed"
                rm -f $test_err
                [ ! -s $test_out ] && rm -f $test_out
            else
                echo -e "${Yellow}${progress} ${file} runtime error, details saved to ${test_err}"
            fi
        else
            echo -e "${Red}${progress} ${file} compile error, details saved to ${test_err}"
        fi
        current_file_count=`expr $current_file_count + 1`
    fi
done